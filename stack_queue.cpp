#include <iostream>
#include <stack>
#include <exception>
#include <queue>
using namespace std;

//两个栈实现一个队列
template<typename T> class CQueue
{
    public:
        CQueue(){}
        ~CQueue(){}
        void appendtail(const T& node);
        T deletehead();
    private:
        stack<T> s1;
        stack<T> s2;
};
template<typename T> void CQueue<T>::appendtail(const T& element)
{
    s1.push(element);
}
template<typename T> T CQueue<T>::deletehead()
{
    if (s2.empty()) {
        while (!s1.empty()) {
            T& t = s1.top();
            s2.push(t);
            s1.pop();
        }
    }

    if (s2.empty()) {
        throw new exception();
    }

    T head = s2.top();
    s2.pop();
    return head;

}
// two queue----> one stack
template<typename T> class CStack
{
    public:
        CStack(){}
        ~CStack(){}
        void push(const T& node);
        T pop();
    private:
        queue<T> q1;
        queue<T> q2;
};
template<typename T> void CStack<T>::push(const T& element)
{
    if (!q1.empty()) {
        q1.push(element);
    } else {
        q2.push(element);
    }
}

template<typename T> T CStack<T>::pop()
{
    if (q1.empty() && q2.empty()) {
        throw new exception();
    } else if (q1.empty()) {
        while (q2.size() > 1) {
            q1.push(q2.front());
            q2.pop();
        }
        T t = q2.front();
        q2.pop();
        return t;
    } else if (q2.empty()) {
        while (q1.size() > 1) {
            q2.push(q1.front());
            q1.pop();
        }
        T t = q1.front();
        q1.pop();
        return t;

    }
}
int main() 
{
    /*
    CQueue<int> q;
    q.appendtail(1);
    q.appendtail(4);
    q.appendtail(5);
    cout<<q.deletehead()<<" ";
    q.appendtail(6);
    cout<<q.deletehead()<<" ";
    cout<<q.deletehead()<<" ";
    cout<<q.deletehead()<<" ";
    */
    CStack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    cout<<st.pop()<<endl;
    cout<<st.pop()<<endl;
    cout<<st.pop()<<endl;
    
    return 0;
}

