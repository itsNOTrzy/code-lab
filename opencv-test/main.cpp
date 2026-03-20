#include <conio.h> //可能与 cout 冲突
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

const int MAXN = 100; //最大阶数
char choice;

int raw, col;

void wait_for_enter() {
    cout << "\n按回车键继续";
    while (_getch() != '\r');
    cout << "\n\n";
}
void inputRC() {
    cout << "输入矩阵行、列数(1-" << MAXN << "):";
    while (1) {
        cin >> raw >> col;
        if (cin.fail()) {
            cout << "输入错误，非整数！退出程序！";
            exit(0);
        }
        else if (raw >= 1 and raw <= MAXN
            and col >= 1 and col <= MAXN) {
            break;
        }
        cout << "超出范围，请重新输入:";
    }
}
void inputMatrix(int matrix[MAXN * MAXN]) {
    for (int i = 0; i < raw * col; ++i) {
        cin >> matrix[i];
        if (cin.fail()) {
            cout << "输入错误，非整数！退出程序！";
            exit(0);
        }
    }
}
void menu() {
    for (int i = 1; i <= 57; ++i) cout << "*";
    cout << "\n*       1 矩阵加法      2 矩阵数乘      3 矩阵转置      *";
    cout << "\n*       4 矩阵乘法      5 Hadamard乘积  6 矩阵卷积      *";
    cout << "\n*       7 卷积应用      8 OTSU算法      9 图像分割      *";
    cout << "\n*                       0 退出系统                      *\n";
    for (int i = 1; i <= 57; ++i) cout << "*";
    cout << "\n选择菜单项<0~9>:";        // 按要求输入菜单选择项choice
    cin >> choice;
}
void matriplus() {
    inputRC();

    cout << "输入矩阵 A 的数据:\n";
    int matrixA[MAXN * MAXN];
    inputMatrix(matrixA);

    cout << "输入矩阵 B 的数据:\n";
    int matrixB[MAXN * MAXN];
    inputMatrix(matrixB);

    cout << "二者之和为:\n";
    for (int i = 0; i < raw; ++i) {
        for (int j = 0; j < col; ++j) {
            cout << matrixA[i * col + j] + matrixB[i * col + j] << ' ';
        }
        cout << endl;
    }
    wait_for_enter();
}
void nummulti() {
    inputRC();

    cout << "输入矩阵的数据:\n";
    int matrix[MAXN * MAXN];
    inputMatrix(matrix);

    cout << "输入整数:";
    int k;
    cin >> k;
    if (cin.fail()) {
        cout << "输入错误，非整数！退出程序！";
        exit(0);
    }

    cout << "数乘结果为:\n";
    for (int i = 0; i < raw; ++i) {
        for (int j = 0; j < col; ++j) {
            cout << k * matrix[i * col + j] << ' ';
        }
        cout << endl;
    }
    wait_for_enter();
}
void matritrans() {
    inputRC();

    cout << "输入矩阵的数据:\n";
    int matrix[MAXN * MAXN];
    inputMatrix(matrix);

    cout << "其转置为:\n";
    for (int j = 0; j < col; ++j) {
        for (int i = 0; i < raw; ++i) {
            cout << matrix[i * col + j] << ' ';
        }
        cout << endl;
    }
    wait_for_enter();
}
void matrimulti() {
    inputRC();

    cout << "输入矩阵 A 的数据:\n";
    int matrixA[MAXN * MAXN];
    inputMatrix(matrixA);

    cout << "输入矩阵 B 的列数(1-" << MAXN << "):";
    int B_col;
    while (1) {
        cin >> B_col;
        if (cin.fail()) {
            cout << "输入错误，非整数！退出程序！";
            exit(0);
        }
        else if (B_col >= 1 and B_col <= MAXN) {
            break;
        }
        cout << "超出范围，请重新输入:";
    }

    cout << "输入矩阵 B 的数据:\n";
    int matrixB[MAXN * MAXN];
    for (int i = 0; i < col * B_col; ++i) {
        cin >> matrixB[i];
        if (cin.fail()) {
            cout << "输入错误，非整数！退出程序！";
            exit(0);
        }
    }

    int sum = 0;
    cout << "乘积为:\n";
    for (int i = 0; i < raw; ++i) {
        for (int j = 0; j < B_col; ++j) {
            for (int z = 0; z < col; ++z) {
                sum += matrixA[i * col + z] * matrixB[z * B_col + j];
            }
            cout << sum << ' ';
            sum = 0;
        }
        cout << endl;
    }
    wait_for_enter();
}
void hadamulti() {
    inputRC();

    cout << "输入矩阵 A 的数据:\n";
    int matrixA[MAXN * MAXN];
    inputMatrix(matrixA);

    cout << "输入矩阵 B 的数据:\n";
    int matrixB[MAXN * MAXN];
    inputMatrix(matrixB);

    cout << "二者的 Hadamard 乘积为:\n";
    for (int i = 0; i < raw; ++i) {
        for (int j = 0; j < col; ++j) {
            cout << matrixA[i * col + j] * matrixB[i * col + j] << ' ';
        }
        cout << endl;
    }
    wait_for_enter();
}
void conv() {
    inputRC();

    cout << "输入矩阵的数据:\n";
    int matrix[MAXN * MAXN];
    inputMatrix(matrix);

    cout << "输入 3x3 核矩阵的数据:\n";
    int kernel[9];
    for (int i = 0; i < 9; ++i) {
        cin >> kernel[i];
    }

    int result[MAXN * MAXN]{};
    for (int x = 0; x < raw; ++x) {
        for (int y = 0; y < col; ++y) { // 遍历卷积核
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    int nx = x + i;
                    int ny = y + j;
                    if (nx >= 0 && nx < raw && ny >= 0 && ny < col) { // 检查边界，处理边界外为0的情况
                        result[x * col + y] += matrix[nx * col + ny] * kernel[(i + 1) * 3 + (j + 1)];
                    }
                }
            }
        }
    }

    cout << "卷积结果为:\n";
    for (int i = 0; i < raw; ++i) {
        for (int j = 0; j < col; ++j) {
            cout << result[i * col + j] << " ";
        }
        cout << endl;
    }
    wait_for_enter();
}
void demo() {
    int B[54]{ 1, 1, 1, 1, 1, 1, 1, 1, 1,
             -1, -2, -1, 0, 0, 0, 1, 2, 1,
             -1, 0, 1, -2, 0, 2, -1, 0, 1,
             -1, -1, -1, -1, 9, -1, -1, -1, -1,
             -1, -1, 0, -1, 0, 1, 0, 1, 1,
             1, 2, 1, 2, 4, 2, 1, 2, 1 },
        kernel[9];

    Mat image = imread(".//image//demolena.jpg"); // 图像的灰度值存放在格式为Mat的变量image中
    namedWindow("Image-original", WINDOW_NORMAL);
    imshow("Image-original", image);

    int matrix[256 * 256];
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            matrix[i * 256 + j] = image.ptr(i, j)[0];
        }
    }

    for (int b = 0; b < 6; ++b) {
        int kernel_sum = 0; //求卷积核的和
        for (int k = 0; k < 9; ++k) {
            kernel[k] = B[b * 9 + k];
            kernel_sum += kernel[k];
        }

        int result[256 * 256]{};
        for (int x = 0; x < 256; ++x) {
            for (int y = 0; y < 256; ++y) {
                for (int i = -1; i <= 1; ++i) {
                    for (int j = -1; j <= 1; ++j) {
                        int nx = x + i;
                        int ny = y + j;
                        if (nx >= 0 && nx < 256 && ny >= 0 && ny < 256) {
                            result[x * 256 + y] += matrix[nx * 256 + ny] * kernel[(i + 1) * 3 + (j + 1)];
                        }
                    }
                }
                if (kernel_sum != 0) {
                    result[x * 256 + y] /= kernel_sum;
                }
                if (b == 1 or b == 2 or b == 4) {
                    result[x * 256 + y] += 128;    // 对亮度过低的可以加偏移量
                }
                if (result[x * 256 + y] > 255) {
                    result[x * 256 + y] = 255;
                }
                else if (result[x * 256 + y] < 0) {
                    result[x * 256 + y] = 0;
                }
            }
        }

        for (int i = 0; i < 256; ++i) {
            for (int j = 0; j < 256; ++j) {
                image.ptr(i, j)[0] = image.ptr(i, j)[1] = image.ptr(i, j)[2] = result[i * 256 + j];
            }
        }
        string name = "B" + to_string(b + 1);
        namedWindow(name, WINDOW_NORMAL);
        imshow(name, image);
    }
    if (waitKey(30000)) destroyAllWindows();
}
void OTSU() {
    Mat image = imread(".//image//demolena.jpg");
    namedWindow("Image-original", WINDOW_NORMAL);
    imshow("Image-original", image);

    int threshold = 0; //灰度值阈值

    int sumB = 0;
    int wB = 0;
    int wF = 0;
    double mB;
    double mF; //各自均值
    double varMax = 0; //最大方差
    double varBetween; //类间方差

    int histogram[256]{};     //灰度值直方图
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            histogram[image.ptr(i, j)[0]]++;
        }
    }

    int sum = 0;
    for (int i = 1; i < 256; ++i) {
        sum += i * histogram[i]; //各像素灰度值总和
    }

    for (int i = 0; i < 256; ++i) {
        wB += histogram[i];
        if (wB == 0) continue; //为零导致方差为零，不是最大的
        wF = 256 * 256 - wB;
        if (wF == 0) break; //说明已经完成最大值查找
        sumB += i * histogram[i];
        mB = (double)sumB / wB;
        mF = ((double)sum - (double)sumB) / wF;
        varBetween = wB * wF * (mB - mF) * (mB - mF);
        if (varBetween > varMax) {
            varMax = varBetween;  //更新最大方差与阈值
            threshold = i;
        }
    }
    //二值化
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            image.ptr(i, j)[0] = image.ptr(i, j)[0] > threshold ? 255 : 0;
            image.ptr(i, j)[1] = image.ptr(i, j)[1] > threshold ? 255 : 0;
            image.ptr(i, j)[2] = image.ptr(i, j)[2] > threshold ? 255 : 0;
        }
    }

    namedWindow("lena", WINDOW_NORMAL);
    imshow("lena", image);
    if (waitKey(30000)) destroyAllWindows();
}
void seg() {
    string path[4] = { "snowball","polyhedrosis","ship","brain" };
    for (int imageN = 0; imageN < 4; ++imageN) {
        Mat image = imread(".//image//" + path[imageN] + ".jpg"); // 原图
        string name = "ORIGIN_IMAGE_" + to_string(imageN + 1);
        namedWindow(name, WINDOW_NORMAL);
        imshow(name, image);

        int threshold[3]{};
        for (int n = 0; n < 3; ++n) {
            int sumB = 0;
            int wB = 0;
            int wF = 0;
            double mB;
            double mF;
            double varMax = 0;
            double varBetween;
            int histogram[256]{};
            for (int i = 0; i < image.rows; ++i) {
                for (int j = 0; j < image.cols; ++j) {
                    histogram[image.ptr(i, j)[n]]++;
                }
            }
            int sum = 0;
            for (int i = 1; i < 256; ++i) {
                sum += i * histogram[i];
            }
            for (int i = 0; i < 256; ++i) {
                wB += histogram[i];
                if (wB == 0) continue;
                wF = image.rows * image.cols - wB;
                if (wF == 0) break;
                sumB += i * histogram[i];
                mB = (double)sumB / wB;
                mF = ((double)sum - (double)sumB) / wF;
                varBetween = wB * wF * (mB - mF) * (mB - mF);
                if (varBetween > varMax) {
                    varMax = varBetween;
                    threshold[n] = i;
                }
            }
        }
        //抠图，按逻辑运算符
        for (int i = 0; i < image.rows; ++i) {
            for (int j = 0; j < image.cols; ++j) {
                if (image.ptr(i, j)[0] < threshold[0] and image.ptr(i, j)[1] < threshold[1] and image.ptr(i, j)[2] < threshold[2])
                    image.ptr(i, j)[0] = image.ptr(i, j)[1] = image.ptr(i, j)[2] = 0;
            }
        }

        string result_name = "RESULT_" + to_string(imageN + 1);
        namedWindow(result_name, WINDOW_NORMAL);
        imshow(result_name, image);
    }
    if (waitKey(30000)) destroyAllWindows();
}

int main() {
    wait_for_enter();
    while (true) { // 注意该循环退出的条件
        system("cls"); // 清屏
        menu(); // 菜单
        if (choice == '0') { // 选择退出
            cout << "\n 确定退出吗? (y/n):";
            cin >> choice;
            if (choice == 'y' || choice == 'Y')
                break;
            else
                continue;
        }
        switch (choice) {
        case '1':
            matriplus();
            break;
        case '2':
            nummulti();
            break;
        case '3':
            matritrans();
            break;
        case '4':
            matrimulti();
            break;
        case '5':
            hadamulti();
            break;
        case '6':
            conv();
            break;
        case '7':
            demo();
            break;
        case '8':
            OTSU();
            break;
        case '9':
            seg();
            break;
        default:
            cout << "\n 输入错误，请重新输入\n";
            wait_for_enter();
        }
    }
    return 0;
}