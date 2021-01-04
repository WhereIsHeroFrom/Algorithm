#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

// RMQ 区间最小值询问

const int MAXM = 18;
const int MAXN = (1<<MAXM)+1;

// typedef __int64 ValueType;
// typedef double ValueType;
typedef int ValueType;
int lg2K[MAXN];

int RMQ_MinIndex(ValueType A[], int l, int r) {
    return A[r] < A[l] ? r : l;
}

// f[i][j] = opt(f[i-1][j], f[i-1][j + 2^{i-1}]);
void RMQ_Init(ValueType A[], int ALen, int(*f)[MAXN]) {
    int i, j, k = 0;
    for (i = 1; i <= ALen; i++) {
        lg2K[i] = k - 1;
        if ((1 << k) == i) k++;
    }
    for (i = 0; i < MAXM; i++) {
        for (j = 1; j + (1 << i) - 1 <= ALen; j++) {
            if (i == 0) {
                f[i][j] = j;
            }
            else {
                f[i][j] = RMQ_MinIndex(A, f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
}

/*
	设区间长度为2^k，则X表示的区间为[a, a + 2^k)，Y表示的区间为(b - 2^k, b]，
则需要满足一个条件就是X的右端点必须大于等于Y的左端点-1，即 a+2^k-1 >= b-2^k，
则2^(k+1) >= (b-a+1), 两边取对数（以2为底），得 k+1 >= lg(b-a+1)，则k >= lg(b-a+1) - 1。
k只要需要取最小的满足条件的整数即可( lg(x)代表以2为底x的对数 )。
*/
int RMQ_Query(ValueType A[], int(*f)[MAXN], int a, int b) {
	if (a == b) {
		return a;
	}
	else if (a > b) {
		a = a^b, b = a^b, a = a^b;
	}
	int k = lg2K[b - a + 1];
	return RMQ_MinIndex(A, f[k][a], f[k][b - (1 << k) + 1]);
}


ValueType fMax[MAXM][MAXN];
ValueType a[MAXN];
ValueType vMax[MAXN], sum[MAXN];
int Index[MAXN];

int Max(int x, int y) {
	return x > y ? x : y;
}

int main() {
	int n, m;
	int i;
	int L = 0;

	while(scanf( "%d %d", &n, &m ) != EOF && n) {
		a[0] = -100000000;
		L = 0;
		for(i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			if(a[i] != a[i-1]) {
				vMax[++L] = 1;
			}else {
				++vMax[L];
			}
			Index[i] = L;
		}
		sum[0] = 0;
		for(i = 1; i <= L; ++i) {
			sum[i] = sum[i-1] + vMax[i];
			//printf("%d %d\n", sum[i], vMax[i]);
			
			vMax[i] = -vMax[i];
		}
		RMQ_Init(vMax, L, fMax);
		
		while(m--) {
			int l, r;
			int idxl, idxr;
			scanf("%d %d", &l, &r);
			
			idxl = Index[l];
			idxr = Index[r];
			
			int ans = 0;
			if(idxl == idxr) {
				ans = r - l + 1;
			}else if( idxl + 1 <= idxr ) {
				ans = Max(sum[idxl] - l + 1,
				r - sum[idxr - 1] );
				
				if( idxl + 1 != idxr ) {
					int v = - vMax[ RMQ_Query(vMax, fMax, idxl + 1, idxr - 1) ];
					ans = Max(ans, v);
				}
			}
			printf("%d\n", ans);
		}
		
	} 
	
	
	return 0;
}
/*

10 10
-1 -1 1 1 1 1 3 10 10 10
2 3
1 10
5 10
3 6


idx|i|sum[i]
1  1   2
2  1   2
3  2   6
4  2   6
5  2   6
6  2   6
7  3   7
8  4  10
9  4  10
10 4  10
*/

