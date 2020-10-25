// HDU 5918
// KMP
// 题意：有两个整数数列，数列a为：a[0], a[1] ... a[n-1]； 数列b为b[0], b[1] ... b[m-1]
// 给定一个数字 p，期望能够找到 q，满足 b = a[q], a[q+p] ... a[q+(m-1)p] 
// 求这样的 q 的数量；
// 题解：将数列a拆成p个数列，然后分别和b进行KMP，结果累加即可； 

#include <iostream>
#include <cstring>
using namespace std;

#pragma warning(disable:4996)

#define NULL_MATCH (-1)
#define MATCH_ALL 0 
#define Type int
#define MAXN 1000010

bool TypeEqualExact(Type a, Type b) {
	return a == b;
}

void GenNext(int *next, Type* M, int MLen) {
	// 0. 用 NULL_MATCH(-1) 代表一定没有真前缀，0的位置一定没有真前缀，所以为 NULL_MATCH
	int MPos = NULL_MATCH;
	next[0] = MPos;
	for (int TPos = 1; TPos < MLen; ++TPos) {
		// 1. M[TPos-MPos-1...TPos-1] 和 M[0...MPos] 完全匹配 
		//    检测 M[TPos] 和 M[MPos + 1] 是否匹配，不匹配，则找下一个 MPos' = next[MPos]；
		while (MPos != NULL_MATCH && !TypeEqualExact(M[TPos], M[MPos + 1]) )
			MPos = next[MPos];
		// 2. 正确匹配上，自增 MPos
		if ( TypeEqualExact(M[TPos], M[MPos + 1]) ) ++MPos;
		// 3. M[TPos-MPos...TPos] 和 M[0...MPos] 完全匹配 
		next[TPos] = MPos;
	}
}

int KMP(int *next, Type* M, int MLen, Type *T, int TLen) {
	// 1. 这里设置成 -1 的目的是：
	// 最初认为的情况是 目标串的空串 和 匹配串的空串 一定匹配
	int MPos = NULL_MATCH;
	int c = 0; 
	for (int TPos = 0; TPos < TLen; ++TPos) {
		// 2. 前提是 T[...TPos-1] == M[0...MPos] （MPos == -1 则代表两个空串匹配，同样成立)
		//    如果 T[TPos] != M[MPos + 1]，则 MPos = MPos' 继续匹配
		while (MPos != NULL_MATCH && !TypeEqualExact(T[TPos], M[MPos + 1])  )
			MPos = next[MPos];
		// 3. 当 T[TPos] == M[MPos + 1] 则 TPos++, MPos++;
		if ( TypeEqualExact(T[TPos], M[MPos + 1]) ) MPos++;
		// 4. 匹配完毕，返回 目标串 第一个匹配的位置
		if (MPos == MLen - 1) {
			++c;
			MPos = next[MPos];
		}
	}
	return c;
}



int Next[MAXN];
Type T[MAXN], TT[MAXN], M[MAXN];

Type a[MAXN], b[MAXN];

int main() {
	int n, m, p;
	int t;
	int i;
	int cas = 0;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d %d", &n, &m, &p);
		for (i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
		}
		for (i = 0;i < m; ++i) {
			scanf("%d", &b[i]);
		}
		GenNext(Next, b, m);
		int ans = 0;
		for(i = 0; i < p; ++i) {
			int s = i;
			int tLen = 0;
			while(s < n) {
				T[tLen ++] = a[s];
				s += p;
			}
			ans +=  KMP(Next, b, m, T, tLen);
		}
		
		printf("Case #%d: %d\n", ++cas, ans);
	}


}

/*
10

10 5 2
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1

10 5 2
1 1 1 2 2 1 1 1 1 1 
1 1 1 1 1

10 3 2
1 1 1 1 1 1 1 1 1 1 
1 1 1

6 3 1
1 2 3 1 2 3
1 2 3

6 3 2
1 3 2 2 3 1
1 2 3

5 3 2
1 3 2 2 3
1 2 3

8 2 2
1 1 3 3 1 1 3 3
1 3


*/
