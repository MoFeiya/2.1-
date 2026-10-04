#include <iostream>
#include <stack>
#include <string>
#include <cctype>
using namespace std;

int priority(char op)
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

void zhong_houzhui(string &a)
{
    stack<char> ops;
    string result;

    for (size_t i = 0; i < a.size();)
    {
        if (isspace(static_cast<unsigned char>(a[i])))
        {
            ++i;
        }
        else if (isalnum(static_cast<unsigned char>(a[i])) || a[i] == '_')
        {
            // 读取完整的变量名或数字
            while (i < a.size() &&
                   (isalnum(static_cast<unsigned char>(a[i])) ||
                    a[i] == '_' || a[i] == '.'))
            {
                result += a[i++];
            }
            result += ' ';
        }
        else if (a[i] == '(')
        {
            ops.push(a[i++]);
        }
        else if (a[i] == ')')
        {
            while (!ops.empty() && ops.top() != '(')
            {
                result += ops.top();
                result += ' ';
                ops.pop();
            }
            if (!ops.empty()) ops.pop(); // 弹出左括号
            ++i;
        }
        else
        {
            char op = a[i++];

            while (!ops.empty() && ops.top() != '(' &&
                   (priority(ops.top()) > priority(op) ||
                    (priority(ops.top()) == priority(op) && op != '^')))
            {
                result += ops.top();
                result += ' ';
                ops.pop();
            }
            ops.push(op);
        }
    }

    while (!ops.empty())
    {
        result += ops.top();
        result += ' ';
        ops.pop();
    }

    if (!result.empty()) result.pop_back(); // 删除末尾空格
    a = result;
}

int main()
{
    string expression = "a + b * (c - 2)";
    zhong_houzhui(expression);
    cout << expression << endl; // a b c 2 - * +
}