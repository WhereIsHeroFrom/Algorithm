#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
using namespace std;

#define eps 1e-6
#define LL __int64
#define MAXX 100002
#include <memory.h>

using namespace std;

const unsigned int MAXDIGITS = 1002;        // 大数的位数，即 10^MAXDIGITS
const unsigned int MAXN = 9999;             // 每个a[i]表示的最大数字  
const unsigned int DLEN = 4;                // MAXN的最大位数 

class BigNum {
public :
    int a[(MAXDIGITS + DLEN - 1) / DLEN + 1];
    int len;
    BigNum(){len = 1; memset(a, 0, sizeof(a));}
    BigNum(const LL b);
    BigNum(const char * buffer);
    BigNum(const BigNum & T);
    void Attach(const char * buffer);
    bool Bigger(const BigNum &) const;
    BigNum & operator=(const BigNum &);
    BigNum & Add(const BigNum &);
    BigNum & Sub(const BigNum &);
    BigNum operator+(const BigNum &) const;
    BigNum operator-(const BigNum &) const;
    BigNum operator*(const BigNum &) const;
    BigNum operator/(const int &) const;
    void Print();
};

BigNum::BigNum(const LL b) {
    LL c, d = b;
    len = 0;
    memset(a, 0, sizeof(a));
    while(d > MAXN) {
        c = d % (MAXN + 1);
        d = d / (MAXN + 1);
        a[len++] = c;
    }
    a[len++] = d;
}

BigNum::BigNum(const char * buffer) {
    Attach(buffer);
}

