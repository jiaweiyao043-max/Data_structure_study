// ---------------------------------------------------------
// 队列的顺序存储实现（循环队列）
// 用一个额外槽位来区分"空"和"满"：capacity = maxsize + 1
// - 队空条件：front == rear
// - 队满条件：(rear + 1) % capacity == front
// - 元素个数：(rear - front + capacity) % capacity
// ---------------------------------------------------------

#include<iostream>
using namespace std;

template<typename T>
class SeqQueue{
private:
    T* data;        // 存放队列元素的数组（动态分配）
    int front;      // 队首下标（指向队首元素）
    int rear;       // 队尾下标（指向队尾元素的下一个空位）
    int capacity;   // 数组总容量 = 用户传入 maxsize + 1

public:
    // 构造函数：分配容量为 cap+1 的数组（牺牲一个槽位用于判满）
    SeqQueue(int cap){
        capacity = cap + 1;             // 实际数组大小 = 用户指定容量 + 1
        data = new T[capacity];         // 动态分配
        front = rear = 0;               // 初始 front 和 rear 都为 0，队空
    }

    // 析构函数：释放动态数组
    ~SeqQueue(){
        delete[] data;
    }

    // 判满：rear 的下一个位置是 front 即满（牺牲一个槽位）
    bool isFull(){
        return (rear + 1) % capacity == front;
    }

    // 判空：front == rear 即空
    bool isEmpty(){
        return front == rear;
    }

    // 入队：把 value 放到 rear 位置，再让 rear 循环后移
    bool enqueue(T value){
        if(isFull()){
            return false;
        }
        else{
            data[rear] = value;
            rear = (rear + 1) % capacity;   // 循环后移
            return true;
        }
    }

    // 出队：front 循环后移，逻辑删除队首元素
    bool dequeue(){
        if(isEmpty()){
            return false;
        }
        else{
            front = (front + 1) % capacity;
            return true;
        }
    }

    // 出队并返回队首元素
    T dequeueAndGet(){
        if(isEmpty()){
            throw "Queue is empty, cannot dequeue";
        }
        T value = data[front];
        front = (front + 1) % capacity;
        return value;
    }

    // 取队首元素（不出队）
    T getFront(){
        if(isEmpty()){
            throw "Queue is empty, no front element";
        }
        return data[front];
    }

    // 取队尾元素（不入队）
    T getRear(){
        if(isEmpty()){
            throw "Queue is empty, no rear element";
        }
        // rear 指向的是队尾元素的下一个空位，所以要回退一格
        return data[(rear - 1 + capacity) % capacity];
    }

    // 获取队列中元素个数
    int getSize(){
        return (rear - front + capacity) % capacity;
    }

    // 清空队列：重置 front 和 rear 即可（数据被覆盖）
    void clear(){
        rear = front = 0;
    }

    // 打印队列（从队首到队尾）
    void print(){
        if(isEmpty()){
            cout << "Queue is empty" << endl;
            return;
        }
        int i = front;
        while(i != rear){
            cout << data[i] << " ";
            i = (i + 1) % capacity;
        }
        cout << endl;
    }
};

int main(){
    // 注意：用户传 5，实际容量是 6（最多存 5 个元素）
    SeqQueue<int> q(5);

    // Test empty queue
    cout << "=== Empty Queue Test ===" << endl;
    cout << "isEmpty: " << (q.isEmpty() ? "true" : "false") << endl;
    cout << "getSize: " << q.getSize() << endl;
    cout << "dequeue empty: " << (q.dequeue() ? "success" : "failed") << endl;
    try {
        q.getFront();
    } catch (const char* msg) {
        cout << "getFront exception: " << msg << endl;
    }

    // Test enqueue
    cout << "\n=== Enqueue Test ===" << endl;
    for (int i = 1; i <= 5; i++) {
        cout << "enqueue " << i << ": " << (q.enqueue(i) ? "success" : "failed") << endl;
    }
    cout << "Queue (front -> rear): ";
    q.print();
    cout << "getSize: " << q.getSize() << endl;
    cout << "getFront: " << q.getFront() << "  getRear: " << q.getRear() << endl;

    // Test enqueue when full
    cout << "\n=== Full Queue Test ===" << endl;
    cout << "enqueue 6: " << (q.enqueue(6) ? "success" : "failed") << endl;
    cout << "isFull: " << (q.isFull() ? "true" : "false") << endl;

    // Test dequeue
    cout << "\n=== Dequeue Test ===" << endl;
    cout << "dequeue: " << (q.dequeue() ? "success" : "failed") << "  new front: " << q.getFront() << endl;
    cout << "dequeueAndGet: " << q.dequeueAndGet() << "  new front: " << q.getFront() << endl;
    cout << "Queue (front -> rear): ";
    q.print();
    cout << "getSize: " << q.getSize() << endl;

    // Test circular behavior (re-enqueue to verify wrap-around)
    cout << "\n=== Circular Behavior ===" << endl;
    q.enqueue(100);
    q.enqueue(200);
    cout << "After enqueue 100, 200: ";
    q.print();
    cout << "getFront: " << q.getFront() << "  getRear: " << q.getRear() << endl;

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
    q.print();

    return 0;
}
