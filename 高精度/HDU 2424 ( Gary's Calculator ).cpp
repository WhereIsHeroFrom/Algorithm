//高博的大数,王荣涛修改版
#include<stdio.h>
#include<memory.h>
#include<string.h>

const unsigned int MAXDIGITS = 1000; // (具体情况而定)      // maximal digits in the big number  
const unsigned int MAXN = 9999;        //(具体情况而定)        // maximal number to store in a single integer element a[i]  
// must be less than 9999 if * is used
const unsigned int DLEN = 4;                // the digits of the maximal number stored in each a[i]  

class BigNum
{
public :
    int a[(MAXDIGITS + DLEN - 1) / DLEN + 1]; // integer elements to hold a big number
    int len;
    BigNum(){len = 1; memset(a, 0, sizeof(a));}
    BigNum(const int b);
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

BigNum::BigNum(const int b)
{
    int c, d = b;
    len = 0;
    memset(a, 0, sizeof(a));
    while(d > MAXN)
    {
        c = d % (MAXN + 1);
        d = d / (MAXN + 1);
        a[len++] = c;
    }
    a[len++] = d;
}

  
BigNum::BigNum(const char * buffer)
{
    Attach(buffer);
}

// assign a C-Style string to a BigNum
void BigNum::Attach(const char * buffer)
{
    int i, j;
    int lst[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
    j = len = 0;
    memset(a, 0, sizeof(a));
    for(i = strlen(buffer) - 1; i >= 0; --i, ++j)
    {
        if(j >= DLEN)
        {
            j = 0;
            len++;
        }
        a[len] += lst[j] * (buffer[i] - '0');
    }
    len++;
    // to process strings such as "0000000001101001"
    while(len > 1 && a[len - 1] == 0) len--;
}

BigNum::BigNum(const BigNum & T) : len(T.len)
{       
    // if not all the big numbers are in the same size
    // this statement should be changed
    memcpy(a, T.a, sizeof(a));
}

bool  BigNum::Bigger(const BigNum & T) const
{
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
BigNum & BigNum::operator=(const BigNum & n)
{
    len = n.len;
    memcpy(a, n.a, sizeof(a));
    return *this;
}
BigNum & BigNum::Add(const BigNum & T)
{
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
BigNum & BigNum::Sub(const BigNum & T)
{
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
BigNum BigNum::operator+(const BigNum & n) const
{
    BigNum a = *this;
    a.Add(n);
    return a;
}
BigNum BigNum::operator-(const BigNum & T) const
{
    BigNum b = *this;
    b.Sub(T);
    return b;
}
BigNum BigNum::operator*(const BigNum & T) const
{
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
BigNum BigNum::operator/(const int & b) const
{
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
void BigNum::Print()
{
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



int n;
char str[100];
BigNum rt[100];
int stack[100];
int top;
int flag;
int i, j;

int main()
{
    int c = 1;
    while(scanf("%d", &n) != EOF)
    {
        flag = 0;
        top = 0;
        for(i = 0; i < n; i++)
        { 
            scanf("%s", str);
            if(!flag)
            {
               
                if(i & 1)
                {
                    if(str[0] != '+' && str[0] != '*')
                        flag = 1;
                    else
                        stack[top++] = str[0];
                }else
                {
                    if(str[0] == '+' || str[0] == '*')
                        flag = 1;
                    else
                        rt[top++] = BigNum(str);
                }
            }
        }


        printf("Case %d: ", c++);
        if(n % 2 == 0 || flag)
        {
            printf("Invalid Expression!\n");
        }else
        {
            while(1)
            {
                int flag = 0;
                for(i = 1; i < top; i += 2)
                {
                    if(stack[i] == '*')
                    {
                        flag = 1;
                        rt[i-1] = rt[i-1] * rt[i+1];

                        for(j = i+1; j < top; j += 2)
                        {
                            rt[j] = rt[j+2];
                        }

                        for(j = i; j < top; j += 2)
                        {
                            stack[j] = stack[j+2];
                        }
                        top -= 2;
                    }
                }

                if(!flag)
                    break;
            }

            BigNum sum = BigNum(0);
            for(i = 0; i < top; i++)
            {
                sum = sum + rt[i];
            }

            sum.Print();
        }
    }
}

