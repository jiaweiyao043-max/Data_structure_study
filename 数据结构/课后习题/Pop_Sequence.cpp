// Pop Sequence（出栈顺序合法性判断）
// 题目：给定栈的最大容量 M、元素个数 N、待判定的序列数 K
//       入栈顺序固定为 1, 2, 3, ..., N
//       判断每个给定序列是否可能是合法的出栈序列
//
// 思路：模拟入栈过程，按 1..N 顺序入栈，每入一个就尝试"贪婪弹出"
//      即只要栈顶 == 当前序列期望值 seq[curr] 就弹出，curr++
//      最终若栈空且 curr == N，则该序列合法
//
// 输入：M N K
//       接下来 K 行，每行 N 个整数表示一个待判定序列
// 输出：每行 "YES" 或 "NO"

#include<iostream>
#include<vector>
#include<stack>
using namespace std;

int main(){
    int M, N, K;
    cin>>M>>N>>K; // M: 栈最大容量  N: 元素个数  K: 待判定序列数
    while(K--){
        int curr = 0;          // 当前期望弹出的序列下标 seq[curr]
        bool flag = true;      // 是否未超过栈容量 M
        vector<int> seq(N);    // 存放待判定序列
        for(int i = 0; i < N; i++){
            cin>>seq[i];
        }

        stack<int> st;          // 模拟栈
        // 按 1, 2, ..., N 顺序入栈
        for(int num = 1; num <= N; num++){
            st.push(num);
            // 容量检查：超过 M 即非法，标记并提前结束
            if ((int)st.size() > M) {
                flag = false;
                break;
            }
            // 贪婪弹出：栈顶 == 期望值就弹出，并推进 curr
            // 这里循环处理是因为弹出后可能新的栈顶仍然匹配
            while(curr != N && !st.empty() && st.top() == seq[curr]){
                    st.pop();
                    curr++;
            }
        }

        // 合法条件：未超容 && 所有元素都被成功弹出（curr == N 表示序列全部匹配完）
        if (flag && curr == N) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
