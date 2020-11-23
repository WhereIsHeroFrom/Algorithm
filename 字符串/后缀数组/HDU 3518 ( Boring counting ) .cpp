#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 4010

int bucket[MAXN];         // 桶计数数组
int wx[MAXN], wy[MAXN];   // 排序辅助数组 
int key[MAXN];
int src[MAXN];

int sa[MAXN], rank[MAXN]; // 后缀数组、名次数组 
int height[MAXN];         // 前缀数组

void debug_print(int *src, int size) {
	for (int i = 0; i < size; i++) printf("%d ", src[i]);
	puts("");
}


int da_cmp(int *x, int a, int b, int l) {
	return x[a] == x[b] && x[a + l] == x[b + l];
}

// 基数排序
// 函数作用：对y[i]数组以key[i]为键值进行排序  (key, y)为一个键值对 
// 函数结果：排序结果存在sa数组中
void calculateSA(int *key, int *sa, int *y, int n, int m) {
	int i, j, *tmp = bucket;
	// 将m个桶置空 
	for (i = 0; i < m; i++) tmp[i] = 0;
	// 统计每个桶中需要放置的元素的个数 
	for (i = 0; i < n; i++) tmp[key[i]] ++;
	// 将所有的桶串起来 
	for (i = 1; i < m; i++) tmp[i] += tmp[i - 1];
	// 记录每个桶中对应的后缀编号 
	for (i = n - 1; i >= 0; i--) sa[--tmp[key[i]]] = y[i];
}

// 倍增算法

// val[i] 源字符串, 需要保证val[n-1]一定是字典序最小的字符 
// sa[i] 表示字典序排在第i个的后缀为suffix(sa[i])
// n 源字符串的长度
// m 源字符集合的最大字符+1 
void doublingAlgorithm(int *src, int *sa, int n, int m) {
	int i, j, p;
	int *x = wx, *y = wy, *t;
	memset(sa, 0, sizeof(sa));

	// 1.对一个字符的所有后缀进行基数排序
	for (i = 0; i < n; i++) {
		x[i] = src[i], y[i] = i;
	}
	calculateSA(x, sa, y, n, m);

	for (j = 1, p = 1; p < n; j *= 2, m = p) {

		for (p = 0, i = n - j; i < n; i++) y[p++] = i;
		for (i = 0; i < n; i++) if (sa[i] >= j) y[p++] = sa[i] - j;


		for (i = 0; i < n; i++) key[i] = x[y[i]];
		calculateSA(key, sa, y, n, m);


		// 通过sa数组来对名次数组进行反算
		// 这里需要比较相邻两个后缀sa[i-1]和sa[i]是否相等
		// 如果相等，x[ sa[i] ] = x[ sa[i-1] ];
		// 否则  x[ sa[i] ] 为之前没有出现过的一个新的编号 
		for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
			x[sa[i]] = da_cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;

	}
}

void lcprefix(int *src, int *sa, int n) {
	int i, j, k = 0;

	for (i = 0; i < n; i++) rank[sa[i]] = i;
	// h[i] >= h[i-1] - 1;
	for (i = 0; i < n; i++) {
		if (k) {
			k--;
		}
		for (j = sa[rank[i] - 1]; src[i + k] == src[j + k]; k++);
		height[rank[i]] = k;
	}
	// height[0] = 0  定义如此 
	// height[1] = 0  因为排名第0位的字符串永远是结尾的那个最小字符，所以字典序最小的两个后缀的公共前缀必定为空集 
}

char str1[MAXN];

int ABS(int v) {
	return v < 0 ? -v : v;
}

int Min(int a, int b) {
	return a < b ? a : b;
}

int Max(int a, int b) {
	return a > b ? a : b;
}


int main() {
	//doublingAlgorithm(test, sa, 9, 3); while(1);
	int i, j, k;
	while (scanf("%s", str1) != EOF) {
		if (strcmp(str1, "#") == 0) break;
		//for(i = 0; i < 1000; i++) str1[i] = i&1?'a':'b';
		//str1[i] = 0;

		int p = 0;
		for (i = 0; str1[i]; i++) {
			src[p++] = 1 + (str1[i] - 'a');
		}
		src[p++] = 0;
		doublingAlgorithm(src, sa, p, 28);
		lcprefix(src, sa, p);
		//debug_print(height, p);
		//debug_print(sa, p);

		int c = 0;
		for (int l = 1; l < p; l++) {
			int flag = 1;
			int min = p + 1, max = -1;
			for (i = 2; i < p; i++) {
				if (height[i] >= l) {
					if (!flag) continue;

					min = Min(min, Min(sa[i], sa[i - 1]));
					max = Max(max, Max(sa[i], sa[i - 1]));
					if (max - min >= l) {
						c++;
						flag = 0;
					}
				}
				else {
					flag = 1;
					min = p + 1;
					max = -1;
				}
			}
		}

		printf("%d\n", c);

	}
	return 0;
}
/*
aaaaaaaaa
aa
*/
