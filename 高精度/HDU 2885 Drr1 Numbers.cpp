#include <iostream> 
#include <cstdio>
#include <cstring>
#include <memory.h>

using namespace std;
#pragma warning(disable : 4996)
const unsigned int MAXDIGITS = 1010;         // 大数的位数，即 10^MAXDIGITS
const unsigned int MAXN = 9999;             // 每个a[i]表示的最大数字  
const unsigned int DLEN = 4;                // MAXN的最大位数 

class BigNum {
public:
    int a[(MAXDIGITS + DLEN - 1) / DLEN + 1];
    int len;
    BigNum() { len = 1; memset(a, 0, sizeof(a)); }
    BigNum(const int b);
    BigNum(const char* buffer);
    BigNum(const BigNum& T);
    void Attach(const char* buffer);
    bool Bigger(const BigNum&) const;
    BigNum& operator=(const BigNum&);
    BigNum& Add(const BigNum&);
    BigNum& Sub(const BigNum&);
    BigNum operator+(const BigNum&) const;
    BigNum operator-(const BigNum&) const;
    BigNum operator*(const BigNum&) const;
    BigNum operator/(const int&) const;
    int digitCount() const;
    int mod100000() const;
    void Print();
};

BigNum::BigNum(const int b) {
    int c, d = b;
    len = 0;
    memset(a, 0, sizeof(a));
    while (d > MAXN) {
        c = d % (MAXN + 1);
        d = d / (MAXN + 1);
        a[len++] = c;
    }
    a[len++] = d;
}

BigNum::BigNum(const char* buffer) {
    Attach(buffer);
}

void BigNum::Attach(const char* buffer) {
    int i, j;
    int lst[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000 };
    j = len = 0;
    memset(a, 0, sizeof(a));
    for (i = strlen(buffer) - 1; i >= 0; --i, ++j) {
        if (j >= DLEN) {
            j = 0;
            len++;
        }
        a[len] += lst[j] * (buffer[i] - '0');
    }
    len++;
    // 处理前导零 
    while (len > 1 && a[len - 1] == 0) len--;
}

BigNum::BigNum(const BigNum& T) : len(T.len)
{
    memcpy(a, T.a, sizeof(a));
}

bool  BigNum::Bigger(const BigNum& T) const {
    int ln;
    if (len > T.len) return true;
    else if (len == T.len) {
        ln = len - 1;
        while (ln >= 0 && a[ln] == T.a[ln]) ln--;
        if (ln >= 0 && a[ln] > T.a[ln]) return true;
        else return false;
    }
    else return false;
}

BigNum& BigNum::operator=(const BigNum& n) {
    len = n.len;
    memcpy(a, n.a, sizeof(a));
    return *this;
}
BigNum& BigNum::Add(const BigNum& T) {
    int i, big;
    big = T.len > len ? T.len : len;
    for (i = 0; i < big; i++)
    {
        a[i] = a[i] + T.a[i];
        if (a[i] > MAXN)
        {
            a[i + 1]++;
            a[i] = a[i] - MAXN - 1;
        }
    }
    if (a[big] != 0) len = big + 1;
    else len = big;
    return *this;
}
BigNum& BigNum::Sub(const BigNum& T) {
    int i, j, big;
    big = T.len > len ? T.len : len;
    for (i = 0; i < big; i++)
    {
        if (a[i] < T.a[i])
        {
            j = i + 1;
            while (a[j] == 0) j++;
            a[j--]--;
            while (j > i) a[j--] += MAXN;
            a[i] = a[i] + MAXN + 1 - T.a[i];
        }
        else a[i] -= T.a[i];
    }
    len = big;
    while (len > 1 && a[len - 1] == 0) len--;
    return *this;
}
BigNum BigNum::operator+(const BigNum& n) const {
    BigNum a = *this;
    a.Add(n);
    return a;
}
BigNum BigNum::operator-(const BigNum& T) const {
    BigNum b = *this;
    b.Sub(T);
    return b;
}

