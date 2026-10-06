#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cctype>
#include <limits>
#include <random>
#include <ctime>

using namespace std;

// 顺序栈
template <typename T>
class SeqStack {
private:
    vector<T> data;

public:
    void push(const T& value) {
        data.push_back(value);
    }

    bool pop(T& value) {
        if (data.empty()) return false;
        value = data.back();
        data.pop_back();
        return true;
    }

    bool top(T& value) const {
        if (data.empty()) return false;
        value = data.back();
        return true;
    }

    bool empty() const {
        return data.empty();
    }

    void print() const {
        if (data.empty()) {
            cout << "栈为空。\n";
            return;
        }

        cout << "栈底 -> ";
        for (const T& value : data) {
            cout << value << " ";
        }
        cout << "<- 栈顶\n";
    }
};

// 循环顺序队列
template <typename T>
class SeqQueue {
private:
    vector<T> data;
    size_t frontIndex;
    size_t rearIndex;

public:
    explicit SeqQueue(size_t capacity)
        : data(capacity + 1), frontIndex(0), rearIndex(0) {}

    bool empty() const {
        return frontIndex == rearIndex;
    }

    bool full() const {
        return (rearIndex + 1) % data.size() == frontIndex;
    }

    bool enqueue(const T& value) {
        if (full()) return false;

        data[rearIndex] = value;
        rearIndex = (rearIndex + 1) % data.size();
        return true;
    }

    bool dequeue(T& value) {
        if (empty()) return false;

        value = data[frontIndex];
        frontIndex = (frontIndex + 1) % data.size();
        return true;
    }

    vector<T> toVector() const {
        vector<T> result;
        size_t i = frontIndex;

        while (i != rearIndex) {
            result.push_back(data[i]);
            i = (i + 1) % data.size();
        }
        return result;
    }
};

// 将表达式拆分成数字和运算符
vector<string> tokenize(const string& expression) {
    vector<string> tokens;
    size_t i = 0;

    while (i < expression.size()) {
        if (isspace(static_cast<unsigned char>(expression[i]))) {
            ++i;
            continue;
        }

        if (isdigit(static_cast<unsigned char>(expression[i])) ||
            expression[i] == '.') {
            size_t start = i;
            int dotCount = 0;
            int digitCount = 0;

            while (i < expression.size() &&
                   (isdigit(static_cast<unsigned char>(expression[i])) ||
                    expression[i] == '.')) {
                if (expression[i] == '.') {
                    ++dotCount;
                    if (dotCount > 1) {
                        throw runtime_error("数字中出现了多个小数点。");
                    }
                } else {
                    ++digitCount;
                }
                ++i;
            }

            if (digitCount == 0) {
                throw runtime_error("无效数字。");
            }

            tokens.push_back(expression.substr(start, i - start));
        } else if (string("+-*/()").find(expression[i]) != string::npos) {
            tokens.push_back(string(1, expression[i]));
            ++i;
        } else {
            throw runtime_error(string("不支持的字符：") + expression[i]);
        }
    }

    return tokens;
}

bool isNumber(const string& token) {
    return !token.empty() &&
           (isdigit(static_cast<unsigned char>(token[0])) || token[0] == '.');
}

int precedence(const string& op) {
    if (op == "u+" || op == "u-") return 3;
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}

bool isUnary(const string& op) {
    return op == "u+" || op == "u-";
}

void applyOperator(vector<double>& values, const string& op) {
    if (isUnary(op)) {
        if (values.empty()) throw runtime_error("表达式不完整。");

        double value = values.back();
        values.pop_back();

        values.push_back(op == "u-" ? -value : value);
        return;
    }

    if (values.size() < 2) throw runtime_error("表达式不完整。");

    double right = values.back();
    values.pop_back();
    double left = values.back();
    values.pop_back();

    if (op == "+") values.push_back(left + right);
    else if (op == "-") values.push_back(left - right);
    else if (op == "*") values.push_back(left * right);
    else if (op == "/") {
        if (right == 0.0) throw runtime_error("除数不能为零。");
        values.push_back(left / right);
    } else {
        throw runtime_error("未知运算符。");
    }
}

