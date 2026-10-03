#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool isMatched(const string& s) {
    stack<char> st;

    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (st.empty()) return false;

            char top = st.top();
            st.pop();

            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) {
                return false;
            }
        }
    }

    return st.empty();
}

int main() {
    string a;
    getline(cin, a);

    cout << (isMatched(a) ? "配对正确" : "配对错误") << '\n';
    return 0;
}