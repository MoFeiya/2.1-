#include<iostream>
using namespace std;
template<class T,int maxsize>
class seqQueue
{
    T data[maxsize];
    int front,rear;
    public:
        seqQueue();
        void enQueue(T x);
        T DeQueue();
        T GetQueue();
        bool isempty();
        bool isfull();

}
template<class T,int maxsize>
bool seQueue<T,maxsize>::isempty()
{
    return rear == front;

}
template<class T,int maxsize>
bool seQueue<T,maxsize>::isfull()
{
    return (rear+1)%maxsize==front;

}



template<class T,int maxsize>
T seQueue<T,maxsize>::GetQueue()
{
    T xx = DeQueue();
    return xx;

}

template<class T,int maxsize>
seqQueue<T,maxsize>::seqQueue()
{
    front  = rear = 0;

}
template<class T,int maxsize>
void seqQueue<T,maxsize>::enQueue(T x)
{
    if((rear+1)%maxsize==front)
    {
        cout<<"man!";
    }
    rear = (rear+1)%maxsize;
    data[rear] = x;

}
template<class T,int maxsize>
T seqQueue<T,maxsize>::DeQueue(){
    if(rear == front) 
    {
        cout<<"kong";
    }
    front = (front+1)%maxsize;
    return data[front];
    
}

int main()
{
    
}