// 用操作数栈和操作符栈直接计算中缀表达式
double evaluateInfix(const string& expression) {
    vector<string> tokens = tokenize(expression);
    vector<double> values;
    vector<string> operators;
    bool expectOperand = true;

    for (const string& token : tokens) {
        if (isNumber(token)) {
            if (!expectOperand) throw runtime_error("数字之间缺少运算符。");
            values.push_back(stod(token));
            expectOperand = false;
        } else if (token == "(") {
            if (!expectOperand) throw runtime_error("左括号前缺少运算符。");
            operators.push_back(token);
            expectOperand = true;
        } else if (token == ")") {
            if (expectOperand) throw runtime_error("右括号位置不正确。");

            while (!operators.empty() && operators.back() != "(") {
                string op = operators.back();
                operators.pop_back();
                applyOperator(values, op);
            }

            if (operators.empty()) throw runtime_error("括号不匹配。");
            operators.pop_back();

            while (!operators.empty() && isUnary(operators.back())) {
                string op = operators.back();
                operators.pop_back();
                applyOperator(values, op);
            }
            expectOperand = false;
        } else {
            if (expectOperand) {
                if (token == "+" || token == "-") {
                    operators.push_back(token == "+" ? "u+" : "u-");
                } else {
                    throw runtime_error("运算符位置不正确。");
                }
            } else {
                while (!operators.empty() && operators.back() != "(" &&
                       precedence(operators.back()) >= precedence(token)) {
                    string op = operators.back();
                    operators.pop_back();
                    applyOperator(values, op);
                }

                operators.push_back(token);
                expectOperand = true;
            }
        }
    }

    if (tokens.empty() || expectOperand) throw runtime_error("表达式不完整。");

    while (!operators.empty()) {
        if (operators.back() == "(") throw runtime_error("括号不匹配.");

        string op = operators.back();
        operators.pop_back();
        applyOperator(values, op);
    }

    if (values.size() != 1) throw runtime_error("表达式格式错误。");
    return values.back();
}

// 将中缀表达式转换为后缀表达式
vector<string> infixToPostfix(const string& expression) {
    vector<string> tokens = tokenize(expression);
    vector<string> output;
    vector<string> operators;
    bool expectOperand = true;

    for (const string& token : tokens) {
        if (isNumber(token)) {
            if (!expectOperand) throw runtime_error("数字之间缺少运算符。");
            output.push_back(token);
            expectOperand = false;
        } else if (token == "(") {
            if (!expectOperand) throw runtime_error("左括号前缺少运算符。");
            operators.push_back(token);
            expectOperand = true;
        } else if (token == ")") {
            if (expectOperand) throw runtime_error("右括号位置不正确。");

            while (!operators.empty() && operators.back() != "(") {
                output.push_back(operators.back());
                operators.pop_back();
            }

            if (operators.empty()) throw runtime_error("括号不匹配。");
            operators.pop_back();

            while (!operators.empty() && isUnary(operators.back())) {
                output.push_back(operators.back());
                operators.pop_back();
            }
            expectOperand = false;
        } else {
            if (expectOperand) {
                if (token == "+" || token == "-") {
                    operators.push_back(token == "+" ? "u+" : "u-");
                } else {
                    throw runtime_error("运算符位置不正确。");
                }
            } else {
                while (!operators.empty() && operators.back() != "(" &&
                       precedence(operators.back()) >= precedence(token)) {
                    output.push_back(operators.back());
                    operators.pop_back();
                }

                operators.push_back(token);
                expectOperand = true;
            }
        }
    }

    if (tokens.empty() || expectOperand) throw runtime_error("表达式不完整。");

    while (!operators.empty()) {
        if (operators.back() == "(") throw runtime_error("括号不匹配。");
        output.push_back(operators.back());
        operators.pop_back();
    }

    return output;
}

