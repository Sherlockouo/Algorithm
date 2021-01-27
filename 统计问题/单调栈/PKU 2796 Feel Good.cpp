#include <iostream>

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
    StackData& top();
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

StackData& Stack::top() {
    return data_[top_ - 1];
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

#define ll long long

ll sum[MAXSTACK];

ll Max(ll a, ll b) {
    return a > b ? a : b;
}

// ֱ��ͼ������ڽ��Ӿ���
ll LargestRectangleInHistogram(int size, int *h, ll *sum, Stack& st, int& l, int& r) {
    st.clear();
    int topIndex;
    ll maxRet = -1;
    h[++size] = -1;
    for (int i = 1; i <= size; ++i) {
        if (st.empty() || h[st.top()] <= h[i]) {
            // ά��һ����ջ�׵�ջ���ĵ�������ջ
            st.push(i);
        }
        else {
            // ���ջ��Ԫ�ش��ڵ��ڵ�ǰԪ�أ���һֱ����ջ��Ԫ�ؽ��бȽ�
            while (!st.empty() && h[st.top()] >= h[i]) {

                topIndex = st.top();
                st.pop();
                ll ans = (ll)(sum[i-1] - sum[topIndex-1]) * (ll)h[topIndex];
                if (ans > maxRet) {
                    maxRet = ans;
                    l = topIndex;
                    r = i - 1;
                }
            }
            st.push(topIndex);
            h[topIndex] = h[i];
        }
    }
    return maxRet;
}

int main() {

    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &h[i]);
            sum[i] = sum[i - 1] + h[i];
        }
        int l, r;
        printf("%lld\n", LargestRectangleInHistogram(n, h, sum, st, l, r));
        printf("%d %d\n", l, r);
    }
    return 0;
}

