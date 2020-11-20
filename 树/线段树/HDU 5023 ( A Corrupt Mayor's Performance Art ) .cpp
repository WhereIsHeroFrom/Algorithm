/*
lazy思想
染色模型
适合颜色数目较少(64以内)的区间染色问题。
具体操作：
1、对某个连续区间进行染色。
2、询问某个连续区间的颜色情况（种类、数目等等）。
适用题型：
poj 2777 Count Color
hdu 5023 A Corrupt Mayor's Performance Art
结点存储
颜色值的位或colorBit：每个颜色用2的幂来表示，颜色值表示分别为1、2、4、8...，该区间有哪些颜色就可以用他们的或来表示
延迟标记lazy：该段区间完全被染色成了lazy这种颜色，这里的lazy要么是2的幂，要么是0

接口说明
giveLazyToSon      传递延迟标记给两个子结点（调用子结点的updateByValue，并且lazy重置）
updateByValue      通过某个颜色值更新当前结点信息（更新colorBit、lazy）
updateFromSon      通过两个子结点更新当前结点信息（更新colorBit）
mergeQuery         询问时用于对分割后的子结点进行合并用，不同情况实现不同

调用说明
建树：              调用静态函数   treeNode::segtree_build(1, 1, n);
插入([x, y], val)： 调用静态函数   treeNode::segtree_insert(1, 1, n, x, y, val);
询问([x, y]):       调用静态函数   treeNode::segtree_query(1, 1, n, x, y, ans);

*/
#include <iostream>

using namespace std;

#define MAXN 1048576
typedef int ValueType;


// 返回[l, r]和[x, y]两条线段是否相交
bool is_intersect(int l, int r, int x, int y) {
	return !(r < x || l > y);
}
// 返回[x, y]是否完全包含[l, r]
bool is_contain(int l, int r, int x, int y) {
	return x <= l && r <= y;
}

struct treeNode {
	ValueType lazy;
	ValueType colorBit;
	int pid;
	int len;

	treeNode() {
		reset(-1, 0);
	}
	void reset(int p, int _len) {
		pid = p;
		colorBit = 0;
		lazy = 0;
		len = _len;
	}
	int lson() { return pid << 1; }
	int rson() { return pid << 1 | 1; }

	void updateByValue(ValueType _val);
	void giveLazyToSon();
	void updateFromSon();

	// 询问的时候将结点合并后计入答案
	void mergeQuery(int p);

	// 建树 
	static void segtree_build(int p, int l, int r);
	// 插入线段[x, y]到[l, r]
	static void segtree_insert(int p, int l, int r, int x, int y, ValueType val);
	// 区间询问[x, y]上的信息
	static void segtree_query(int p, int l, int r, int x, int y, treeNode& ans);

};

/* 全局变量
nodes[MAXN*2] 存储所有静态线段树结点(动态开内存太费时间)
totalNodes    存储结点数目
*/
treeNode nodes[MAXN * 2];

void treeNode::updateByValue(ValueType _val) {
	lazy = _val;
	colorBit = _val;
}

void treeNode::giveLazyToSon() {
	if (lazy) {
		nodes[lson()].updateByValue(lazy);
		nodes[rson()].updateByValue(lazy);
		lazy = 0;
	}
}

void treeNode::updateFromSon() {
	colorBit = nodes[lson()].colorBit | nodes[rson()].colorBit;
}

void treeNode::mergeQuery(int p) {
	colorBit |= nodes[p].colorBit;
}

void treeNode::segtree_build(int p, int l, int r) {
	// 创建线段树结点的时候只需要知道该线段树结点管辖区间的长度，区间端点不用存，可以在递归的时候作为函数传参
	nodes[p].reset(p, r - l + 1);
	nodes[p].colorBit = (1 << 1);
	if (l < r) {
		int mid = (l + r) >> 1;
		// 递归创建左右儿子结点
		treeNode::segtree_build(p << 1, l, mid);
		treeNode::segtree_build(p << 1 | 1, mid + 1, r);
		nodes[p].updateFromSon();
	}
}

void treeNode::segtree_insert(int p, int l, int r, int x, int y, ValueType val) {
	if (!is_intersect(l, r, x, y)) {
		return;
	}
	if (is_contain(l, r, x, y)) {
		nodes[p].updateByValue(val);
		return;
	}
	nodes[p].giveLazyToSon();
	int mid = (l + r) >> 1;
	treeNode::segtree_insert(p << 1, l, mid, x, y, val);
	treeNode::segtree_insert(p << 1 | 1, mid + 1, r, x, y, val);
	nodes[p].updateFromSon();
}

void treeNode::segtree_query(int p, int l, int r, int x, int y, treeNode& ans) {
	if (!is_intersect(l, r, x, y)) {
		return;
	}
	if (is_contain(l, r, x, y)) {
		ans.mergeQuery(p);
		return;
	}
	nodes[p].giveLazyToSon();
	int mid = (l + r) >> 1;
	treeNode::segtree_query(p << 1, l, mid, x, y, ans);
	treeNode::segtree_query(p << 1 | 1, mid + 1, r, x, y, ans);
	nodes[p].updateFromSon();
}

int n, m;
int main() {
	int i;
	while (scanf("%d %d", &n, &m) != EOF && (n || m)) {
		treeNode::segtree_build(1, 1, n);
		int maxz = 2;
		while (m--) {
			char str[10];
			int x, y, z;
			scanf("%s %d %d", str, &x, &y);
			if (str[0] == 'P') {
				scanf("%d", &z);
				treeNode::segtree_insert(1, 1, n, x, y, 1 << z - 1);
				if (z > maxz) {
					maxz = z;
				}
			}
			else {
				treeNode ans;
				treeNode::segtree_query(1, 1, n, x, y, ans);
				bool flag = false;
				for (i = 0; i < 30; i++) {
					if ((1 << i) & ans.colorBit) {
						if (flag) {
							printf(" ");
						}
						flag = 1;
						printf("%d", i + 1);
					}
				}
				puts("");
			}
		}
	}
	return 0;
}