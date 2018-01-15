#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Stack
{
    private:
        vector<T>s;
        int top;
    public:
        Stack() {top = -1;}
        ~Stack()
        {
            top = -1;
            s.clear();
        }
        bool empty_()
        {
            if(top == -1) return true;
            return false;
        }
        void push(const T &itm)
        {
            s.push_back(itm);
            top++;
        }
        T top_()
        {
            if(top != -1) return s[top];
            else
            {
                cout << "Eroare !";
            }
        }
        void pop()
        {
            if(top == -1) return;
            s.pop_back();
            top--;
        }
};

int main()
{
    Stack <int>st;
    cout << st.top_() << endl;
    st.push(9);
    cout << st.top_() << endl;
    st.pop();
    cout << st.top_() << endl;
}