void BigNum::Attach(const char * buffer) {
    int i, j;
    int lst[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
    j = len = 0;
    memset(a, 0, sizeof(a));
    for(i = strlen(buffer) - 1; i >= 0; --i, ++j) {
        if(j >= DLEN) {
            j = 0;
            len++;
        }
        a[len] += lst[j] * (buffer[i] - '0');
    }
    len++;
    // 处理前导零 
    while(len > 1 && a[len - 1] == 0) len--;
}

BigNum::BigNum(const BigNum & T) : len(T.len)
{
    memcpy(a, T.a, sizeof(a));
}

bool  BigNum::Bigger(const BigNum & T) const {
    int ln;
    if(len > T.len) return true;
    else if(len == T.len){
        ln = len - 1;
        while(ln>=0 && a[ln] == T.a[ln]) ln--;
        if(ln >= 0 && a[ln] > T.a[ln]) return true;
        else return false;
    }
    else return false;
}

BigNum & BigNum::operator=(const BigNum & n){
    len = n.len;
    memcpy(a, n.a, sizeof(a));
    return *this;
}
BigNum & BigNum::Add(const BigNum & T){
    int i,big;
    big = T.len > len ? T.len : len;
    for(i = 0 ; i < big ; i++)
    {
        a[i] = a[i] + T.a[i];
        if(a[i] > MAXN)
        {
            a[i + 1]++;
            a[i] = a[i] - MAXN - 1;
        }
    }
    if(a[big] != 0) len = big + 1;
    else len = big;
    return *this;
}
BigNum & BigNum::Sub(const BigNum & T){
    int i,j,big;
    big = T.len > len ? T.len : len;
    for(i = 0 ; i < big ; i++)
    {
        if(a[i] < T.a[i])
        {
            j = i + 1;
            while(a[j] == 0) j++;
            a[j--]--;
            while(j > i) a[j--] += MAXN;
            a[i] = a[i] + MAXN + 1 - T.a[i];
        }
        else a[i] -= T.a[i];
    }
    len = big;
    while(len>1 && a[len - 1] == 0) len--;
    return *this;
}
BigNum BigNum::operator+(const BigNum & n) const{
    BigNum a = *this;
    a.Add(n);
    return a;
}
BigNum BigNum::operator-(const BigNum & T) const{
    BigNum b = *this;
    b.Sub(T);
    return b;
}

BigNum BigNum::operator*(const BigNum & T) const{
    BigNum ret;
    int i, j, up, temp1, temp;
    for(i = 0 ; i < len ; i++)
    {
        up = 0;
        for(j = 0 ; j < T.len ; j++)
        {
            temp = a[i] * T.a[j] + ret.a[i + j] + up;
            if(temp > MAXN)
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
        if(up != 0) ret.a[i + j] = up;
    }
    ret.len = i + j;
    while(ret.len>1 && ret.a[ret.len - 1] == 0) ret.len--;
    return ret;
}
BigNum BigNum::operator/(const int & b) const{
    BigNum ret;
    int i,down = 0;
    for(i = len - 1 ; i >= 0 ; i--)
    {
        ret.a[i] = (a[i] + down * (MAXN + 1)) / b;
        down = a[i] + down * (MAXN + 1) - ret.a[i] * b;
    }
    ret.len = len;
    while(ret.a[ret.len - 1] == 0) ret.len--;
    return ret;
}
void BigNum::Print() {
    int i;
    char format[10];
    sprintf(format, "%%0%dd", DLEN);
    printf("%d", a[len - 1]);
    for(i = len - 2 ; i >= 0 ; i--)
    {
        printf(format, a[i]);
    }
    putchar('\n');
}

struct Kou {
    int isCubic;
    int intPart;
    double doublePart;
    double value;
    Kou() {
        isCubic = false;
        reset(0, 0);
    }
    void reset(int iPart, double dPart) {
        intPart = iPart;
        doublePart = dPart;
    }
}K32[MAXX];

struct ansPath {
    int A, B;
    double A_Div_B;
    // -1未定义    0下整取得值    1上整取得值 
    int roundType;
    ansPath (){
        roundType = -1;
    }
};
int K;

#define MAXC 2010
class ContinuedFraction {
    int data[MAXC];
    int len;
    
    void getContinuedFractionRecursively(double val, int depth, int maxDepth);
    void reduceFractionRecursively(int depth, int maxDepth, LL& u, LL& d);
public:
    void getContinuedFraction(double val, int maxLength);
    void reduceFraction(int maxDepth, LL& u, LL& d);
    void printContinuedFraction();
    
    static ContinuedFraction& Instance() {
        static ContinuedFraction inst;
        return inst;
    }
};

void ContinuedFraction::getContinuedFractionRecursively(double val, int depth, int maxDepth) {
    if (depth == maxDepth) {
        return ;
    }
    data[depth] = int(val);
    val -= data[depth];
    val = 1 / val;
    getContinuedFractionRecursively(val, depth+1, maxDepth);
}
void ContinuedFraction::getContinuedFraction(double val, int maxLength) {
    len = maxLength;
    getContinuedFractionRecursively(val, 0, maxLength);
}

void ContinuedFraction::reduceFractionRecursively(int depth, int maxDepth, LL& u, LL& d) {
    if(depth == maxDepth) {
        u = data[depth];
        d = 1;
        return ;
    }
    reduceFractionRecursively(depth+1, maxDepth, u, d);
    LL temp = d;
    d = u;
    u = data[depth]*u + temp;
}

void ContinuedFraction::reduceFraction(int maxDepth, LL& u, LL& d) {
    reduceFractionRecursively(0, maxDepth, u, d);
}

void ContinuedFraction::printContinuedFraction() {
    printf("[");
    for(int i = 0; i < len; ++ i) {
        printf("%d,", data[i]);
    }
    printf("]\n");
} 


class Fraction {
    LL U, D;
public:
    Fraction() {
    }
    Fraction(LL u, LL d) {
        U = u;
        D = d;
    } 
    void reset(const Fraction &o) {
        U = o.U;
        D = o.D;
    }
    
    double value() {
        return U * 1.0 / D;
    }
    
    Fraction operator^(const Fraction& other) const {
        return Fraction(U+other.U, D+other.D);
    }
    
    // 计算最接近 K^(2/3)的分数 
    void getFraction(double val, Fraction l, Fraction r, LL maxD) {
        while(1) {
            Fraction mid = (l^r);
            if(mid.D > maxD) {
                BigNum LU(l.U);
                BigNum RD(r.D);
                BigNum LD(l.D);
                BigNum RU(r.U);
                
                BigNum U = (LU*RD+LD*RU);
                U = U*U*U;
                BigNum V = (LD*RD);
                V = V*V*V;
                
                bool isBigger = U.Bigger( V*8*(LL)K*K );
                if(isBigger) {
                    reset(l);
                }else {
                    reset(r);
                }
                return ;
            }
            if(mid.U > val*mid.D) {
                r = mid;
            }else {
                l = mid;
            }
        }
    }

    void Print() {
        printf("%I64d/%I64d\n", U, D);
    }
};



int main() {
    int t;
    int i;
    //freopen("output.txt", "w", stdout);
    for(i = 1; ; ++i) {
        int v = i*i*i;
        if(v > MAXX) break;
        K32[v].isCubic = true;
        K32[v].reset(i*i, 0);
    }
    for(i = 1; i < MAXX; ++i) {
        if(!K32[i].isCubic) {
            double v = pow(i*1.0, 2.0/3);
            K32[i].intPart = int(v + eps);
            K32[i].doublePart = v - K32[i].intPart;
            K32[i].value = v;
        }
    }
    
    K = 0;
    scanf("%d", &t);
    t = 100000;
    while(t--) {
        ++K;
        scanf("%d", &K);
        
        if(K32[K].isCubic) {
            printf("%d/%d\n", K32[K].intPart, 1);
            continue;
        }
        Fraction ans;
        ans.getFraction(K32[K].value, Fraction(K32[K].intPart, 1),  Fraction(K32[K].intPart+1, 1), 100000);
        ans.Print();
    }
    return 0;
} 