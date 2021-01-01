/*
并查集 : 判奇环

利用启发式合并构造一棵深度不会超过 log(n) 的树；
可以通过 O(log(n)) 的时间内找到每个节点的深度；

输入的两个节点 (x,y)，分别计算 根(rx, ry)
1）rx == ry， 如果深度同奇偶，则存在奇环；否则不用处理；
2）rx != ry，如果深度不同奇偶，则需要将 最大深度小的那棵树增加一个伪根结点，然后再进行合并；

*/
#include <iostream>

using namespace std;


const int MAXN = 1003010;
int fset[MAXN], rk[MAXN];
int n;

void init_set(int n) {
    for (int i = 1; i < MAXN; ++i) {
        fset[i] = i;
        rk[i] = 0;
    }
}

int find_set(int x) {
    return (fset[x] == x) ? x : find_set(fset[x]);
}

int find_depth(int x) {
    return (fset[x] == x) ? 0 : 1 + find_depth(fset[x]);
}

int add_set(int x) {
    fset[x] = ++n;
    rk[fset[x]] = rk[x] + 1;
    return fset[x];
}

bool union_set(int x, int y) {
    int fx = find_set(x), fy = find_set(y);
    int dx = find_depth(x), dy = find_depth(y);
    bool bfit = (dx - dy) % 2;

    if (fx == fy) {
        // 根节点一样，则需要判断奇偶性，深度相减为偶数，说明出现了奇环
        return bfit;
    }
    if (bfit) {
        // 奇偶性 不一致的情况：深度小的那个需要增加一个 伪根 
        if (rk[fx] < rk[fy]) {
            fx = add_set(fx);
        }
        else {
            fy = add_set(fy);
        }
    }

    // 奇偶性 一致的情况：直接连接根
    if (rk[fx] == rk[fy]) {
        ++rk[fx];
        fset[fy] = fx;
    }
    else if (rk[fx] < rk[fy]) {
        fset[fx] = fy;
    }
    else {
        fset[fy] = fx;
    }

    return true;
}

enum QSType {
    QST_NOT_SURE = 0,
    QST_DIFF = 1,
    QST_SAME = 2
};

QSType quest_set(int x, int y) {
    int fx = find_set(x), fy = find_set(y);
    int dx = find_depth(x), dy = find_depth(y);
    bool bfit = (dx - dy) % 2;
    if (fx != fy) {
        return QST_NOT_SURE;
    }
    if (fx == fy) {
        return !bfit ? QST_SAME : QST_DIFF;
    }
}

void print_set(QSType tp) {
    if (tp == QST_NOT_SURE) printf("Not sure yet.\n");
    else if (tp == QST_DIFF) printf("In different gangs.\n");
    else if (tp == QST_SAME) printf("In the same gang.\n");
}

int main() {
    int t, cas = 0;
    int m, i, x, y;
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &m);
        init_set(n);
        bool f = false;
        char ch[10];

        for (i = 0; i < m; ++i) {
            scanf("%s %d %d", ch, &x, &y);
            if (ch[0] == 'D') {
                union_set(x, y);
            }
            else {
                print_set(quest_set(x, y));
            }
        }
    }

    return 0;
}