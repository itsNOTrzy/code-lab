#define _CRT_SECURE_NO_WARNINGS
#include "PicReader.h"
#include "FastPrinter.h"
#include <conio.h>
#include <string>
#include <iostream>
#pragma comment(lib, "winmm.lib")
using namespace std;

string image_names[] = { "", "airplane.jpg", "baboon.jpg", "barbara.jpg", "cameraman.jpg",
		"compa.png", "goldhill.jpg", "lena.jpg", "lena1.jpg", "milkdrop.jpg", "peppers.jpg", "woman.jpg" };
string ascii = "MNHQ$OC?7>!:-;. "; // 16 级
string ascii_color = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";

static void SetPos(int x, int y) {
	COORD point = { x,y };
	HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(HOutput, point);
}
static void SetConsoleSize(int width, int height) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		cerr << "无法获取控制台信息! " << endl;
	}
	// 确保缓冲区尺寸不小于窗口尺寸
	COORD bufferSize;
	bufferSize.X = max(width, csbi.srWindow.Right - csbi.srWindow.Left + 1);
	bufferSize.Y = max(height, csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
	if (!SetConsoleScreenBufferSize(hConsole, bufferSize)) {
		cerr << "无法设置缓冲区大小! " << endl;
	}
	// 设置窗口尺寸
	SMALL_RECT windowSize;
	windowSize.Left = 0;
	windowSize.Top = 0;
	windowSize.Right = width - 1;  // 窗口宽度 = 右边界 - 左边界 + 1
	windowSize.Bottom = height - 1; // 窗口高度 = 下边界 - 上边界 + 1
	if (!SetConsoleWindowInfo(hConsole, TRUE, &windowSize)) {
		cerr << "无法设置窗口大小! " << endl;
	}
}
static void SetFont(int size) {
	CONSOLE_FONT_INFOEX cfi = { 0 }; 
	cfi.cbSize = sizeof(cfi);
	cfi.dwFontSize.Y = size; // 最小高度1 最大30
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetCurrentConsoleFontEx(hStdOut, NULL, &cfi);
}

Array RGB2GRAY(Array& im) {
	int height = im.shape[0]; int width = im.shape[1];
	Array gray_im(height, width);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int gray = 0.299 * im.at(i, j, 0) + 0.587 * im.at(i, j, 1) + 0.114 * im.at(i, j, 2); //加权平均
			gray_im.at(i, j).set(gray); // 通道全部换灰度
		}
	}
	return gray_im; // .shape[2] == 0
}

void show_ascii(Array& im) {
	int num_cols = 128; int num_chars = ascii.size() - 1;
	int scale = 2; // ASCII字母
	int height = im.shape[0]; int width = im.shape[1];
	float cell_width = float(width) / num_cols;
	float cell_height = scale * cell_width;
	int num_rows = height / cell_height;
	if (num_cols > width || num_rows > height) {
		cell_width = 1;
		cell_height = scale * cell_width;
		num_cols = width / cell_width;
		num_rows = height / cell_height;
	}
	int step = 0.9 * cell_width + 0.1 * cell_height; // weights
	Array result;
	result.reshape(im.shape[0] / step, im.shape[1] / step); //rows approx to 128
	for (int i = 0; i < im.shape[0] / step; i++) {
		for (int j = 0; j < im.shape[1] / step; j++) {
			int sum = 0;
			for (int x = 0; x < step; ++x) {
				for (int y = 0; y < step; ++y) sum += int(im.at(step * i + x, step * j + y));
			}
			int index = int(sum / (step * step)) * num_chars / 255; // 强度越大 ascii 字符内容越少 (越白)
			result.at(i, j) = int(ascii[index]);
		}
	}
	height = result.shape[0]; //图片行数
	width = result.shape[1]; //图片列数
	FastPrinter printer(width * 2, height, 5); //创建窗口，字体大小
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			char temp[3]{ char(result.at(i , j)), char(result.at(i , j)) };
			COORD pos = { j * 2 , i };
			printer.setText(pos, temp, 2, 0, 0, 0, 255, 255, 255);
		}
	}
	printer.draw(true);
	printer.cleanSrceen();
	system("pause>nul");
}

