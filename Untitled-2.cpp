#include <iostream>
#include <string>
using namespace std;

// 学生信息
struct Student
{
    int studentId;       // 学号
    string name;         // 姓名
    string sex;          // 性别

    int birthYear;       // 出生年
    int birthMonth;      // 出生月
    int birthDay;        // 出生日

    string major;        // 专业
    double score;        // 成绩
};

// 单链表结点
struct Node
{
    Student data; // 当前结点保存的学生
    Node* next;   // 指向下一个结点
};

class StudentList
{
private:
    Node* head; // 头指针，指向第一个结点

public:
    StudentList();
    ~StudentList();

    bool addStudent(const Student& student);
    Node* findStudent(int studentId);
    bool removeStudent(int studentId);
    bool changeStudent(int studentId, const Student& newStudent);

    void inputStudent();
    void showStudent(const Student& student) const;
    void showAll() const;
};

// 初始化空链表
StudentList::StudentList()
{
    head = nullptr;
}

// 析构函数：释放所有结点
StudentList::~StudentList()
{
    Node* current = head;

    while (current != nullptr)
    {
        Node* temp = current;
        current = current->next;
        delete temp;
    }

    head = nullptr;
}

// 根据学号查询
Node* StudentList::findStudent(int studentId)
{
    Node* current = head;

    while (current != nullptr)
    {
        if (current->data.studentId == studentId)
        {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}

// 增加学生：使用尾插法
bool StudentList::addStudent(const Student& student)
{
    // 防止学号重复
    if (findStudent(student.studentId) != nullptr)
    {
        return false;
    }

    // 创建新结点
    Node* newNode = new Node;

    newNode->data = student;
    newNode->next = nullptr;

    // 情况1：当前链表为空
    if (head == nullptr)
    {
        head = newNode;
        return true;
    }

    // 情况2：链表不为空，找到最后一个结点
    Node* current = head;

    while (current->next != nullptr)
    {
        current = current->next;
    }

    // 原来的最后一个结点指向新结点
    current->next = newNode;

    return true;
}

// 删除学生
bool StudentList::removeStudent(int studentId)
{
    if (head == nullptr)
    {
        return false;
    }

    // 要删除的是第一个结点
    if (head->data.studentId == studentId)
    {
        Node* temp = head;
        head = head->next;
        delete temp;

        return true;
    }

    // 查找待删除结点的前一个结点
     Node* previous = head;

    while (previous->next != nullptr &&
           previous->next->data.studentId != studentId)
    {
        previous = previous->next;
    }

    // 没有找到
    if (previous->next == nullptr)
    {
        return false;
    }

    Node* deletedNode = previous->next;

    previous->next = deletedNode->next;
    delete deletedNode;

    return true;
}

// 修改学生信息
bool StudentList::changeStudent(
    int studentId,
    const Student& newStudent)
{
    Node* node = findStudent(studentId);

    if (node == nullptr)
    {
        return false;
    }

    // 如果要修改学号，需要检查新学号是否重复
    if (newStudent.studentId != studentId &&
        findStudent(newStudent.studentId) != nullptr)
    {
        return false;
    }

    node->data = newStudent;

    return true;
}

// 输出一个学生的信息
void StudentList::showStudent(const Student& student) const
{
    cout << "学号：" << student.studentId << '\n';
    cout << "姓名：" << student.name << '\n';
    cout << "性别：" << student.sex << '\n';

    cout << "出生日期："
         << student.birthYear << '-'
         << student.birthMonth << '-'
         << student.birthDay << '\n';

    cout << "专业：" << student.major << '\n';
    cout << "成绩：" << student.score << '\n';
}

// 输出全部学生
void StudentList::showAll() const
{
    if (head == nullptr)
    {
        cout << "当前没有学生信息。\n";
        return;
    }

    Node* current = head;

    while (current != nullptr)
    {
        cout << "--------------------\n";
        showStudent(current->data);

        current = current->next;
    }

    cout << "--------------------\n";
}

// 从键盘输入并增加学生
void StudentList::inputStudent()
{
    Student student;

    cout << "请输入学号：";
    cin >> student.studentId;

    if (findStudent(student.studentId) != nullptr)
    {
        cout << "该学号已经存在，添加失败。\n";
        return;
    }

    cout << "请输入姓名：";
    cin >> student.name;

    cout << "请输入性别：";
    cin >> student.sex;

    cout << "请输入出生年、月、日：";
    cin >> student.birthYear
        >> student.birthMonth
        >> student.birthDay;

    cout << "请输入专业：";
    cin >> student.major;

    cout << "请输入成绩：";
    cin >> student.score;

    if (addStudent(student))
    {
        cout << "添加成功。\n";
    }
    else
    {
        cout << "添加失败。\n";
    }
}

int main()
{
    StudentList list;

    int choice;

    do
    {
        cout << "\n===== 学籍管理系统 =====\n";
        cout << "1. 增加学生\n";
        cout << "2. 查询学生\n";
        cout << "3. 删除学生\n";
        cout << "4. 修改学生\n";
        cout << "5. 显示全部学生\n";
        cout << "0. 退出系统\n";
        cout << "请选择：";

        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            list.inputStudent();
            break;
        }

        case 2:
        {
            int studentId;

            cout << "请输入要查询的学号：";
            cin >> studentId;

            Node* result = list.findStudent(studentId);

            if (result == nullptr)
            {
                cout << "没有找到该学生。\n";
            }
            else
            {
                list.showStudent(result->data);
            }

            break;
        }

        case 3:
        {
            int studentId;

            cout << "请输入要删除的学号：";
            cin >> studentId;

            if (list.removeStudent(studentId))
            {
                cout << "删除成功。\n";
            }
            else
            {
                cout << "没有找到该学生。\n";
            }

            break;
        }

        case 4:
        {
            int oldStudentId;
            Student newStudent;

            cout << "请输入要修改的学生学号：";
            cin >> oldStudentId;

            if (list.findStudent(oldStudentId) == nullptr)
            {
                cout << "没有找到该学生。\n";
                break;
            }

            cout << "请输入新的学号：";
            cin >> newStudent.studentId;

            cout << "请输入新的姓名：";
            cin >> newStudent.name;

            cout << "请输入新的性别：";
            cin >> newStudent.sex;

            cout << "请输入新的出生年、月、日：";
            cin >> newStudent.birthYear
                >> newStudent.birthMonth
                >> newStudent.birthDay;

            cout << "请输入新的专业：";
            cin >> newStudent.major;

            cout << "请输入新的成绩：";
            cin >> newStudent.score;

            if (list.changeStudent(oldStudentId, newStudent))
            {
                cout << "修改成功。\n";
            }
            else
            {
                cout << "修改失败，新学号可能已经存在。\n";
            }

            break;
        }

        case 5:
        {
            list.showAll();
            break;
        }

        case 0:
        {
            cout << "系统已退出。\n";
            break;
        }

        default:
        {
            cout << "输入错误，请重新选择。\n";
        }
        }
    }
    while (choice != 0);

    return 0;
}