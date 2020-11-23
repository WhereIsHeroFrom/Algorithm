#include <iostream> 
#include <cstdio>
#include <cstring>
#include <memory.h>

using namespace std;

const unsigned int MAXDIGITS = 210;        // 大数的位数，即 10^MAXDIGITS
const unsigned int MAXN = 9999;             // 每个a[i]表示的最大数字  
const unsigned int DLEN = 4;                // MAXN的最大位数 

class BigNum {
public:
	int a[(MAXDIGITS + DLEN - 1) / DLEN + 1];
	int len;
	BigNum(){ len = 1; memset(a, 0, sizeof(a)); }
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
	void PrintEx();
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

BigNum::BigNum(const char * buffer) {
	Attach(buffer);
}

void BigNum::Attach(const char * buffer) {
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

BigNum::BigNum(const BigNum & T) : len(T.len)
{
	memcpy(a, T.a, sizeof(a));
}

bool  BigNum::Bigger(const BigNum & T) const {
	int ln;
	if (len > T.len) return true;
	else if (len == T.len){
		ln = len - 1;
		while (ln >= 0 && a[ln] == T.a[ln]) ln--;
		if (ln >= 0 && a[ln] > T.a[ln]) return true;
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
BigNum & BigNum::Sub(const BigNum & T){
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
BigNum BigNum::operator/(const int & b) const{
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

void BigNum::PrintEx() {
	if (len < 4) {
		Print();
		return;
	}
	else if (len == 4) {
		if (a[len - 1] < 1000) {
			Print();
			return;
		}
	}
	len = 4;
	a[len - 1] %= 1000;

	int i;
	char format[10];
	sprintf(format, "%%0%dd", DLEN - 1);
	printf(format, a[len - 1]);
	sprintf(format, "%%0%dd", DLEN);
	for (i = len - 2; i >= 0; i--)
	{
		printf(format, a[i]);
	}
	putchar('\n');

}
#define MAXL 10

struct Cyclic {
	int size;
	int a[MAXL];
	int visit[MAXL];

	Cyclic() {
	}

	Cyclic(char* str) {
		size = strlen(str) - 1;
		int i;
		for (i = 1; i <= size; ++i) {
			a[i] = str[i] - '0';
		}
	}

	Cyclic rotate120() {
		Cyclic ret;
		ret.size = size;

		ret.a[5] = a[5];
		ret.a[4] = a[4];

		ret.a[1] = a[7];
		ret.a[7] = a[6];
		ret.a[6] = a[1];

		ret.a[2] = a[3];
		ret.a[3] = a[8];
		ret.a[8] = a[2];

		return ret;
	}

	int getLoopCount() {
		int i, pos, cnt = 0;
		for (i = 1; i <= size; ++i) {
			visit[i] = 0;
		}
		for (i = 1; i <= size; ++i) {
			if (!visit[i]) {
				++cnt;
				visit[i] = 1;
				pos = a[i];
				while (!visit[pos]) {
					visit[pos] = 1;
					pos = a[pos];
				}
			}
		}
		return cnt;
	}
};

char pos[8][10] = {
	"X34781256",
	"X65872143",
	"X42863175",
	"X86754231",
	"X12345678",
	"X51736284",
	"X31427586",
	"X62518473",
};

BigNum power(BigNum x, int c) {
	BigNum ret = 1, tmp = x;
	while (c) {
		if (c & 1) {
			ret = ret * tmp;
		}
		tmp = tmp * tmp;
		c >>= 1;
	}
	return ret;
}

BigNum ans;
int main() {
	int i, j, t, cases = 0;
	int C;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &C);
		ans = 0;
		for (i = 0; i < 8; ++i) {
			Cyclic c(pos[i]);
			for (j = 0; j < 3; ++j) {
				ans = ans + power(C, c.getLoopCount());
				c = c.rotate120();
			}
		}
		ans = ans / 24;
		printf("Case %d: ", ++cases);
		ans.PrintEx();
	}
	return 0;
}