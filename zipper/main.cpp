#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include <chrono>
#include <unordered_map>
#include <cstdint>

// Helper function to compute a hash for four characters
uint32_t hashFunction(const char* data) {
    return (static_cast<uint32_t>(data[0]) << 24) |
        (static_cast<uint32_t>(data[1]) << 16) |
        (static_cast<uint32_t>(data[2]) << 8) |
        (static_cast<uint32_t>(data[3]));
}

// LZ4-like compression function (optimized with hash table)
void compress(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile, std::ios::binary);
    std::ofstream outFile(outputFile, std::ios::binary);

    if (!inFile || !outFile) {
        std::cerr << "Error opening files!" << std::endl;
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();

    std::deque<char> input((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    size_t inputSize = input.size();
    std::deque<char> output;

    std::unordered_map<uint32_t, size_t> hashTable; // Hash table to store positions of 4-byte sequences
    size_t i = 0;
    const size_t MIN_MATCH_LENGTH = 4;
    const size_t MAX_OFFSET = 65535; // Maximum offset for matching

    while (i + MIN_MATCH_LENGTH <= inputSize) {
        uint32_t hash = hashFunction(&input[i]);
        size_t matchOffset = 0;
        size_t matchLength = 0;

        if (hashTable.find(hash) != hashTable.end()) {
            size_t candidate = hashTable[hash];
            if (candidate + MIN_MATCH_LENGTH <= i && (i - candidate) <= MAX_OFFSET) { // Ensure the candidate is within bounds and offset is valid
                size_t j = 0;
                while (i + j < inputSize && input[candidate + j] == input[i + j] && j < 255) {
                    ++j;
                }
                if (j >= MIN_MATCH_LENGTH) {
                    matchLength = j;
                    matchOffset = i - candidate;
                }
            }
        }

        // Update hash table with current position
        hashTable[hash] = i;

        if (matchLength >= MIN_MATCH_LENGTH) {
            // Write match as (offset, length) pair
            output.push_back(static_cast<char>(0x80 | ((matchLength - MIN_MATCH_LENGTH) & 0x7F)));
            output.push_back(static_cast<char>((matchOffset >> 8) & 0xFF));
            output.push_back(static_cast<char>(matchOffset & 0xFF));
            i += matchLength;
        }
        else {
            // Write literal
            output.push_back(input[i++]);
        }
    }

    // Write remaining literals if any
    while (i < inputSize) {
        output.push_back(input[i++]);
    }

    outFile.write(reinterpret_cast<const char*>(&output[0]), output.size() * sizeof(char));


    inFile.close();
    outFile.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> compressionTime = end - start;
    std::cout << "Compression completed successfully in " << compressionTime.count() << " seconds." << std::endl;

    // Calculate compression rate
    std::ifstream original(inputFile, std::ios::binary | std::ios::ate);
    std::ifstream compressed(outputFile, std::ios::binary | std::ios::ate);
    double originalSize = original.tellg();
    double compressedSize = compressed.tellg();
    double compressionRate = (compressedSize / originalSize) * 100;

    std::cout << "Compression rate: " << compressionRate << "%" << std::endl;
}

// LZ4-like decompression function (optimized)
void decompress(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile, std::ios::binary);
    std::ofstream outFile(outputFile, std::ios::binary);

    if (!inFile || !outFile) {
        std::cerr << "Error opening files!" << std::endl;
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();

    std::deque<char> input((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    size_t inputSize = input.size();
    std::deque<char> output;


    size_t i = 0;
    while (i < inputSize) {
        if (input[i] & 0x80) { // Match
            if (i + 2 >= inputSize) {
                std::cerr << "Decompression error: insufficient data for match." << std::endl;
                return;
            }
            size_t matchLength = (input[i++] & 0x7F) + 4;
            size_t matchOffset = (static_cast<unsigned char>(input[i++]) << 8) | static_cast<unsigned char>(input[i++]);

            if (matchOffset > output.size()) {
                std::cerr << "Decompression error: match offset out of range." << std::endl;
                return;
            }

            size_t startPos = output.size() - matchOffset;

            // Dynamically adjust output size to handle large matches
            while (output.size() < startPos + matchLength) {
                output.push_back(0); // Fill with zeroes to ensure the match can be copied without overflow
            }

            // Copy match data
            for (size_t j = 0; j < matchLength; ++j) {
                output.push_back(output[startPos + j]);
            }
        }
        else { // Literal
            if (i >= inputSize) {
                std::cerr << "Decompression error: insufficient dataz for literal." << std::endl;
                return;
            }
            output.push_back(input[i++]);
        }
    }

    outFile.write(reinterpret_cast<const char*>(&output[0]), output.size() * sizeof(char));


    inFile.close();
    outFile.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> decompressionTime = end - start;
    std::cout << "Decompression completed successfully in " << decompressionTime.count() << " seconds." << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " {inputFile} {outputFile} {zip/unzip}" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    std::string mode = argv[3];

    if (mode == "zip") {
        compress(inputFile, outputFile);
    }
    else if (mode == "unzip") {
        decompress(inputFile, outputFile);
    }
    else {
        std::cerr << "Invalid mode: use 'zip' for compression or 'unzip' for decompression." << std::endl;
        return 1;
    }

    return 0;
}
