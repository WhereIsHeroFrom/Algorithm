/*
题意：
给定两种操作：
T A B : 将集合A中的元素合并到集合B；
Q A : 输出三个数： X （A所在集合）；Y （X集合中元素个数）Z (A迁移的次数)
题解：
并查集
前三个操作都是常规的并查集操作，求A的迁移次数 需要对路径压缩进行一些变形；
由于数据量较大，所以需要采用路径压缩，但是压缩路径会导致迁移次数回溯的时候漏
掉之前归并的集合（即并查集树的中间结点），所以在路径压缩的时候需要将集合树上
祖先结点的值都累加到当前结点本身。
*/
#include <iostream>

using namespace std;


#define MAXN 10010

int pre[MAXN];
int sum[MAXN], transTime[MAXN];

int unionset_find(int p) {
	int x = p;
	int sumT = 0;
	while (pre[p] != p) {
		sumT += transTime[p];
		p = pre[p];
	}
	sumT -= transTime[x];

	while (x != p) {
		transTime[x] += sumT;
		sumT -= transTime[pre[x]];
		int tmp = pre[x];
		pre[x] = p;
		x = tmp;
	}
	return p;
}

int unionset_union(int x, int y) {
	int fx = unionset_find(x);
	int fy = unionset_find(y);
	if (fx == fy) {
		return false;
	}
	else {
		pre[fx] = fy;
		sum[fy] += sum[fx];
		transTime[fx] ++;
		return true;
	}
}

int find_transtime(int p) {
	int cnt = 0;
	while (p != pre[p]) {
		cnt += transTime[p];
		p = pre[p];
	}
	return cnt;
}

int n, m;
char str[10];

int main() {
	int i;
	int t, cases = 1;
	scanf("%d", &t);

	while (t--) {
		scanf("%d %d", &n, &m);
		for (i = 1; i <= n; i++) {
			pre[i] = i;
			sum[i] = 1;
			transTime[i] = 0;
		}
		printf("Case %d:\n", cases++);
		while (m--) {
			scanf("%s", str);
			if (strcmp(str, "T") == 0) {
				int a, b;
				scanf("%d %d", &a, &b);
				unionset_union(a, b);
			}
			else {
				int a;
				scanf("%d", &a);
				int X = unionset_find(a);
				int Y = sum[X];
				int Z = find_transtime(a);
				printf("%d %d %d\n", X, Y, Z);
			}
		}

	}
	return 0;
}


/*
5
3 3
T 1 2
T 3 2
Q 2
3 4
T 1 2
Q 1
T 1 3
Q 1
*/