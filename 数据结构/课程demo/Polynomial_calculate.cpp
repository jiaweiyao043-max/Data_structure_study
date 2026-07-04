// 给定一个多项式f(x)=a0 + a1*x^1 + a2*x^2 + ... + a_{n-1}*x^{n-1}，求解f(x)的值
#include <iostream>
#include <cmath>
#include <chrono>
#include <functional>
int MAXK = 1000;  // 重复运行次数，用于求平均耗时
// ---------------------------------------------------------
// evaluate: 计时函数，参数 func 是一个函数指针（用 std::function 包装）
// ---------------------------------------------------------
// std::function<double(int[], int, double)> 表示：
//   - 返回值类型: double
//   - 参数列表:   (int[], int, double)
// 它可以把任意符合此签名的函数（f1、f2、lambda 等）传进来，实现回调
// ---------------------------------------------------------
void evaluate(std::function<double(int[], int, double)> func,
              int arry[], int length, double x) {

    auto start_clock = std::chrono::high_resolution_clock::now();

    double result = 0;
    for (int i = 0; i < MAXK; i++) {
        result = func(arry, length, x);   // 调用传入的函数（f1 或 f2）
    }

    auto stop_clock = std::chrono::high_resolution_clock::now();

    // 计算单次平均耗时（纳秒）
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
                        stop_clock - start_clock) / MAXK;

    std::cout << "result = " << result
              << ", time = " << duration.count() << " ns" << std::endl;
}

// ---------------------------------------------------------
// f1: 逐项求幂法
// 直接计算每一项 a_i * x^i 再累加，每次循环调用 pow()
// 时间复杂度 O(n^2)（pow 内部非线性）
// ---------------------------------------------------------
double f1(int arry[], int length, double x) {
    double p1 = arry[0];                 // 常数项 a0
    for (int i = 1; i < length; i++) {
        p1 += arry[i] * pow(x, i);       // 累加 a_i * x^i
    }
    return p1;
}

// ---------------------------------------------------------
// f2: 秦九韶算法（Horner's method）
// 将多项式改写为: f(x) = a0 + x*(a1 + x*(a2 + ... + x*a_{n-1}))
// 从内向外逐层计算，每层只需一次乘法+一次加法
// 时间复杂度 O(n)
// ---------------------------------------------------------
double f2(int arry[], int length, double x) {
    double p2 = arry[length - 1];        // 从最高次项系数开始
    for (int i = length - 1; i > 0; i--) {
        p2 = arry[i - 1] + x * p2;       // a_{i-1} + x * (内层结果)
    }
    return p2;
}

int main() {
    // 多项式系数: 2 + 5x + 6x^2 + x^3 + 8x^4 + 9x^5 + 11x^6 + 67x^7 + 3x^8 + 9x^9
    int fx[] = {2, 5, 6, 1, 8, 9, 11, 67, 3, 9};

    evaluate(f1, fx, 10, 3);  // 把 f1 作为参数传入 evaluate
    evaluate(f2, fx, 10, 3);  // 把 f2 作为参数传入 evaluate

    return 0;
}
