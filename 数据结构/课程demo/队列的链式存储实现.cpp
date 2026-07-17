// ---------------------------------------------------------
// 队列的链式存储实现（无头结点的单链表，FIFO 先进先出）
// front 直接指向队首元素（无头结点方案）
// 特点：动态分配无容量上限；但需要特殊处理"删空后 rear 也要归零"
// ---------------------------------------------------------

#include<iostream>
using namespace std;

// 链队列结点
template<typename T>
struct Node
{
    T data;             // 结点数据
    Node* next;         // 下一跳指针
    Node(const T &value):data(value),next(nullptr){}   // 构造函数
};

// 链队列
template<typename T>
class LinkQueue
{
private:
    Node<T>* front;     // 指向队首结点（直接指向第一个真实元素，front==nullptr 表示空队列）
    Node<T>* rear;      // 指向队尾结点
    int count;          // 队列元素个数

public:
    // 构造函数：初始化空队列
    LinkQueue():front(nullptr),rear(nullptr),count(0){}

    // 析构函数：调用 clear 释放所有结点
    ~LinkQueue(){
        clear();
    }

    // 判空
    bool isEmpty(){
        return front == nullptr;
    }

    // 入队：在队尾追加新结点
    // 时间复杂度 O(1)，rear 直接可用，无需遍历
    bool enqueue(const T& value){
        Node<T>* newNode = new Node<T>(value);
        if(isEmpty()){
            // 空队列：front 和 rear 都指向新结点
            front = rear = newNode;
        }
        else{
            rear->next = newNode;     // 原队尾指向新结点
            rear = newNode;           // rear 更新为新结点
        }
        count++;
        return true;
    }

    // 出队：删去队首结点，把值通过引用带回
    // 注意点：删空后 rear 也要重置为 nullptr，否则成野指针
    bool dequeue(T& value){
        if(isEmpty()){
            return false;
        }
        Node<T>* tempNode = front;    // 暂存待删结点
        value = tempNode->data;        // 把值带回给调用者
        front = front->next;           // front 指针后移
        if(front == nullptr){          // 删空了，rear 也要归零
            rear = nullptr;
        }
        delete tempNode;
        count--;
        return true;
    }

    // 取队首元素（不出队）
    bool getFront(T& value){
        if(isEmpty()){
            return false;
        }
        value = front->data;
        return true;
    }

    // 取队尾元素（不入队）
    bool getRear(T& value) const {
        if(isEmpty()){
            return false;
        }
        value = rear->data;
        return true;
    }

    // 获取队列元素个数
    int getSize(){
        return count;
    }

    // 清空队列：循环 delete 所有结点，rear 重置
    void clear(){
        while(!isEmpty()){
            Node<T>* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
        count = 0;
    }

    // 打印队列（从队首到队尾）
    void printQueue(){
        if(isEmpty()){
            cout << "Queue is empty" << endl;
            return;
        }
        Node<T>* current = front;
        while(current != nullptr){
            cout << current->data << "  ";
            current = current->next;
        }
        cout << endl;
        cout << "the size of queue is: " << count << endl;
    }
};

int main(){
    LinkQueue<int> q;

    // Test empty queue
    cout << "=== Empty Queue Test ===" << endl;
    cout << "isEmpty: " << (q.isEmpty() ? "true" : "false") << endl;
    cout << "getSize: " << q.getSize() << endl;
    int x = 0;
    cout << "dequeue empty: " << (q.dequeue(x) ? "success" : "failed") << endl;
    cout << "getFront empty: " << (q.getFront(x) ? "success" : "failed") << endl;
    cout << "getRear empty: " << (q.getRear(x) ? "success" : "failed") << endl;

    // Test enqueue
    cout << "\n=== Enqueue Test ===" << endl;
    for (int i = 1; i <= 5; i++) {
        cout << "enqueue " << i << ": " << (q.enqueue(i) ? "success" : "failed") << endl;
    }
    cout << "Queue (front -> rear): ";
    q.printQueue();
    cout << "getSize: " << q.getSize() << endl;
    q.getFront(x);  cout << "getFront: " << x << endl;
    q.getRear(x);   cout << "getRear: "  << x << endl;

    // Test dequeue
    cout << "\n=== Dequeue Test ===" << endl;
    for (int i = 0; i < 3; i++) {
        if (q.dequeue(x)) {
            q.getFront(x);
            cout << "dequeue: " << x << "  new front: " << x << endl;
        }
    }
    cout << "Queue (front -> rear): ";
    q.printQueue();
    cout << "getSize: " << q.getSize() << endl;

    // Test dequeue until empty (verify rear reset)
    cout << "\n=== Dequeue All ===" << endl;
    while (q.dequeue(x)) {
        cout << "dequeue: " << x << endl;
    }
    cout << "isEmpty after drain: " << (q.isEmpty() ? "true" : "false") << endl;

    // Test re-enqueue after drain (verify front/rear pointers are valid)
    cout << "\n=== Re-enqueue After Drain ===" << endl;
    q.enqueue(100);
    q.enqueue(200);
    q.enqueue(300);
    cout << "Queue (front -> rear): ";
    q.printQueue();
    q.getFront(x);  cout << "getFront: " << x << endl;
    q.getRear(x);   cout << "getRear: "  << x << endl;

    // Test clear
    cout << "\n=== Clear Test ===" << endl;
    q.clear();
    cout << "isEmpty after clear: " << (q.isEmpty() ? "true" : "false") << endl;
    cout << "getSize after clear: " << q.getSize() << endl;

    // Test reuse after clear
    cout << "\n=== Reuse After Clear ===" << endl;
    q.enqueue(999);
    q.enqueue(888);
    cout << "Queue (front -> rear): ";
    q.printQueue();

    return 0;
}
