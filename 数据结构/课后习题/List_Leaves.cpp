// ---------------------------------------------------------
// 列出二叉树的所有叶子结点（List Leaves）
// 题目：给定一棵二叉树，按"从上到下、从左到右"的顺序输出所有叶子结点的下标
// 输入：N（结点数） + N 行 [左孩子下标 右孩子下标]，- 表示空
// 输出：所有叶子下标，空格分隔，结尾无空格
// 关键：必须用层序遍历（BFS）才能保证"自顶向下、自左向右"顺序
// ---------------------------------------------------------

#include<iostream>
#include<string>
#include<vector>
#include<queue>
using namespace std;

// 树结点（下标本身就是结点编号，所以不存 value 字段）
struct TreeNode{
    int idx;                  // 结点下标（即题目给的编号）
    TreeNode* left;           // 左孩子
    TreeNode* right;          // 右孩子
    bool hasParents;          // 是否有父结点（用于找根）
    TreeNode(int i): idx(i), left(nullptr), right(nullptr), hasParents(false){}
};

// ---------------------------------------------------------
// 找根结点：根的特征是"没有父结点"
// 从 0..n-1 中找第一个 hasParents == false 的
// ---------------------------------------------------------
int findRoot(const vector<TreeNode*>& nodes){
    for(int i = 0; i < (int)nodes.size(); i++){
        if(!nodes[i]->hasParents){
            return i;
        }
    }
    return -1;   // 没找到（理论上不会发生，除非树为空）
}

// ---------------------------------------------------------
// 层序遍历（BFS），收集所有叶子结点下标
// 用 queue 实现"自顶向下、自左向右"的访问顺序
// ---------------------------------------------------------
void collectLeavesBFS(TreeNode* root, vector<int>& leaves){
    if(root == nullptr) return;          // 空树直接返回

    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()){
        TreeNode* cur = q.front();
        q.pop();

        // 叶子判定：左右孩子都为空
        if(cur->left == nullptr && cur->right == nullptr){
            leaves.push_back(cur->idx);
        }
        // 先左后右入队，保证自左向右的访问顺序
        if(cur->left)  q.push(cur->left);
        if(cur->right) q.push(cur->right);
    }
}

// ---------------------------------------------------------
// 释放 new 出来的所有结点
// ---------------------------------------------------------
void freeTree(vector<TreeNode*>& nodes){
    for(auto p : nodes) delete p;
}

int main(){
    int n;
    cin >> n;

    // 边界：空树直接输出空行
    if(n == 0){
        return 0;
    }

    // 第一步：创建所有结点对象
    vector<TreeNode*> nodes(n, nullptr);
    for(int i = 0; i < n; i++){
        nodes[i] = new TreeNode(i);
    }

    // 第二步：连孩子指针，并标记"有父结点"
    for(int i = 0; i < n; i++){
        string l, r;
        cin >> l >> r;
        if(l != "-"){
            int li = stoi(l);
            nodes[i]->left = nodes[li];
            nodes[li]->hasParents = true;
        }
        if(r != "-"){
            int ri = stoi(r);
            nodes[i]->right = nodes[ri];   // 原代码这里写成了 nodes[i]->left = ...，是 bug
            nodes[ri]->hasParents = true;
        }
    }

    // 第三步：找根并层序收集叶子
    int rootIdx = findRoot(nodes);
    vector<int> leaves;
    if(rootIdx >= 0){
        collectLeavesBFS(nodes[rootIdx], leaves);
    }

    // 第四步：输出，元素间一个空格，结尾无空格
    for(int i = 0; i < (int)leaves.size(); i++){
        if(i > 0) cout << " ";
        cout << leaves[i];
    }
    cout << endl;

    // 第五步：释放内存
    freeTree(nodes);
    return 0;
}
