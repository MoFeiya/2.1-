#include<iostream>
using namespace std;
template<class T>
struct node
{
    T x;
    node *next;

}
template<class T>
class lianbiao_zhai
{
    node<T> *top;
    public:
        lianbiao_zhai();

        ~lianbiao_zhai();
        void push(T x);
        T pop();
        T gettop();
        bool empty();


}
template<class T>
bool lianbiao_zhai::empty()
{
    if(top == NULL) return true;
    return false;

}
template<class T>
lianbiao_zhai::~lianbiao()
{
    p = top;
    while(p!=NULL)
    {
        q = p;
        p = p->next;
        delete q;

    }
    top = NULL;
    
}

template<class T>
T lianbiao_zhai::pop()
{
    if(top ==NULL) 
    {
        cerr<<"下溢";
        exit(1);

    }
    x = top->data;
    top = top->next;
    delete p;
    return x;

}
template<class T>
T lianbiao_zhai::top()
{
    if(top ==NULL)
    {
        cout<<"xiayi";
        exit(1);

    }

}

template<class T>
lianbiao_zhai<T>::lianbiao_zhai()
{
    top = NULL;

}
template<class T>
void lianbiao_zhai::push(T x)
{
    s = new node<T>;
    s->data = x;
    s->next = top;
    top = s;

}
