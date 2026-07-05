// 最大子列和问题：给定一个整数序列，求连续子列的最大和
#include <iostream>
#include <algorithm>
using namespace std;

// ---------------------------------------------------------
// 算法1: 暴力枚举 O(n^3)
// 枚举所有子列的起点 i 和终点 j，再循环求和
// ---------------------------------------------------------
int MaxSubseqSum1(int List[], int N) {
    int i, j, k;
    int ThisSum, MaxSum = 0;
    for (i = 0; i < N; i++) {           // 子列起点
        for (j = 0; j < N; j++) {       // 子列终点
            ThisSum = 0;
            for (k = i; k <= j; k++) {  // 求和 List[i..j]
                ThisSum += List[k];
                if (ThisSum > MaxSum)
                    MaxSum = ThisSum;
            }
        }
    }
    return MaxSum;
}

// ---------------------------------------------------------
// 算法2: 优化枚举 O(n^2)
// 固定起点 i 后向右扩展，累加时直接复用上次的结果
// ---------------------------------------------------------
int MaxSubseqSum2(int List[], int N) {
    int i, j;
    int ThisSum, MaxSum = 0;
    for (i = 0; i < N; i++) {           // 子列起点
        ThisSum = 0;
        for (j = i; j < N; j++) {       // 从 i 开始向右逐个累加
            ThisSum += List[j];
            if (ThisSum > MaxSum)
                MaxSum = ThisSum;
        }
    }
    return MaxSum;
}

// 返回三个数中的最大值（C++11 标准库 max({...})）
int Max3(int A, int B, int C) {
    return max({A, B, C});
}

// ---------------------------------------------------------
// 分治法核心递归 O(n log n)
// 最大子列和要么在左半边、右半边、要么跨越中间
// ---------------------------------------------------------
int DivideAndConquer(int List[], int left, int right) {
    int MaxLeftSum, MaxRightSum;
    int MaxLeftBoarderSum, MaxRightBoarderSum;
    int LeftBoarderSum, RightBoarderSum;
    int Center, i;

    if (left == right) {                // 递归终止：只有一个元素
        if (List[left] > 0) return List[left];
        else return 0;                  // 全负数则最大和为 0
    }

    Center = (left + right) / 2;

    // 递归求左、右半部分的最大子列和
    MaxLeftSum = DivideAndConquer(List, left, Center);
    MaxRightSum = DivideAndConquer(List, Center + 1, right);

    // 求跨中线向左扫描的最大和
    MaxLeftBoarderSum = 0; LeftBoarderSum = 0;
    for (i = Center; i >= left; i--) {
        LeftBoarderSum += List[i];
        if (LeftBoarderSum > MaxLeftBoarderSum)
            MaxLeftBoarderSum = LeftBoarderSum;
    }

    // 求跨中线向右扫描的最大和
    MaxRightBoarderSum = 0; RightBoarderSum = 0;
    for (i = Center + 1; i <= right; i++) {
        RightBoarderSum += List[i];
        if (RightBoarderSum > MaxRightBoarderSum)
            MaxRightBoarderSum = RightBoarderSum;
    }

    // 返回三者最大值：左 | 右 | 跨中线
    return Max3(MaxLeftSum, MaxRightSum,
                MaxLeftBoarderSum + MaxRightBoarderSum);
}

int MaxSubseqSum3(int List[], int N) {
    return DivideAndConquer(List, 0, N - 1);
}

// ---------------------------------------------------------
// 算法4: 在线处理（贪心）O(n)
// 累加当前和，若变负数则直接抛弃重新开始
// ---------------------------------------------------------
int MaxSubseqSum4(int List[], int N) {
    int i;
    int ThisSum, MaxSum;
    ThisSum = MaxSum = 0;
    for (i = 0; i < N; i++) {
        ThisSum += List[i];             // 向右累加
        if (ThisSum > MaxSum) {         // 发现更大的和
            MaxSum = ThisSum;
        } else if (ThisSum < 0) {       // 当前和变负，抛弃前面的子列
            ThisSum = 0;
        }
    }
    return MaxSum;
}

int main() {
    int List[100000];
    int x;
    cin >> x;
    for (int i = 0; i < x; i++) {
        cin >> List[i];
    }
    // int result = MaxSubseqSum1(List, x);
    // int result = MaxSubseqSum2(List, x);
    // int result = MaxSubseqSum3(List, x);
    int result = MaxSubseqSum4(List, x);
    cout << result;
    return 0;
}
