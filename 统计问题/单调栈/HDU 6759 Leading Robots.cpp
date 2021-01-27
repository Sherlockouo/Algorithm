#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

/***************************ջ ģ��***********************************/
typedef int StackData;
const int MAXSTACK = 100010;

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
    StackData& pretop() const;
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

StackData& Stack::pretop() const {
    return data_[top_ - 2];
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

int n;
int h[MAXSTACK];
Stack st;

struct Robot {
    int pos, a;
    void read() {
        scanf("%d %d", &pos, &a);
    }

    bool operator < (const Robot & r) const {
        if (pos == r.pos) {
            return a > r.a;
        }
        return pos > r.pos;
    }

    bool operator == (const Robot & r) const {
        return pos == r.pos && a == r.a;
    }

}R[MAXSTACK];

#define ll long long

int has[MAXSTACK];

int Max(int a, int b) {
    return a > b ? a : b;
}

bool timeLargerThan(int pretop, int top, int cur) {
    //   (R[pretop].s - R[top].s) / (R[top].a - R[pretop].a) >= (R[top].s - R[cur].s) / (R[cur].a - R[top].a)

    return (ll)(R[pretop].pos - R[top].pos)*(R[cur].a - R[top].a) >= (ll)(R[top].pos - R[cur].pos)*(R[top].a - R[pretop].a);
}

int getLeadingCount(int size, Robot *R, Stack& st) {
    st.clear();
    int topIdx, preTopIdx;
    int MaxA = -1;
    memset(has, 0, sizeof(has));

    for (int i = 1; i <= size; ++i) {

        if (R[i].a <= MaxA) {
            // û�д���֮ǰ�������ٶȣ���������Ϊ ����ͷ�� ��ѡ��
            continue;
        }

        MaxA = Max(MaxA, R[i].a);
        if (i > 1 && R[i].pos == R[i - 1].pos) {
            // ��ʼλ����ͬ�������ˣ����ٶ�С���Ǹ���Զû�л����Ϊ ����ͷ�򡱣�
            continue;
        }
        if (i + 1 <= size) {
            if (R[i] == R[i + 1]) {
                // ��ʼλ����ͬ�����ٶ�Ҳ��ͬ�������˶�û�л����Ϊ ����ͷ�򡱣�
                has[i] = 1;
            }
        }


        if (st.size() < 2) {
            st.push(i);
        }
        else {
            // ���ջ��Ԫ�ش��ڵ��ڵ�ǰԪ�أ���һֱ����ջ��Ԫ�ؽ��бȽ�
            while (st.size() >= 2 && timeLargerThan(st.pretop(), st.top(), i)) {
                st.pop();
            }
            st.push(i);
        }
    }
    int ans = 0;
    while (!st.empty()) {
        if (!has[st.top()]) ++ans;
        st.pop();
    }
    return ans;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            R[i].read();
        }
        sort(R + 1, R + n + 1);
        printf("%d\n", getLeadingCount(n, R, st));
    }
    return 0;
}

/*
10
5
9 1
8 2
7 3
6 4
5 5
*/