BigNum BigNum::operator*(const BigNum& T) const {
    BigNum ret;
    int i, j, up, temp1, temp;
    for (i = 0; i < len; i++)
    {
        up = 0;
        for (j = 0; j < T.len; j++)
        {
            temp = a[i] * T.a[j] + ret.a[i + j] + up;
            if (temp > MAXN)
            {
                temp1 = temp % (MAXN + 1);
                up = temp / (MAXN + 1);
                ret.a[i + j] = temp1;
            }
            else
            {
                up = 0;
                ret.a[i + j] = temp;
            }
        }
        if (up != 0) ret.a[i + j] = up;
    }
    ret.len = i + j;
    while (ret.len > 1 && ret.a[ret.len - 1] == 0) ret.len--;
    return ret;
}
BigNum BigNum::operator/(const int& b) const {
    BigNum ret;
    int i, down = 0;
    for (i = len - 1; i >= 0; i--)
    {
        ret.a[i] = (a[i] + down * (MAXN + 1)) / b;
        down = a[i] + down * (MAXN + 1) - ret.a[i] * b;
    }
    ret.len = len;
    while (ret.a[ret.len - 1] == 0) ret.len--;
    return ret;
}

void BigNum::Print() {
    int i;
    char format[10];
    sprintf(format, "%%0%dd", DLEN);
    printf("%d", a[len - 1]);
    for (i = len - 2; i >= 0; i--)
    {
        printf(format, a[i]);
    }
    putchar('\n');
}

int BigNum::digitCount() const {
    int ans = (len - 1) * DLEN;
    int num = a[len - 1];
    if (num < 10) {
        ++ans;
    }
    else if (num < 100) {
        ans += 2;
    }
    else if (num < 1000) {
        ans += 3;
    }
    else {
        ans += 4;
    }
    return ans;
}

int BigNum::mod100000() const {
    if (len == 1) {
        return a[len - 1];
    }
    return a[1] % 10 * 10000 + a[0];
}

#define ll long long
ll exp(ll a, ll b, ll c) {
    if (b == 0) {
        return 1 % c;
    }
    ll tmp = exp(a * a % c, b >> 1, c);
    if (b & 1) {
        tmp = tmp * a % c;
    }
    return tmp;
}

/*
    原数 y = 10A + B，其中 B 属于 [1,9]
    将 B 移动到 A 的前面，如果 A 本身是 x 位的数，则有：
    B * 10^x + A = Ty = T (10A + B)
    整理等式得到：
    A = B (10^x - T) / (10T - 1)
    其中 T 属于 [1,9]，B 属于 [1,9]，这两个数都是可以枚举的
    而 x 小于 1000，所以也是可以枚举的，
    利用快速幂 预判  (10T - 1) 是否整除  B(10^x - T)
    如果整除，则计算出 A 的值，A 的值必须严格满足   10^x <= A < 10^(x+1)
    对满足条件的数取模即可。

    y = 102564 = 10256 * 10 + 4
    4 * 10^5 + 10256 = 4 * 102564

    T = 4
    B = 4
    x = 5
    A = 10256
*/
const int maxn = 1002;
int ans[maxn];
BigNum P[maxn];

int main() {
    P[0] = 1;
    for (int i = 1; i < maxn; ++i) {
        P[i] = P[i - 1] * 10;
    }

    for (int B = 1; B <= 9; ++B) {
        for (int T = 1; T <= 9; ++T) {
            for (int x = 1; x <= 1000; ++x) {
                int mod = 10 * T - 1;
                int tot = B * (exp(10, x, mod) - T);
                if (tot % mod == 0) {
                    BigNum A = (P[x] - T) * B / mod;

                    //printf("%d %d %d\n", B, T, x);
                    //A.Print();
                    int dc = A.digitCount();
                    if (dc == x) {
                        BigNum Y = A * 10 + B;
                        //printf("--> %d\n", Y.mod100000());
                        ans[x + 1] += Y.mod100000();
                        ans[x + 1] %= 100000;
                    }
                }
            }
        }
    }
    for (int i = 2; i <= 1000; ++i) {
        ans[i] += ans[i - 1];
        ans[i] %= 100000;
    }
    int n;
    while (scanf("%d", &n) != EOF) {
        printf("%d\n", ans[n]);
    }

    return 0;
}

