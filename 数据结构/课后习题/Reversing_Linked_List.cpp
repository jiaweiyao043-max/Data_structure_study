// 反转链表：给定一个单链表，每 K 个结点反转一次，不足 K 个不反转
// 输入：第一行 head地址 N(结点数) K(反转长度)
//       接下来 N 行：地址 数据 下一跳地址

#include <iostream>
using namespace std;

#define MAXSIZE 100001    // 地址是 5 位数，最大 99999

int main() {
    // 数组模拟链表：直接用地址当下标
    int Data[MAXSIZE];    // Data[地址] = 结点值
    int Link[MAXSIZE];    // Link[地址] = 下一跳地址

    int head, N, K;
    cin >> head >> N >> K;

    // 读入 N 个结点（输入顺序可能是乱的）
    for (int i = 0; i < N; i++) {
        int Address, data, Next;
        cin >> Address >> data >> Next;
        Data[Address] = data;
        Link[Address] = Next;
    }

    // 顺着链收集地址，排成实际顺序
    int count = 0;
    int SortList[MAXSIZE];          // SortList[i] = 链表中第 i 个结点的地址
    while (head != -1) {
        SortList[count] = head;     // 记下当前结点地址
        head = Link[head];          // 沿链走到下一个
        count++;
    }

    // 每 K 个结点反转一次（不足 K 个的尾部不动）
    for (int i = 0; i < count - (count % K); i += K) {
        for (int j = 0; j < K / 2; j++) {
            // 组内首尾对称交换
            int t = SortList[i + j];
            SortList[i + j] = SortList[i + K - j - 1];
            SortList[i + K - j - 1] = t;
        }
    }

    // 输出：地址(5位补零) 数据 下一跳地址(5位补零)
    for (int i = 0; i < count - 1; i++)
        printf("%05d %d %05d\n",
               SortList[i], Data[SortList[i]], SortList[i + 1]);

    // 最后一个结点，下一跳地址固定为 -1
    printf("%05d %d -1\n",
           SortList[count - 1], Data[SortList[count - 1]]);

    return 0;
}
