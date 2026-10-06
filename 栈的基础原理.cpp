#include<iostream>
using namespace std;
template<class T,int maxsize>
class zhan
{
        T data[maxsize];
        int top;
    public:
        zhan();
        T gettop();
        void push(T X);
        T pop();
        bool empty();
        bool full();

};

template<class T,int maxsize>
zhan<T,maxsize>::zhan()
{
    top = -1;

}

template<class T,int maxsize>
T zhan<T,maxsize>::gettop()
{
    return data[top];

}

template<class T,int maxsize>
void zhan<T,maxsize>::push(T X)
{
    if(top == maxsize-1)
    {
        cout<<"沾满";
        exit(1);
    }
    else{
        top++;
        data[top] = X;
        
    }
} 
template<class T,int maxsize>
T zhan<T,maxsize>::pop()
{
    if(top == -1) 
    {
        cout<<"站空";
        exit(1);
    }
    T xx;
    xx = data[top];
    top--;

    return xx;

}
template<class T,int maxsize>
bool zhan<T,maxsize>::empty()
{
    return top == -1;
}
template<class T,int maxsize>
bool zhan<T,maxsize>::full()
{
    return top == maxsize - 1;

}
int main()
{
    zhan<int, 5> s;
    s.push(10);
    s.push(20);

    cout << s.gettop() << '\n'; // 20
    cout << s.pop() << '\n';    // 20
    cout << s.empty() << '\n';  // 0，表示栈非空
}


