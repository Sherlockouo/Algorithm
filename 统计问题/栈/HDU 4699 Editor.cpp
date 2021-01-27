#include <iostream>
#include <cstring>
using namespace std;

/***************************ջ ģ��***********************************/
typedef int StackData;
const int MAXSTACK = 1000100;

class  Stack {
private:
    StackData *data_;
    int top_;
public:
    Stack();
    virtual ~Stack();

    void clear();
    void push(const StackData& sd);
    StackData& top() const;
    int size() const;

    void pop();

public:
    bool empty() const;
};

Stack::Stack() : data_(NULL) {
    data_ = new StackData[MAXSTACK];
}
Stack::~Stack() {
    if (data_) {
        delete[] data_;
        data_ = NULL;
    }
}

void Stack::clear() {
    top_ = 0;
}

void Stack::push(const StackData& sd) {
    data_[top_++] = sd;
}

StackData& Stack::top() const {
    return data_[top_ - 1];
}

int Stack::size() const {
    return top_;
}

void Stack::pop() {
    if (!empty()) {
        --top_;
    }
}

bool Stack::empty() const {
    return !top_;
}
/***************************ջ ģ��***********************************/

/*
    ˫ջ�Զ�

    ��ߵ�ջ �� �ұߵ�ջ ��ϳ��������У����λ��ʼ��������ջ��Ԫ��֮�䣻

    1��I Insert ������
    2��D Delete ������ɾ�����ǰ��Ԫ�أ�
    3��R Move ��������ջ��������ջ��ջ��
    4��L Move ��������ջ��������ջ��ջ��
    5��Q k�� ѯ�����ǰ׺�ͣ�
*/

int n;
Stack stackL, stackR;
int sum[MAXSTACK], dp[MAXSTACK];
char cmd[10];

int Max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        stackL.clear();
        stackR.clear();
        dp[0] = -2000000000;
        sum[0] = 0;

        while (n--) {
            scanf("%s", cmd);
            if (cmd[0] == 'I') {
                int x;
                scanf("%d", &x);
                stackL.push(x);
                int idx = stackL.size();
                sum[idx] = sum[idx - 1] + x;
                dp[idx] = Max(dp[idx - 1], sum[idx]);
            }
            else if (cmd[0] == 'D') {
                if (!stackL.empty()) {
                    stackL.pop();
                }
            }
            else if (cmd[0] == 'L') {
                if (!stackL.empty()) {
                    int x = stackL.top();
                    stackL.pop();
                    stackR.push(x);
                }
            }
            else if (cmd[0] == 'R') {
                if (!stackR.empty()) {
                    int x = stackR.top();
                    stackR.pop();
                    stackL.push(x);

                    int idx = stackL.size();
                    sum[idx] = sum[idx - 1] + x;
                    dp[idx] = Max(dp[idx - 1], sum[idx]);
                }
            }
            else if (cmd[0] == 'Q') {
                int k;
                scanf("%d", &k);
                printf("%d\n", dp[k]);
            }

            //printf("(%d) - (%d)\n", stackL.size(), stackR.size());
        }
    }
    return 0;
}

/*
8
I 2
I -1
I 1
Q 3
L
D
R
Q 2
*/