#ifndef ARRAY_H
#define ARRAY_H
#include <stdio.h>
class Array {
public:
    // 矩阵是否兼容
    bool isCompatible(const Array& other) const {
        //if (axisNum != other.axisNum) return false;
        for (int i = 0; i < axisNum; ++i)
            if (shape[i] != other.shape[i]) {
                printf("Matrix size mismatch!");
                return false;
            }
        return true;
    }
    // 总大小
    int totalSize() {
        int size = 1;
        for (int i = 0; i < axisNum; ++i) size *= shape[i];
        return size;
    }

    // 构造函数，支持多维初始化，使用参数包
    template <typename... Args>
    Array(Args... args) : index(0), axisNum(sizeof...(args)), nowAxis(0), shape{ args... } {
        // 获取参数包大小并转换为size_t数组
        auto num = sizeof...(args);
        if constexpr (sizeof...(args) > 0) {
            size_t list[] = { args... };
            size_t totalSize = 1; // 计算总大小
            for (size_t i = 0; i < num; ++i) totalSize *= list[i];
            data = new int[totalSize] {}; // 初始化数组
        }
        else data = nullptr;
    }
    // 析构函数
    ~Array() { delete[] data; }
    // 拷贝构造函数
    Array(const Array& a) : index(a.index), axisNum(a.axisNum), nowAxis(a.nowAxis) {
        for (int i = 0; i < axisNum; i++) shape[i] = a.shape[i];
        int size = totalSize();
        data = new int[size] {};
        for (int i = 0; i < size; i++) data[i] = a.data[i];
    }

    // 成员函数，用于设置或访问元素，使用参数包
    template <typename... Args>
    Array& at(Args... args) {
        // 获取参数包大小并转换为size_t数组
        auto num = sizeof...(args);
        size_t list[] = { args... };
        index = 0; //线性索引
        for (size_t i = 0; i < num; ++i) {
            int temp = 1; // 计算轴 i 的步长
            for (int j = i + 1; j < num; ++j) temp *= shape[j];
            index += list[i] * temp;
        }
        int size = totalSize();
        if (size <= index) {
            index = size - 1;
            printf("out of range!");
        }
        return *this;
    }

    // 成员函数，用于重塑矩阵，使用参数包
    template <typename... Args>
    void reshape(Args... args) {
        // 获取参数包大小并转换为size_t数组
        auto num = sizeof...(args);
        size_t list[] = { args... };

        // 检查是否可以reshape
        size_t newSize = 1; // 新矩阵总大小
        for (int i = 0; i < num; i++) newSize *= list[i];
        size_t oldSize = 1;
        for (int i = 0; i < axisNum; i++) oldSize *= shape[i]; // totalSize()
        if (1 == oldSize) oldSize = 0; // 空矩阵
        if (newSize < oldSize) printf("Invalid reshape dimension!");
        else if (newSize == oldSize) { // 如果大小相同，直接修改shape数组
            for (int i = 0; i < num; i++) shape[i] = list[i];
            axisNum = num;
        }
        else { //重新分配内存
            int* temp = new int[oldSize] {};
            for (int i = 0; i < oldSize; i++) temp[i] = data[i];
            delete[] data;
            data = new int[newSize] {};
            for (int i = 0; i < oldSize; i++) data[i] = temp[i];
            delete[] temp;

            for (int i = 0; i < num; i++) shape[i] = list[i];
            axisNum = num;
        }
    }

    // 获取数组内容的指针，返回内部数据
    int* get_content() { return data; }

    // 设置指定索引的值
    void set(const int& value) { data[index] = value; index = 0; }

    // 重载索引下标操作符
    Array& operator[](const int& index) {
        // 在这里修改子矩阵的nowAxis的值以及其他有必要的值，以返回一个子矩阵
        if (nowAxis == 0) this->index = 0;

        int stride = 1; // 计算轴 nowAxis 的步长
        for (int i = nowAxis + 1; i < axisNum; i++) stride *= shape[i];
        this->index += index * stride;

        nowAxis++;

        if (nowAxis == axisNum) nowAxis = 0;
        int temp = totalSize();
        if (this->index >= temp || this->index < 0) {
            this->index = 0; nowAxis = 0;
            printf("out of range!");
        }
        return *this;
    }

    // 赋值操作符重载
    Array& operator=(const int& data) {
        this->data[index] = data;
        index = 0;
        nowAxis = 0;
        return *this;
    }
    Array& operator=(const Array& a) {
        delete[] data;
        axisNum = a.axisNum;
        index = a.index;
        nowAxis = a.nowAxis;
        for (int i = 0; i < axisNum; i++) shape[i] = a.shape[i];

        int size = totalSize();
        data = new int[size] {};
        for (int i = 0; i < size; i++) data[i] = a.data[i];
        return *this;
    }

    // 算术操作符重载
    Array operator+(const Array& a) {
        int size = totalSize();
        Array result = *this;
        if (isCompatible(a))
            for (int i = 0; i < size; i++) result.data[i] = data[i] + a.data[i];
        return result;
    }
    Array operator+(const int& a) {
        int size = totalSize();
        Array result = *this;
        for (int i = 0; i < size; i++) result.data[i] = data[i] + a;
        return result;
    }
    Array operator-(const Array& a) {
        int size = totalSize();
        Array result = *this;
        if (isCompatible(a))
            for (int i = 0; i < size; i++) result.data[i] = data[i] - a.data[i];
        return result;
    }
    Array operator-(const int& a) {
        int size = totalSize();
        Array result = *this;
        for (int i = 0; i < size; i++) result.data[i] = data[i] - a;
        return result;
    }
    Array operator*(const Array& a) {
        int size = totalSize();
        Array result = *this;
        if (isCompatible(a))
            for (int i = 0; i < size; i++) result.data[i] = data[i] * a.data[i];
        return result;
    }
    Array operator*(const int& a) {
        int size = totalSize();
        Array result = *this;
        for (int i = 0; i < size; i++) result.data[i] = data[i] * a;
        return result;
    }
    Array operator/(const Array& a) {
        int size = totalSize();
        Array result = *this;
        if (isCompatible(a)) {
            for (int i = 0; i < size; i++) {
                if (a.data[i] == 0) {
                    printf("Division by zero!");
                    break;
                }
                result.data[i] = data[i] / a.data[i];
            }
        }
        return result;
    }
    Array operator/(const int& a) {
        if (a == 0) {
            printf("Division by zero!");
            return *this;
        }
        int size = totalSize();
        Array result = *this;
        for (int i = 0; i < size; i++) result.data[i] = data[i] / a;
        return result;
    }

    // 类型隐式转换操作符
    operator int() { return data[index]; }

    int* data;           // 数据指针
    int shape[16];    // 矩阵形状
    int axisNum;         // 维度

    int index;           // 当前索引
    int nowAxis;         // 当前操作轴
};

#endif