// 计算后缀表达式
double evaluatePostfix(const vector<string>& postfix) {
    vector<double> values;

    for (const string& token : postfix) {
        if (isNumber(token)) {
            values.push_back(stod(token));
        } else {
            applyOperator(values, token);
        }
    }

    if (values.size() != 1) throw runtime_error("后缀表达式格式错误。");
    return values.back();
}

void stackTest() {
    SeqStack<int> stack;
    int choice;

    while (true) {
        cout << "\n--- 顺序栈测试 ---\n"
             << "1. 入栈\n2. 出栈\n3. 查看栈顶\n4. 显示栈\n0. 返回\n"
             << "请选择：";

        cin >> choice;

        if (choice == 0) return;

        if (choice == 1) {
            int value;
            cout << "输入整数：";
            cin >> value;
            stack.push(value);
        } else if (choice == 2) {
            int value;
            if (stack.pop(value)) cout << "出栈元素：" << value << "\n";
            else cout << "栈为空。\n";
        } else if (choice == 3) {
            int value;
            if (stack.top(value)) cout << "栈顶元素：" << value << "\n";
            else cout << "栈为空。\n";
        } else if (choice == 4) {
            stack.print();
        } else {
            cout << "无效选项。\n";
        }
    }
}

void hospitalQueue() {
    SeqQueue<int> patients(100);
    static mt19937 generator(static_cast<unsigned int>(time(nullptr)));
    uniform_int_distribution<int> distribution(10000, 99999);
    int choice;

    while (true) {
        cout << "\n--- 医院候诊队列 ---\n"
             << "1. 排队\n2. 就诊\n3. 查看候诊队列\n0. 下班并返回\n"
             << "请选择：";

        cin >> choice;

        if (choice == 0) return;

        if (choice == 1) {
            int id = distribution(generator);
            if (patients.enqueue(id)) {
                cout << "病历号 " << id << " 已加入候诊队列。\n";
            } else {
                cout << "候诊队列已满。\n";
            }
        } else if (choice == 2) {
            int id;
            if (patients.dequeue(id)) {
                cout << "请病历号 " << id << " 的患者就诊。\n";
            } else {
                cout << "当前没有候诊患者。\n";
            }
        } else if (choice == 3) {
            vector<int> waiting = patients.toVector();
            if (waiting.empty()) {
                cout << "当前没有候诊患者。\n";
            } else {
                cout << "候诊病历号（队首到队尾）：";
                for (int id : waiting) cout << id << " ";
                cout << "\n";
            }
        } else {
            cout << "无效选项。\n";
        }
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\n===== 上机实验题 3 =====\n"
             << "1. 测试顺序栈\n"
             << "2. 直接计算中缀表达式\n"
             << "3. 中缀转后缀并计算\n"
             << "4. 医院候诊队列\n"
             << "0. 退出\n"
             << "请选择：";

        cin >> choice;

        if (choice == 0) {
            cout << "程序结束。\n";
            break;
        }

        if (choice == 1) {
            stackTest();
        } else if (choice == 2 || choice == 3) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string expression;

            cout << "请输入表达式：";
            getline(cin, expression);

            try {
                if (choice == 2) {
                    cout << "计算结果：" << evaluateInfix(expression) << "\n";
                } else {
                    vector<string> postfix = infixToPostfix(expression);

                    cout << "后缀表达式：";
                    for (const string& token : postfix) cout << token << " ";
                    cout << "\n";

                    cout << "计算结果：" << evaluatePostfix(postfix) << "\n";
                }
            } catch (const exception& e) {
                cout << "错误：" << e.what() << "\n";
            }
        } else if (choice == 4) {
            hospitalQueue();
        } else {
            cout << "无效选项。\n";
        }
    }

    return 0;
}