void show_ascii_color(Array& im) {
	int num_cols = 128; int num_chars_color = ascii_color.size() - 1;
	int scale = 2;
	int height = im.shape[0]; int width = im.shape[1];
	float cell_width = float(width) / num_cols;
	float cell_height = scale * cell_width;
	int num_rows = height / cell_height;
	if (num_cols > width || num_rows > height) {
		cell_width = 1;
		cell_height = scale * cell_width;
		num_cols = width / cell_width;
		num_rows = height / cell_height;
	}
	int step = 0.9 * cell_width + 0.1 * cell_height;
	Array result;
	result.reshape(im.shape[0] / step, im.shape[1] / step, 4);
	for (int i = 0; i < im.shape[0] / step; i++) {
		for (int j = 0; j < im.shape[1] / step; j++) {
			for (int k = 0; k < im.shape[2]; k++) {
				int sum = 0;
				for (int x = 0; x < step; ++x) {
					for (int y = 0; y < step; ++y) sum += int(im.at(step * i + x, step * j + y, k));
				}
				result.at(i, j, k) = sum / (step * step);
				int gray = 0.299 * int(result.at(i, j, 0)) + 0.587 * int(result.at(i, j, 1)) + 0.114 * int(result.at(i, j, 2));
				int index = (255 - gray) * num_chars_color / 255;  // 强度越大 ascii 字符内容越多 (越亮)
				result.at(i, j, 3) = int(ascii_color[index]); //ascii储存在通道4
			}
		}
	}
	height = result.shape[0];
	width = result.shape[1];
	FastPrinter printer(width * 2, height, 5);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			char temp[3]{ char(result.at(i , j, 3)), char(result.at(i , j, 3)) };
			COORD pos = { j * 2 , i };
			printer.setText(pos, temp, 2, result.at(i, j, 0), result.at(i, j, 1), result.at(i, j, 2), 0, 0, 0);
		}
	}
	printer.draw(true);
	printer.cleanSrceen();
	system("pause>nul");
}

void player() {
	char buf[150]; int delay = 33;
	clock_t stime = 0, ftime = 0;
	PlaySoundA("video2txt\\input\\input.wav", NULL, SND_FILENAME | SND_ASYNC);
	stime = clock();
	int i = 1, frames = 271;
	while (i <= frames) {
		if (i % 30 == 0) delay = 43; // 30 fps
		else delay = 33;
		string path = "video2txt\\input\\txt\\input_" + string(6 - to_string(i).length(), '0') + to_string(i) + ".txt";
		ftime = clock();
		if (ftime - stime >= delay) {
			FILE* frame = fopen(path.c_str(), "r");
			if (frame == nullptr) {
				printf("error to open");
				break;
			}
			else {
				SetConsoleSize(200, 57); // 行+1留位置
				SetFont(7);
				system("color f0");
				while (fgets(buf, 150, frame)) printf("%s", buf);
				fclose(frame);
				SetPos(0, 0);
				i++;
				stime += delay;
			}
		}
	}
	system("cls");
}

int main() {
	char style;
	while (1) {
		SetConsoleSize(120, 30);
		SetFont(15);
		system("color 0f");
		printf("[Esc-exit, Enter-color, Space-gray_white, Other-player]");
		style = _getch();
		if (style == 27) break;
		if (style == ' ' || style == '\r') {
			for (int i = 1; i <= 11; ++i) {
				string path = "classic_picture//" + image_names[i];
				PicReader imread; imread.readPic(path.c_str()); //读取图片
				Array image; imread.getData(image);
				if (style == '\r') show_ascii_color(image);  // 彩色
				else {
					Array gray_image = RGB2GRAY(image);
					show_ascii(gray_image);
				}
			}
		} /* .-pics2txt */
		else player();
	}
	return 0;
}