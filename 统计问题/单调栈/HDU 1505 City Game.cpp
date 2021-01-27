#include <iostream>
#include <cstring>

using namespace std;

/***************************栈 模板***********************************/
typedef int StackData;
const int MAXSTACK = 10001;

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
/***************************栈 模板***********************************/

Stack st;

#define ll long long

ll Max(ll a, ll b) {
    return a > b ? a : b;
}

// 直方图的最大内接子矩阵
ll LargestRectangleInHistogram(int size, int *h, Stack& st) {
    st.clear();
    int topIndex;
    ll maxRet = 0;
    h[size++] = -1;
    for (int i = 0; i < size; ++i) {
        if (st.empty() || h[st.top()] <= h[i]) {
            // 维护一个从栈底到栈顶的单调递增栈
            st.push(i);
        }
        else {
            // 如果栈顶元素大于等于当前元素，则一直弹出栈顶元素进行比较
            while (!st.empty() && h[st.top()] >= h[i]) {

                topIndex = st.top();
                st.pop();
                maxRet = Max(maxRet, (ll)(i - topIndex) * (ll)h[topIndex]);
            }
            st.push(topIndex);
            h[topIndex] = h[i];
        }
    }
    return maxRet;
}

int n, m;
int Map[1010][1010], h[1010];
char str[20];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {

        ll MaxV = 0;
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                scanf("%s", str);
                Map[i][j] = (str[0] == 'F') ? 1 : 0;
            }
            if (i) {
                for (int j = 0; j < m; ++j) {
                    if (Map[i][j]) {
                        Map[i][j] += Map[i - 1][j];
                    }
                }
            }
            for (int j = 0; j < m; ++j)
                h[j] = Map[i][j];
            ll ans = LargestRectangleInHistogram(m, h, st);
            MaxV = Max(ans, MaxV);
        }

        printf("%lld\n", MaxV * 3);
    }
    return 0;
}

