// 一元多项式的乘法与加法运算（链表实现，带头结点）
// 输入格式：每行第一个数为项数 n，后面 n 对 (系数, 指数)，指数递降
// 例如: 4 3 4 -5 2 6 1 -2 0  表示 3x^4 - 5x^2 + 6x - 2

#include <iostream>
using namespace std;

// ---------------------------------------------------------
// 多项式结点
// ---------------------------------------------------------
typedef struct PolyNode *Polynomial;
struct PolyNode {
    int coef;      // 系数
    int expon;     // 指数
    Polynomial next;
};

// 创建空的头结点（coef 和 expon 无实际意义，仅用作链表头）
Polynomial CreatPolyNode() {
    Polynomial head = new PolyNode;
    head->coef = 0;
    head->expon = 0;
    head->next = nullptr;
    return head;
}

// ---------------------------------------------------------
// 从标准输入读取一个多项式（带头结点返回）
// ---------------------------------------------------------
Polynomial ReadPoly() {
    Polynomial head = CreatPolyNode();
    Polynomial tail = head;          // tail 始终指向链表最后一个结点
    int n;
    cin >> n;                        // 读入项数
    for (int i = 0; i < n; i++) {
        int coef, expon;
        cin >> coef >> expon;
        Polynomial NewNode = CreatPolyNode();
        NewNode->coef = coef;
        NewNode->expon = expon;
        NewNode->next = nullptr;
        tail->next = NewNode;        // 尾插法
        tail = NewNode;
    }
    return head;
}

// （备用）从数组读取多项式，用于本地调试，arry[0] 为项数
Polynomial ReadPoly2(int arry[]) {
    Polynomial head = CreatPolyNode();
    Polynomial tail = head;
    for (int i = 1; i < arry[0] * 2; i += 2) {
        Polynomial NewNode = CreatPolyNode();
        NewNode->coef = arry[i];
        NewNode->expon = arry[i + 1];
        NewNode->next = nullptr;
        tail->next = NewNode;
        tail = NewNode;
    }
    return head;
}

// ---------------------------------------------------------
// 输出多项式，指数递降
// 零多项式输出 "0 0"，结尾无多余空格
// ---------------------------------------------------------
void PrintPolyNode(Polynomial head) {
    Polynomial p = head->next;
    if (p == nullptr) {              // 零多项式
        cout << "0 0";
        return;
    }
    bool first = true;
    while (p != nullptr) {
        if (!first) cout << " ";     // 项与项之间的分隔空格
        cout << p->coef << " " << p->expon;
        first = false;
        p = p->next;
    }
}

// ---------------------------------------------------------
// 按指数递降顺序将 (coef, expon) 插入结果链表
// - 指数相同时合并系数（系数为 0 则删除该结点）
// - 指数不同时插入新结点到正确位置
// ---------------------------------------------------------
void InsertPolyNode(Polynomial ResultNode, int coef, int expon) {
    Polynomial Prev = ResultNode;         // Prev 始终在 Curr 前一个位置
    Polynomial Curr = ResultNode->next;

    if (coef == 0) return;               // 系数为 0，直接忽略

    // 找到第一个指数 <= expon 的位置
    while (Curr != nullptr && expon < Curr->expon) {
        Prev = Curr;
        Curr = Curr->next;
    }

    if (Curr != nullptr && expon == Curr->expon) {
        // 指数相同：合并系数
        Curr->coef += coef;
        if (Curr->coef == 0) {           // 合并后系数为 0，删除该结点
            Prev->next = Curr->next;
            delete Curr;
        }
        return;
    } else {
        // 指数不同：在 Prev 和 Curr 之间插入新结点
        Polynomial NewNode = CreatPolyNode();
        NewNode->coef = coef;
        NewNode->expon = expon;
        NewNode->next = Curr;
        Prev->next = NewNode;
    }
}

// ---------------------------------------------------------
// 多项式乘法：P1 每一项 × P2 每一项，结果插入到新链表
// ---------------------------------------------------------
Polynomial Mult(Polynomial PolyNode1, Polynomial PolyNode2) {
    Polynomial result = CreatPolyNode();       // 结果链表（头结点）
    Polynomial p1 = PolyNode1->next;
    while (p1 != nullptr) {
        Polynomial p2 = PolyNode2->next;
        while (p2 != nullptr) {
            int coef = p1->coef * p2->coef;    // 系数相乘
            int expon = p1->expon + p2->expon; // 指数相加
            InsertPolyNode(result, coef, expon);
            p2 = p2->next;
        }
        p1 = p1->next;
    }
    return result;
}

// ---------------------------------------------------------
// 多项式加法：把两个多项式的所有项依次插入到新链表
// ---------------------------------------------------------
Polynomial Add(Polynomial PolyNode1, Polynomial PolyNode2) {
    Polynomial p1 = PolyNode1->next;
    Polynomial p2 = PolyNode2->next;
    Polynomial result = CreatPolyNode();       // 结果链表（头结点）

    while (p1 != nullptr) {
        InsertPolyNode(result, p1->coef, p1->expon);
        p1 = p1->next;
    }
    while (p2 != nullptr) {
        InsertPolyNode(result, p2->coef, p2->expon);
        p2 = p2->next;
    }
    return result;
}

int main() {
    Polynomial P1 = ReadPoly();
    Polynomial P2 = ReadPoly();

    Polynomial prod = Mult(P1, P2);   // 乘积
    Polynomial sum  = Add(P1, P2);    // 和

    PrintPolyNode(prod);
    cout << endl;
    PrintPolyNode(sum);

    return 0;
}
