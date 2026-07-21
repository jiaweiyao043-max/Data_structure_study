// ---------------------------------------------------------
// 树的同构判断（Isomorphic Trees）
// 题目：两棵树若可以通过若干次"左右子树互换"变成彼此，则称为同构
// 输入：两棵树的结点信息，每行 [结点值 左孩子下标 右孩子下标]，- 表示空
// 输出：Yes / No
// 思路：
//   1. 数组下标模拟指针建树（用 set 找根 = 不在任何孩子位置上的下标）
//   2. 递归比较：四种情况：两空/一空一非空/值不同
//      值相同时既要试"不交换"，也要试"交换左右"两种匹配
// ---------------------------------------------------------

#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

// ---------------------------------------------------------
// 基础类型与树结点定义
// ---------------------------------------------------------
typedef char element;   // 结点值类型

struct TreeNode{
    element val;            // 结点值
    TreeNode* left;         // 左孩子
    TreeNode* right;        // 右孩子
    // 构造函数：初始化时左/右孩子为 nullptr
    TreeNode(element val): val(val),left(nullptr),right(nullptr){}
};

// ---------------------------------------------------------
// 根据输入数组建树，返回根结点
// 难点1：输入只给了"每个结点的孩子下标"，但没直接给根结点
// 难点2：结点值是字符，但孩子下标是字符串形式（如 "-", "0", "12"）
//       所以左右孩子数组用 string 而非 int
// 难点3：要先 new 出所有结点对象，再把它们之间用指针连起来
//       （因为指针赋值时需要对象已存在）
// ---------------------------------------------------------
TreeNode* buildTree(int n, vector<char>& val, vector<string>& left, vector<string>& right){
    if(n == 0) return nullptr;       // 空树直接返回

    // 第一步：先创建所有结点对象，存到 node 数组里（下标就是结点编号）
    vector<TreeNode*> node(n, nullptr);
    for(int i = 0; i < n; i++){
        node[i] = new TreeNode(val[i]);
    }

    // 第二步：把每个结点的左右孩子指针连上
    //   stoi 把 string 转 int（孩子下标是字符串形式）
    //   "-" 表示该孩子为空
    for(int i = 0; i < n; i++){
        if(left[i] != "-"){
            int l = stoi(left[i]);
            node[i]->left = node[l];
        }
        if(right[i] != "-"){
            int r = stoi(right[i]);
            node[i]->right = node[r];
        }
    }

    // 第三步：找根结点 —— 根的特点是"不在任何结点的孩子位置上"
    //   用 set 收集所有出现过的孩子下标，剩下的就是根
    set<int> children;
    for(int i = 0; i < n; i++){
        if(left[i] != "-")  children.insert(stoi(left[i]));
        if(right[i] != "-") children.insert(stoi(right[i]));
    }
    int rootIdx = 0;
    for(int i = 0; i < n; i++){
        if(children.find(i) == children.end()){
            rootIdx = i;     // 找到了：i 没在任何孩子位置出现过
            break;
        }
    }
    return node[rootIdx];
}

// ---------------------------------------------------------
// 递归判断两棵树是否同构
// 难点：判断同构时要同时考虑"交换左右"和"不交换"两种情况
//   因为树的对称性，左右互换后仍然算同构
// ---------------------------------------------------------
bool isIsomorphic(TreeNode* r1, TreeNode* r2) {
    // 情况 1：两棵树都为空 → 同构
    if (!r1 && !r2) return true;

    // 情况 2：只有一个为空 → 不同构
    if (!r1 || !r2) return false;

    // 情况 3：根结点值不同 → 不同构
    if (r1->val != r2->val) return false;

    // 情况 4：值相同，递归比较子树
    //   4a. 不交换左右：r1.left 配 r2.left，r1.right 配 r2.right
    //   4b. 交换左右：r1.left 配 r2.right，r1.right 配 r2.left
    //   任一成立即同构
    if (isIsomorphic(r1->left, r2->left) && isIsomorphic(r1->right, r2->right))
        return true;

    if (isIsomorphic(r1->left, r2->right) && isIsomorphic(r1->right, r2->left))
        return true;

    return false;
}

// ---------------------------------------------------------
// 主函数
// 难点：cin 读入时 val 是 char，left/right 是 string
//       像 "- " 这种必须用 string 读，char 读不到
// ---------------------------------------------------------
int main(){
    // 读入第一棵树
    int n1;
    cin >> n1;
    vector<char> val1(n1);
    vector<string> left1(n1), right1(n1);
    for (int i = 0; i < n1; i++) {
        cin >> val1[i] >> left1[i] >> right1[i];
    }

    // 读入第二棵树
    int n2;
    cin >> n2;
    vector<char> val2(n2);
    vector<string> left2(n2), right2(n2);
    for (int i = 0; i < n2; i++) {
        cin >> val2[i] >> left2[i] >> right2[i];
    }

    // 建树并判断
    TreeNode* root1 = buildTree(n1, val1, left1, right1);
    TreeNode* root2 = buildTree(n2, val2, left2, right2);
    cout << (isIsomorphic(root1, root2) ? "Yes" : "No") << endl;
    return 0;
}
