#include <iostream>

using namespace std;
typedef int hugeint;
//应不大于,以防乘法时溢出
const int Base = 1000; 
const int Capacity = 35;

struct xnum
{
    int Len;
    int Data[Capacity];
    xnum() : Len(0) {}
    xnum(const xnum& V) : Len(V.Len) {
        memcpy(Data, V.Data, Len * sizeof *Data);
    }
    xnum(int V) : Len(0) { 
        for (; V > 0; V /= Base) Data[Len++] = V % Base;
    }
    xnum(char S[]);
    xnum& operator=(const xnum& V) { 
        Len = V.Len;
        memcpy(Data, V.Data, Len * sizeof *Data); 
        return *this;
    }
    int& operator[](int Index) { return Data[Index]; }
    int operator[](int Index) const { return Data[Index]; }

    void print(){
        printf("%d",Len==0?0:Data[Len-1]);
        for(int i=Len-2;i>=0;i--)
            for(int j=Base/10;j>0;j/=10)
                printf("%d",Data[i]/j%10);
    }
};

xnum::xnum(char S[])
{
    int I, J;
    Data[Len = 0] = 0;
    J = 1;
    for (I = strlen(S)-1; I>=0; I--) {
        Data[Len] += (S[I] - '0') * J;
        J *= 10;
        if (J >= Base) J = 1, Data[++Len] = 0;
    }
    if (Data[Len] > 0) Len++;
}

int compare(const xnum& A, const xnum& B)
{
    int I;
    if (A.Len != B.Len) return A.Len > B.Len ? 1 : -1;
    for (I = A.Len - 1; I >= 0 && A[I] == B[I]; I--);
    if (I < 0) return 0;
    return A[I] > B[I] ? 1 : -1;
}

xnum operator+(const xnum& A, const xnum& B)
{
    xnum R;
    int I;
    int Carry = 0;
    for (I = 0; I < A.Len || I < B.Len || Carry > 0; I++)
    {
        if (I < A.Len) Carry += A[I];
        if (I < B.Len) Carry += B[I];
        R[I] = Carry % Base;
        Carry /= Base;
    }
    R.Len = I;
    return R;
}

xnum operator-(const xnum& A, const xnum& B)
{
    xnum R;
    int Carry = 0;
    R.Len = A.Len;
    int I;
    for (I = 0; I < R.Len; I++)
    {
        R[I] = A[I] - Carry;
        if (I < B.Len) R[I] -= B[I];
        if (R[I] < 0) Carry = 1, R[I] += Base;
        else Carry = 0;
    }
    while (R.Len > 0 && R[R.Len - 1] == 0) R.Len--;
    return R;
}

xnum operator*(const xnum& A, const int B)
{
    int I;
    if (B == 0) return 0;
    xnum R;
    hugeint Carry = 0;
    for (I = 0; I < A.Len || Carry > 0; I++)
    {
        if (I < A.Len) Carry += hugeint(A[I]) * B;
        R[I] = Carry % Base;
        Carry /= Base;
    }
    R.Len = I;
    return R;
}

xnum operator*(const xnum& A, const xnum& B)
{
    int I;
    if (B.Len == 0) return 0;
    xnum R;
    for (I = 0; I < A.Len; I++)
    {
        hugeint Carry = 0;
        for (int J = 0; J < B.Len || Carry > 0; J++)
        {
            if (J < B.Len) Carry += hugeint(A[I]) * B[J];
            if (I + J < R.Len) Carry += R[I + J];
            if (I + J >= R.Len) R[R.Len++] = Carry % Base;
            else R[I + J] = Carry % Base;
            Carry /= Base;
        }   
    }
    return R;
}

xnum operator/(const xnum& A, const int B)
{
    xnum R;
    int I;
    hugeint C = 0;
    for (I = A.Len - 1; I >= 0; I--)
    {
        C = C * Base + A[I];
        R[I] = C / B;
        C %= B;
    }
    R.Len = A.Len;
    while (R.Len > 0 && R[R.Len - 1] == 0) R.Len--;
    return R;
}

//div
xnum operator/(const xnum& A, const xnum& B)
{
    int I;
    xnum R, Carry = 0;
    int Left, Right, Mid;
    for (I = A.Len - 1; I >= 0; I--)
    {
        Carry = Carry * Base + A[I];
        Left = 0;
        Right = Base - 1;
        while (Left < Right)
        {
            Mid = (Left + Right + 1) / 2;
            if (compare(B * Mid, Carry) <= 0) Left = Mid;
            else Right = Mid - 1;
        }
        R[I] = Left;
        Carry = Carry - B * Left;
    }
    R.Len = A.Len;
    while (R.Len > 0 && R[R.Len - 1] == 0) R.Len--;
    return R;
}

//mod
xnum operator%(const xnum& A, const xnum& B)
{
    int I;
    xnum R, Carry = 0;
    int Left, Right, Mid;
    for (I = A.Len - 1; I >= 0; I--)
    {
        Carry = Carry * Base + A[I];
        Left = 0;
        Right = Base - 1;
        while (Left < Right)
        {
            Mid = (Left + Right + 1) / 2;
            if (compare(B * Mid, Carry) <= 0) Left = Mid;
            else Right = Mid - 1;
        }
        R[I] = Left;
        Carry = Carry - B * Left;
    }
    R.Len = A.Len;
    while (R.Len > 0 && R[R.Len - 1] == 0) R.Len--;
    return Carry;
}

istream& operator>>(istream& In, xnum& V)
{
    char Ch;
    for (V = 0; In >> Ch;)
    {
        V = V * 10 + (Ch - '0');
        if (cin.peek() <= ' ') break;
    }
    return In;
}

ostream& operator<<(ostream& Out, const xnum& V)
{
    int I;
    Out << (V.Len == 0 ? 0 : V[V.Len - 1]);
    for (I = V.Len - 2; I >= 0; I--) 
        for (int J = Base / 10; J > 0; J /= 10) 
            Out << V[I] / J % 10;
        return Out;
}

xnum gcd(xnum a,xnum b)
{
    if(compare(b,0)==0) return a;
    else return gcd(b,a%b); 
}

int div(char *A,int B)
{
    int I;
    int C = 0;
    int Alen=strlen(A);
    for (I = 0; I <Alen; I++)
    {
        C = C * Base + A[I]-'0';
        C %= B;
    }
    return C;
}

xnum C(int n,int m)
{
    int i;
    xnum sum = 1;

    for(i = n; i >= n-m+1; i --)
        sum = sum*i;
    for(i = 1; i <= m; i ++)
        sum = sum/i;

    return sum;
}

int n, m;
int a[101];
xnum x[1100], xx[1100];
int i, j, k;

int main() {
	while(scanf("%d %d", &n, &m) != EOF) {
		
		memset(x, 0, sizeof(x) );
		memset(xx, 0, sizeof(xx));

		for(i = 1; i <= m; i++) {
			a[i] = i;
		}

		for(i = 0; i <= 1000; i++) {
			xx[i] = 1;
		}

		for(i = 2; i <= m; i++) {
			for(j = 0; j <= n; j++) {
				for(k = 0; k + j <= n; k = k + a[i])
					x[j+k] = x[j+k] + xx[j];
			}
			for(j = 0; j <= n; j++) {
				xx[j] = x[j];
				x[j] = 0;
			}
		}

		xx[n].print(); printf("\n");
	}
	return 0;
}
