#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

/***************************栈 模板***********************************/
typedef int StackData;
const int MAXSTACK = 200010;

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
/***************************栈 模板***********************************/

struct Point {
    double x, y;
    void read() {
        scanf("%lf %lf", &x, &y);
        idx = -1;
    }
    int idx;

    bool operator < (const Point& o) {
        return x < o.x;
    }

}P[MAXSTACK];
double ans[MAXSTACK];

bool checkK(int pretop, int top, int cur) {
    // (P[pretop].y - P[top].y) / (P[pretop].x - P[top].x) <= (P[top].y - P[cur].y) / (P[top].x - P[cur].x)
    return (P[pretop].y - P[top].y) * (P[top].x - P[cur].x) <= (P[pretop].x - P[top].x) * (P[top].y - P[cur].y);
}

double Min(double a, double b) {
    if (a < -0.5) return b;
    if (b < -0.5) return a;
    return a < b ? a : b;
}


void calcStack(int size, Point *P, Stack& st) {
    st.clear();

    for (int i = 0; i < size; ++i) {
        if (P[i].idx == -1) {
            // building

            // 确保栈顶元素一定是 大于 当前元素的
            while (!st.empty() && P[st.top()].y <= P[i].y) st.pop();

            // 检查斜率
            while (st.size() >= 2 && checkK(st.pretop(), st.top(), i)) st.pop();

            st.push(i);

        }
        else {
            // people

            // 检查斜率
            while (st.size() >= 2 && checkK(st.pretop(), st.top(), i)) st.pop();

            ans[P[i].idx] += atan(P[st.top()].y / (P[i].x - P[st.top()].x));
        }
    }
}

Stack st;

const double PI = acos(-1.0);

int main() {
    int t, cas = 0;
    int n, q, tot;

    scanf("%d", &t);

    while (t--) {
        tot = 0;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            P[tot++].read();
        }
        scanf("%d", &q);
        for (int i = 0; i < q; ++i) {
            Point v;
            scanf("%lf", &v.x);
            v.y = 0;
            v.idx = i;
            P[tot++] = v;
            ans[i] = 0;
        }
        sort(P, P + tot);
        calcStack(tot, P, st);

        for (int i = 0; i < tot; ++i) P[i].x = -P[i].x;
        sort(P, P + tot);
        calcStack(tot, P, st);

        printf("Case #%d:\n", ++cas);

        for (int i = 0; i < q; ++i) {
            ans[i] = 180 - 180 * ans[i] / PI;
            if (fabs(ans[i]) < 1e-7) ans[i] = 0;
            printf("%lf\n", ans[i]);
        }


    }
    return 0;
}