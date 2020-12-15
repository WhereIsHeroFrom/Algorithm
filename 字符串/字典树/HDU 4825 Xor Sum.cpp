#include <iostream>
#include <cstring>

using namespace std;

#define MAXNODES 4000100
#define LL __int64
#define MAXBIT 34
LL Pow2[MAXBIT];

void globalInit() {
	Pow2[0] = 1;
	for (int i = 1; i < MAXBIT; ++i) {
		Pow2[i] = Pow2[i - 1] << 1;
	}
}

struct trieNode {
	trieNode *sn[2];
};
trieNode nodes[MAXNODES];
int nodeId;

trieNode * getNode() {
	if (nodeId >= MAXNODES) while (1) {}
	trieNode *p = &(nodes[nodeId++]);
	p->sn[0] = p->sn[1] = NULL;
	return p;
}

void trieInit() {
	nodeId = 0;
}

void trieInsert(trieNode *root, int depth, LL val) {
	for (int i = depth; i >= 0; --i) {
		int sonBit = (Pow2[i] & val) ? 1 : 0;
		if (NULL == root->sn[sonBit]) {
			root->sn[sonBit] = getNode();
		}
		root = root->sn[sonBit];
	}
}

LL trieQuery(trieNode *root, int depth, LL val) {
	LL ans = 0;
	for (int i = depth; i >= 0; --i) {
		int sonBit = (Pow2[i] & val) ? 0 : 1;
		if (NULL == root->sn[sonBit]) {
			sonBit ^= 1;
		}
		root = root->sn[sonBit];
		if (sonBit & 1)
			ans |= Pow2[i];
	}
	return ans;
}

int main() {
	globalInit();
	int t, cas = 0;
	int i;
	int n, m;
	LL v;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &n, &m);
		trieInit();
		trieNode *root = getNode();
		for (i = 0; i < n; ++i) {
			scanf("%I64d", &v);
			trieInsert(root, MAXBIT - 1, v);
		}
		printf("Case #%d:\n", ++cas);
		while (m--) {
			scanf("%I64d", &v);
			LL ans = trieQuery(root, MAXBIT - 1, v);
			printf("%I64d\n", ans);
		}
	}

	return 0;
}

/*
100
6 100
4294967295 4294967294 4294967293 4294967292 4294967291 4294967290

4294967295 4294967294 4294967293 4294967292 4294967291 4294967290

100
6 10
7 6 4 3 1 0
9 8 7 6 5 4 3 2 1 0
*/