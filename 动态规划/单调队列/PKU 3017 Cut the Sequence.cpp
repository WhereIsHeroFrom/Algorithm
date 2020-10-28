#include <iostream>
#include <cstdio>

using namespace std;

#define LL __int64
#define MAXN 100010
#define INF -1

class Queue {
	public:
	int data[MAXN];
	int f, t;
	Queue() {
		f = t = 0;
	}
	void clear() {
		f = t = 0;
	}
	void push(int val) {
		data[ t++ ] = val;
	}
	void pop_front() {
		f ++;
	}
	void pop_tail() {
		t--;
	}
	int front() {
		return data[f];
	}
	int tail() {
		return data[t-1];
	}
	bool empty() {
		return f == t;
	}
};

int n;
LL M, dp[ MAXN ], sum[ MAXN ];
Queue maxQ;   // 存储满足条件窗口的最大值 
Queue rangeQ;
int pre[ MAXN ];
int a[ MAXN ];


int main() {
	int i, j;
		scanf("%d %I64d", &n, &M ); {
		bool noAns = false;
		sum[0] = 0;
		for(i = 1; i <= n; i++) {
			
			scanf("%d", &a[i]);
			dp[i] = INF;
			sum[i] = sum[i-1] + a[i];
			
			if ( a[i] > M ) {
				noAns = true;
			}
			
		}
		// 有一个数大于M的情况单独处理
		if ( noAns ) {
			printf("-1\n");
		}else {
			maxQ.clear();
			rangeQ.clear();
			
			
			dp[0] = 0;
			dp[1] = a[1];
			pre[1] = 0;
			
			maxQ.push(1);
			rangeQ.push(1);
			
			// 一定有解的情况 
			for(i = 2; i <= n; i++) {
				rangeQ.push(i);
				while ( sum[ rangeQ.tail() ] - sum[ rangeQ.front() - 1 ] > M ) {
					rangeQ.pop_front();
				}				
				
				while ( !maxQ.empty() ) {
					if ( a[i] >= a[ maxQ.tail() ] ) {
						maxQ.pop_tail();
					}else {
						break;
					}
				}
				maxQ.push(i);				
				while ( sum[ maxQ.tail() ] - sum[ maxQ.front() - 1 ] > M ) {
					maxQ.pop_front();
				}				
				
				dp[i] = dp[ rangeQ.front() - 1 ] + a[ maxQ.front() ];
				pre[i] = rangeQ.front() - 1;
				
				for (j = maxQ.f + 1; j < maxQ.t; j++ ) {
					int idx = maxQ.data[j];
					int preidx = maxQ.data[j-1];
					if( dp[preidx] + a[idx] < dp[i] ) {
						dp[i] = dp[preidx] + a[idx];
						pre[i] = preidx;
					}	
					
				}
			}
			
			printf("%I64d\n", dp[n]);
			/*for(i = 1; i <= n; i++) {
				printf("%d(%I64d) ", pre[i], dp[i]);
			}
			puts("");*/
		}
	}
	return 0;
}

/*
8 17
2 2 2 8 1 8 2 1

20 11
2 2 2 8 1 
8 2 1 9 8 
7 3 4 5 6 
7 1 2 8 9


-1 0 0 0 0 4 4 4 7 8 8 10 10 10 11 13 13 16 16 18
*/