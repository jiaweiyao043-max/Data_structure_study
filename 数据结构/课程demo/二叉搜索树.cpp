#include<iostream>
using namespace std;

// 二叉搜索树节点
struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x):val(x), left(nullptr), right(nullptr){}
};

class BST{
private:
    TreeNode* root;

    // 递归插入：val 小于当前节点则向左，大于则向右，等于则忽略（不允许重复）
    TreeNode* InsertHelper(TreeNode* node, int val){
        if(node == nullptr){
            return new TreeNode(val); // 找到插入位置，创建新节点
        }
        if(val < node->val){
            node->left = InsertHelper(node->left, val);
        }
        else if(val > node->val){   // 用 else if：val 不可能同时满足两个分支
            node->right = InsertHelper(node->right, val);
        }
        // val == node->val：重复值不插入，直接返回
        return node;
    }

    // 找到以 node 为根的子树中的最小节点（一路向左）
    TreeNode* findMin(TreeNode* node){
        while(node && node->left){
            node = node->left;
        }
        return node;
    }

    // 递归删除值为 val 的节点，返回删除后的子树根节点
    TreeNode* DeleteHelper(TreeNode* node, int val){
        if(node == nullptr) return nullptr; // 未找到目标值

        if(val < node->val){
            // 目标在左子树，递归删除，并将新的左子树根挂回
            node->left = DeleteHelper(node->left, val);
        }
        else if(val > node->val){
            // 目标在右子树，递归删除，并将新的右子树根挂回
            node->right = DeleteHelper(node->right, val);
        }
        else{
            // 找到了目标节点，分三种情况处理

            // 情况1：无左子树，直接用右子树替代当前节点
            if(node->left == nullptr){
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            // 情况2：无右子树，直接用左子树替代当前节点
            else if(node->right == nullptr){
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            // 情况3：有两个子节点
            // 策略：用右子树最小节点（中序后继）的值覆盖当前节点，
            //       再从右子树中删除该后继节点
            else{
                TreeNode* minNode = findMin(node->right); // 找右子树最小节点
                node->val = minNode->val;                 // 覆盖当前节点值
                node->right = DeleteHelper(node->right, minNode->val); // 删除后继
            }
        }
        return node;
    }

    // 后序遍历释放所有节点（先释放子树，再释放自身）
    void Destroy(TreeNode* node){
        if(node == nullptr) return;
        Destroy(node->left);
        Destroy(node->right);
        delete node;
    }

    // 中序遍历打印（BST 中序遍历结果为升序）
    void inorderHelper(TreeNode* node){
        if(node == nullptr) return;
        inorderHelper(node->left);
        cout << node->val << " ";
        inorderHelper(node->right);
    }

public:
    BST():root(nullptr){}

    // 析构函数：释放所有节点，防止内存泄漏
    ~BST(){
        Destroy(root);
    }

    void Insert(int val){
        root = InsertHelper(root, val);
    }

    // 删除值为 val 的节点；必须将返回值赋回 root，以处理删除根节点的情况
    void Remove(int val){
        root = DeleteHelper(root, val); // Bug 修复：原代码丢弃了返回值
    }

    // 销毁整棵树并将 root 置空，避免悬空指针
    void DestroyBST(){
        Destroy(root);
        root = nullptr; // Bug 修复：原代码未置 nullptr，后续 Print 会访问野指针
    }

    // 中序打印，末尾换行
    void Print(){
        inorderHelper(root);
        cout << endl;
    }
};

int main(){
    BST bst;
    int arry[5] = {1, 67, 32, 10, 7};
    for(int i = 0; i < 5; i++){
        bst.Insert(arry[i]);
    }
    bst.Print();        // 中序输出：1 7 10 32 67
    bst.Remove(67);
    bst.Print();        // 删除 67 后：1 7 10 32
    bst.DestroyBST();
    bst.Print();        // 树已销毁，输出空行
    return 0;
}
