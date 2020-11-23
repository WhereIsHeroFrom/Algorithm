#include <iostream>

using namespace std;

#define MAXN 140000
#define maxv(a,b) a>b?a:b 

int n;
int c[MAXN];



int lowbit(int x) {
	return x & -x;
}

void add(int x, int val) {
	while (x <= n) {
		c[x] += val;
		x += lowbit(x);
	}
}

int sum(int x) {
	int s = 0;
	while (x) {
		s += c[x];
		x ^= lowbit(x);
	}
	return s;
}


struct treeNode {
	int max;
	void reset() {
		max = 0;
	}
}nodes[2 * MAXN];

treeNode *getNode(int id) {
	return &nodes[id];
}

void build_segtree(int p, int l, int r) {
	treeNode* now = getNode(p);
	now->reset();
	if (l < r) {
		int mid = (l + r) >> 1;
		build_segtree(p << 1, l, mid);
		build_segtree(p << 1 | 1, mid + 1, r);
	}
}

void insert_segtree(int p, int l, int r, int pos, int v) {
	if (l > r) {
		return;
	}
	treeNode *now = getNode(p);
	if (l > pos || pos > r) {
		return;
	}
	if (l == r) {
		now->max = v;
		return;
	}
	int mid = (l + r) >> 1;
	insert_segtree(p << 1, l, mid, pos, v);
	insert_segtree(p << 1 | 1, mid + 1, r, pos, v);

	now->max = maxv(getNode(p << 1)->max, getNode(p << 1 | 1)->max);
}

void query_segtree(int p, int l, int r, int s, int t, treeNode* ans) {
	if (t < l || s > r) {
		return;
	}
	treeNode *now = getNode(p);

	if (now->max <= ans->max) {
		return;
	}

	if (s <= l && r <= t) {
		ans->max = now->max;
		return;
	}

	int mid = (l + r) >> 1;
	query_segtree(p << 1, l, mid, s, t, ans);
	query_segtree(p << 1 | 1, mid + 1, r, s, t, ans);

}

int K[MAXN];
int finalArray[MAXN];
int ansv[MAXN];

int main() {
	int t, cases = 0;
	int i, j;
	scanf("%d", &t);

	while (t--) {
		scanf("%d", &n);
		for (i = 1; i <= n; i++) {
			scanf("%d", &K[i]);
			c[i] = 0;
		}
		for (i = 1; i <= n; i++) {
			add(i, 1);
		}
		for (i = n; i >= 1; i--) {
			int val = K[i] + 1;
			int l = 1, r = n, ans = -1;
			while (l <= r) {
				int mid = (l + r) >> 1;
				if (sum(mid) >= val) {
					ans = mid;
					r = mid - 1;
				}
				else {
					l = mid + 1;
				}
			}
			finalArray[ans] = i;
			add(ans, -1);
		}
		/*for(i = 1; i <= n; i++) {
		printf("%d ", finalArray[i]);
		}
		puts("");*/
		build_segtree(1, 1, n);

		for (i = 1; i <= n; i++) {
			treeNode s;
			s.reset();
			query_segtree(1, 1, n, 1, finalArray[i] - 1, &s);
			ansv[finalArray[i]] = s.max + 1;
			insert_segtree(1, 1, n, finalArray[i], s.max + 1);
		}
		printf("Case #%d:\n", ++cases);
		int maxans = 0;
		for (i = 1; i <= n; i++) {
			if (ansv[i] > maxans) maxans = ansv[i];
			printf("%d\n", maxans);

		}
		puts("");

	}

	return 0;
}

/*
6
6
0 0 2 2 3 1

10
0 1 0 1 0 0 2 3 4 0

17
0 1 0 2 0 3 0 4 0 1 0 2 3 4 5 6 7

7
0 1 2 3 2 1 0
*/