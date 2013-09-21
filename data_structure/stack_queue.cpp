#include <iostream>
#include <stack>
#include <cassert>
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

//题21：定义栈的数据结构，实现能得到栈最小元素的min函数，要求pop，push，min都是O(1)
template<typename T> class StackWithMin
{
    public:
        StackWithMin(){}
        ~StackWithMin(){}
        void push(const T&);
        T pop();
        T min();
    
    private:
        stack<T> st;
        stack<T> min_st;
};

template<typename T> void StackWithMin<T>::push(const T& element)
{
    st.push(element);
    if (min_st.empty() || element < min_st.top()) {
        min_st.push(element);
    } else {
        min_st.push(min_st.top());
    }
}

template<typename T> T StackWithMin<T>::pop()
{
    if (st.empty()) {
        throw new exception();
    }
    T t = st.top();
    st.pop();
    min_st.pop();

    return t;
}
template<typename T> T StackWithMin<T>::min() 
{
    if (min_st.empty()) {
        throw new exception();
    }
    return min_st.top();
    
}

//题22：栈的压入、弹出序列：给出两个整数队列，第一个是压入顺序，判断第二个是否是弹出顺序，假设压入栈的数字不相同
bool is_pop_order(int push_order[], int pop_order[], int n)
{
    assert(push_order && pop_order && n > 0);
    stack<int> st;
    int i = 0, j = 0;
    while (i  < n) {
        if (st.empty() || st.top() != pop_order[j]) {
            st.push(push_order[i++]);
        } else {
            st.pop();
            j++;
        }
    }
    
    if (pop_order[j] == st.top()) {
        st.pop();
        j++;
    }
    printf("i=%d,j=%d\n",i,j);

   return  (j == n) ? true : false; 
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
    /*
    CStack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    cout<<st.pop()<<endl;
    cout<<st.pop()<<endl;
    cout<<st.pop()<<endl;
    */

    int push_order[] = {1,2,3,4,5};
    int pop_order1[] = {1,2,3,4,5};
    int pop_order2[] = {4,5,3,1,2};

    printf("{1,2,3,4,5} is pop order of {1,2,3,4,5}:%d\n", is_pop_order(push_order,pop_order1,sizeof(push_order)/sizeof(int)));
    printf("{4,5,3,1,2} is pop order of {1,2,3,4,5}:%d\n", is_pop_order(push_order,pop_order2,sizeof(push_order)/sizeof(int)));
    return 0;
}

