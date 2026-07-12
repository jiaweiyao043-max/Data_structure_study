#include<iostream>
using namespace std;

// ---------------------------------------------------------
// 栈的顺序存储实现（数组模拟栈，LIFO 后进先出）
// ---------------------------------------------------------
template<typename T>
class Stack{
private:
    T* Data;         // 存放栈元素的数组（动态分配）
    int top;         // 栈顶下标（指向栈顶元素，-1 表示空栈）
    int capacity;    // 栈的最大容量

public:
    // 构造函数：分配大小为 size 的数组，初始化空栈
    Stack(T size){
        Data = new T[size];
        capacity = size;
        top = -1;
        cout<<"Stack is build"<<"  "<<"size: "<<size<<endl;
    }

    // 析构函数：释放动态分配的数组内存
    ~Stack(){
        delete[] Data;
        cout<<"Stack is delete"<<endl;
    }

    // 判空：top == -1 时栈为空
    bool isEmpty(){
        if(top == -1){
            cout<<"Stack is empty"<<endl;
            return true;
        }
        else
            return false;
    }

    // 判满：top == capacity-1 时栈满（数组最后一个位置已被占用）
    bool isFull(){
        if(top == capacity-1){
            cout<<"Stack is full"<<endl;
            return true;
        }
        else
            return false;
    }

    // 入栈：先移动 top 指针，再将元素放入数组
    bool push(T value){
        if(isFull()){
            return false;
        }
        else{
            Data[++top] = value;    // ++top 先自增再赋值，对应"先移指针再放元素"
            return true;
        }
    }

    // 出栈：top 指针下移，逻辑删除（元素仍在数组中但已不可访问）
    bool pop(){
        if(isEmpty()){
            return false;
        }
        else{
            top--;
            return true;
        }
    }

    // 取栈顶元素：返回 Data[top]，空栈时抛出异常
    T getTop(){
        if(isEmpty()){
            throw "Stack is empty, no top element";
        }
        else{
            return Data[top];
        }
    }

    // 获取栈中当前元素个数
    int getSize(){
        return top+1;
    }

    // 打印栈内元素（从栈底到栈顶）
    void printStack(){
        if(isEmpty()){
            cout<<"Stack is empty"<<endl;
        }
        else{
            for(int i = 0; i <= top; i++ ){
                cout<<Data[i]<<" ";
            }
            cout<<endl;
        }
    }

};

int main(){
    Stack<int> s(5);

    // Test empty stack
    cout << "=== Empty Stack Test ===" << endl;
    cout << "isEmpty: " << (s.isEmpty() ? "true" : "false") << endl;
    cout << "pop empty stack: " << (s.pop() ? "success" : "failed") << endl;
    try {
        s.getTop();
    } catch (const char* msg) {
        cout << "getTop exception: " << msg << endl;
    }

    // Test push
    cout << "\n=== Push Test ===" << endl;
    for (int i = 1; i <= 5; i++) {
        cout << "push " << i << ": " << (s.push(i) ? "success" : "failed") << endl;
    }
    cout << "Stack (bottom -> top): ";
    s.printStack();
    cout << "Current size: " << s.getSize() << endl;

    // Test push when full
    cout << "\n=== Full Stack Test ===" << endl;
    cout << "push 6: " << (s.push(6) ? "success" : "failed") << endl;
    cout << "Top element: " << s.getTop() << endl;

    // Test pop
    cout << "\n=== Pop Test ===" << endl;
    cout << "pop: " << (s.pop() ? "success" : "failed") << "  new top: " << s.getTop() << endl;
    cout << "pop: " << (s.pop() ? "success" : "failed") << "  new top: " << s.getTop() << endl;
    cout << "Stack (bottom -> top): ";
    s.printStack();

    // Pop until empty
    cout << "\n=== Pop All ===" << endl;
    while (!s.isEmpty()) {
        cout << "pop top " << s.getTop() << ": " << (s.pop() ? "success" : "failed") << endl;
    }
    cout << "isEmpty: " << (s.isEmpty() ? "true" : "false") << endl;

    return 0;
}
