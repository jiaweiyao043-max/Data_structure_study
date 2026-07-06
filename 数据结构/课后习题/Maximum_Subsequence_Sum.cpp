#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
void MaxSubseqSum4(int List[], int N) {
    int i;
    int start, end, temp_start;
    start = end = temp_start = 0;
    int ThisSum = 0, MaxSum = -1;  // MaxSum 初始 -1，这样遇 0 也能更新起止下标
    for (i = 0; i < N; i++) {
        ThisSum += List[i];             // 向右累加
        if (ThisSum > MaxSum) {         // 发现更大的和
            MaxSum = ThisSum;
            start = temp_start;
            end = i;
        } else if (ThisSum < 0) {       // 当前和变负，抛弃前面的子列
            ThisSum = 0;
            temp_start = i+1;
        }
    }
    if(MaxSum >= 0){
        cout<<MaxSum<<" "<<List[start]<<" "<<List[end];   
    }
    else{
        cout<<0<<" "<<List[0]<<" "<<List[N-1];
    }
        
}

int main() {
    int List[100000];
    int x;
    cin >> x;
    for (int i = 0; i < x; i++) {
        cin >> List[i];
    }
    MaxSubseqSum4(List, x);
    return 0;
}
