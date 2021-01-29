#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

#define ll long long

struct ZeroOne {
    int one, zero;
    ZeroOne() {}
    ZeroOne(int o, int z) : one(o), zero(z) {
    }

    bool operator <= (const ZeroOne& o) const {
        return (ll)one * (o.one + o.zero) <= (ll)o.one* (one + zero);
    }

};

/***************************栈 模板***********************************/
typedef ZeroOne StackData;
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
/***************************栈 模板***********************************/

int A[MAXSTACK];
Stack st;

double sqr(double x) { return x*x; }

// 这个是最快的
char line[1000010];

void get() {
    int idx = 0, t = 0, s = 0, has = false;
    getchar();
    gets(line);

    while (line[idx]) {
        if (line[idx] >= '0' && line[idx] <= '9') {
            has = true;
            s = line[idx] - '0';
        }
        else {
            if (has) {
                A[t++] = s;
                s = 0;
                has = false;
            }

        }
        ++idx;
    }
    if (has) {
        A[t++] = s;
    }
}


int main() {
    int t;
    int n;
    scanf("%d", &t);

    while(t--) {
        st.clear();

        scanf("%d", &n);
        get();

        ZeroOne p;
        int i = 0;
        while (i < n) {
            p = ZeroOne(0, 0);
            while (i < n && A[i]) {
                ++p.one;
                ++i;
            }
            while (i < n && !A[i]) {
                ++p.zero;
                ++i;
            }

            if ( st.empty() || st.top() <= p ) {
                st.push(p);
            }
            else {
                while (!st.empty() && !(st.top() <= p)) {
                    ZeroOne tp = st.top();
                    st.pop();
                    p.one += tp.one;
                    p.zero += tp.zero;
                }
                st.push(p);
            }
        }

        double ans = 0;
        int startIdx = n - 1;
        while (!st.empty()) {
            ZeroOne zo = st.top();
            st.pop();
            int one = zo.one;
            int cnt = zo.one + zo.zero;
            double val = one * 1.0 / cnt;

            ans += sqr(val - 1) * one + sqr(val) * zo.zero;
        }
        printf("%.6lf\n", ans);

    }
    return 0;
}

/*
10
14
1 1 1 0 0 1 0 1 1 1 1 0 0 0
14
1 1 1 1 0 0 0 1 1 1 0 0 1 0

13
1 1 1 0 1 1 0 0 1 1 0 0 0

161 0 0 1 0 0 1 1 1 0 0 1 0 0 0 1200 1 1 1 1 1 0 0 0 0 0 1 1 1 0 1 0 1 0 0161 1 1 0 1 1 0 0 1 1 1 1 1 0 0 0121 1 1 0 1 1 0 0 1 1 1 01001 0 0 0 0 1 1 1 1 0 0 0 0 0 0 1 0 1 0 0 0 0 1 0 0 1 1 1 1 0 0 0 0 0 0 1 0 1 0 01 0 1 1 0 1 1 1 1 0 0 0 0 0 0 1 0 1 0 01 0 0 0 0 1 1 1 1 0 0 0 0 0 0 1 0 1 0 11 0 0 0 0 1 1 0 0 0 0 0 1 0 0 1 0 1 1 01 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 00 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 13.5555564.722222

*/