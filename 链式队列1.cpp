#include <iostream>
#include <stdexcept>
using namespace std;

template<class T>
struct node
{
    T data;
    node<T>* next;
};

template<class T>
class linkqueue
{
private:
    node<T>* front;
    node<T>* rear;

public:
    linkqueue();
    ~linkqueue();

    void enqueue(T x);
    T dequeue();
    T getqueue() const;
    bool empty() const;
};

template<class T>
linkqueue<T>::linkqueue()
{
    // 创建不存放队列数据的头结点
    front = rear = new node<T>;
    front->next = NULL;
}

template<class T>
linkqueue<T>::~linkqueue()
{
    // 从头结点开始，逐个释放所有结点
    while (front != NULL)
    {
        node<T>* p = front;
        front = front->next;
        delete p;
    }
}

template<class T>
bool linkqueue<T>::empty() const
{
    return front == rear;
}

template<class T>
void linkqueue<T>::enqueue(T x)
{
    node<T>* p = new node<T>;
    p->data = x;
    p->next = NULL;

    rear->next = p;
    rear = p;
}

template<class T>
T linkqueue<T>::dequeue()
{
    if (empty())
        throw underflow_error("Queue is empty");

    node<T>* p = front->next;
    T x = p->data;

    front->next = p->next;

    // 如果刚删除的是最后一个数据结点，rear 要退回头结点
    if (rear == p)
        rear = front;

    delete p;
    return x;
}

template<class T>
T linkqueue<T>::getqueue() const
{
    if (empty())
        throw underflow_error("Queue is empty");

    // 只查看队头，不删除结点
    return front->next->data;
}

int main()
{
    linkqueue<int> q;
    q.enqueue(10);
    q.enqueue(20);

    cout << q.getqueue() << '\n'; // 10
    cout << q.dequeue() << '\n';  // 10
}