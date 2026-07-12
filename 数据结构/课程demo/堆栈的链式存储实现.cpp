#include <iostream>
using namespace std;

// ---------------------------------------------------------
// 栈的链式存储实现（带头结点的链表模拟栈，LIFO 后进先出）
// 链栈特点：栈顶在链表头部，无需预先分配容量，不会"栈满"
// ---------------------------------------------------------

// 链栈结点
template<typename T>
struct Node
{
    T Data;             // 结点数据
    Node<T> *Next;      // 下一跳指针
    Node(T value):Data(value),Next(nullptr){}   // 构造函数
};

template<typename T>
class ListStack{
private:
    Node<T> *top;      // 栈顶指针，指向链表第一个结点（top == nullptr 表示空栈）
    int count;         // 栈中元素个数

public:
    // 构造函数：初始化空栈
    ListStack(){
        top = nullptr;
        count = 0;
    }

    // 析构函数：逐个 pop 释放所有结点，避免内存泄漏
    ~ListStack(){
        clear();
    }

    // 入栈：newNode 的 Next 指向当前 top，再让 top 指向 newNode
    // 即"头插法"，新结点总是成为新的栈顶
    void push(T value){
        Node<T> *newNode = new Node<T>(value);
        newNode->Next = top;    // 新结点指向原栈顶
        top = newNode;          // top 更新为新结点
        count++;
    }

    // 出栈：保存 top 指针，top 下移到 Next，再 delete 原 top
    bool pop(){
        if(isEmpty()){
            return false;
        }
        else{
            Node<T> *tempNode = top;    // 暂存待删除结点
            top = top->Next;            // top 指针下移
            delete tempNode;            // 释放内存
            count--;
            return true;
        }
    }

    // 判空：top == nullptr 即空栈
    bool isEmpty(){
        return top == nullptr;
    }

    // 获取栈中元素个数
    int getSize(){
        return count;
    }

    // 取栈顶元素：空栈抛异常（泛型 T 无法用 -1 占位）
    T getTop(){
        if(isEmpty()){
            throw "Stack is empty, no top element";
        }
        else{
            return top->Data;
        }
    }

    // 打印栈内元素（从栈顶到栈底）
    void printStack(){
        if(isEmpty()){
            cout<<"Stack is Empty"<<endl;
        }
        else{
            Node<T> *current = top;
            while(current != nullptr){
                cout<<current->Data<<"  ";
                current = current->Next;
            }
            cout<<endl;
            cout<<"size of Stack is:"<<count<<endl;
        }
    }

    // 清空栈：循环 pop 直到栈空
    void clear(){
        while(top != nullptr){
            pop();
        }
    }
};

int main(){
    ListStack<int> s;

    // Test empty stack
    cout << "=== Empty Stack Test ===" << endl;
    cout << "isEmpty: " << (s.isEmpty() ? "true" : "false") << endl;
    cout << "getSize: " << s.getSize() << endl;
    cout << "pop empty stack: " << (s.pop() ? "success" : "failed") << endl;
    try {
        s.getTop();
    } catch (const char* msg) {
        cout << "getTop exception: " << msg << endl;
    }

    // Test push
    cout << "\n=== Push Test ===" << endl;
    for (int i = 1; i <= 5; i++) {
        s.push(i);
        cout << "push " << i << "  current top: " << s.getTop() << endl;
    }
    cout << "Stack (top -> bottom): ";
    s.printStack();
    cout << "getSize: " << s.getSize() << endl;

    // Test pop
    cout << "\n=== Pop Test ===" << endl;
    cout << "pop: " << (s.pop() ? "success" : "failed") << "  new top: " << s.getTop() << endl;
    cout << "pop: " << (s.pop() ? "success" : "failed") << "  new top: " << s.getTop() << endl;
    cout << "Stack (top -> bottom): ";
    s.printStack();

    // Test clear
    cout << "\n=== Clear Test ===" << endl;
    s.clear();
    cout << "isEmpty after clear: " << (s.isEmpty() ? "true" : "false") << endl;
    cout << "getSize after clear: " << s.getSize() << endl;

    // Test reuse after clear
    cout << "\n=== Reuse After Clear ===" << endl;
    s.push(100);
    s.push(200);
    cout << "Stack (top -> bottom): ";
    s.printStack();

    return 0;
}
