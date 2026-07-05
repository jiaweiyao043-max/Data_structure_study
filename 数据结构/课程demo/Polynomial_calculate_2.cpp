// f(x) = 1 + x/1 + x^2/2 + x^3/3 + ... + x^100/100，求解 f(1.1) 的值
// 系数规律：a_0 = 1, a_i = 1/i (i=1,2,...,100)

#include <iostream>
#include <cmath>
#include <chrono>
#include <functional>

int MAXK = 1e7;  // 重复运行 1e7 次求平均耗时

// ---------------------------------------------------------
// evaluate: 计时函数，std::function<double(double)> 表示：
//   - 返回值: double
//   - 参数:   一个 double
// ---------------------------------------------------------
void evaluate(std::function<double(double)> func, double x) {
    auto start_clock = std::chrono::high_resolution_clock::now();

    double result = 0;
    for (int i = 0; i < MAXK; i++) {
        result = func(x);               // 调用传入的函数（f1 或 f2）
    }

    auto stop_clock = std::chrono::high_resolution_clock::now();

    // 单次平均耗时（纳秒）
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
                        stop_clock - start_clock) / MAXK;

    std::cout << "result = " << result
              << ", time = " << duration.count() << " ns" << std::endl;
}

// ---------------------------------------------------------
// f1: 逐项求幂法
// 直接计算每一项 x^i / i 再累加，每轮循环调用 pow()
// ---------------------------------------------------------
double f1(double x) {
    double p1 = 1;                      // a_0 = 1
    for (int i = 1; i <= 100; i++) {
        p1 += pow(x, i) / i;            // 累加 x^i / i
    }
    return p1;
}

// ---------------------------------------------------------
// f2: 秦九韶算法（Horner's method）
// 将多项式改写为嵌套形式：1 + x*(1 + x*(1/2 + x*(... + x*(1/100))))
// 从最高次项 a_100 开始，逐层向外计算
// ---------------------------------------------------------
double f2(double x) {
    double p2 = 1.0 / 100;              // a_100 = 1/100，最内层
    for (int i = 99; i >= 1; i--) {     // a_99 到 a_1，系数为 1/i
        p2 = 1.0 / i + x * p2;          // 乘 x 后加上当前系数
    }
    p2 = 1 + x * p2;                    // a_0 = 1，最外层（单独处理避免除零）
    return p2;
}

int main() {
    evaluate(f1, 1.1);
    evaluate(f2, 1.1);
    return 0;
}
