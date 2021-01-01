/*
    并查集 + HASH + 逆序离线处理

    你妹的！！！！！ add 参数 里面 用的  1 和 -1，结果用了个 bool 

*/

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <set>

using namespace std;

const int MAXN = 20010;
int fset[MAXN];
int n, m, q;
multiset <int> vmap[MAXN];
multiset <int> edges[MAXN];
int val[MAXN];

const int MAXQ = 300010;
typedef multiset <int>::iterator multisetIter;

void init_set(int n) {
    for (int i = 1; i <= n; ++i) {
        fset[i] = i;
        vmap[i].clear();
        edges[i].clear();
    }
}

int find_set(int x) {
    return (fset[x] == x) ? x : fset[x] = find_set(fset[x]);
}

bool union_set(int x, int y) {
    int fx = find_set(x);
    int fy = find_set(y);
    if (fx != fy) {

        if (vmap[fx].size() > vmap[fy].size()){
            int tmp = fx; fx = fy; fy = tmp;
        }
        // 少的往多的合并：fx -> fy
        fset[fx] = fy;
        vmap[fy].insert(vmap[fx].begin(), vmap[fx].end());
        vmap[fx].clear();

        return true;
    }
    return false;
}

char ch[10];

struct Triple {
    char ot;
    int a, b;
    
    void read_char();
    void read_intpair();
    void readme();
}T[MAXQ];

void Triple::read_char() {
    scanf("%s", ch);
}

void Triple::read_intpair() {
    scanf("%d %d", &a, &b);
}

int fuck = 0;
void Triple::readme() {
    read_char();
    read_intpair();
    ot = ch[0];

    if (ot == 'E') {
        if (a > b) {
            int tmp = a;
            a = b;
            b = tmp;
        }
    }
}

struct Edge {
    int u, v;
    
    void read() {
        scanf("%d %d", &u, &v);
        if (u > v) {
            int tp = u;
            u = v;
            v = tp;
        }
    }

}E;


int ansval, anscnt;

void processQuery(int f, int K) {
    multisetIter it = vmap[f].lower_bound(K);
    if (it != vmap[f].end()) {
        ansval += (*it);
        //printf("%d\n", ((*it)));
    }
    ++anscnt;
}

void initEdge() {
    for (int i = 0; i < m; ++i) {
        E.read();
        edges[E.u].insert(E.v);
    }

}
void initQuery() {
    int i;

    for (i = 0; i < q; ++i) {
        T[i].readme();
        if (T[i].ot == 'E') {

            multisetIter it = edges[T[i].a].find(T[i].b);
            if (it != edges[T[i].a].end())
                edges[T[i].a].erase(it);
        }
        else if (T[i].ot == 'U') {
            /*int tp = val[T[i].a];
            val[T[i].a] = T[i].b;
            T[i].b = tp;*/
            swap(val[T[i].a], T[i].b);
        }
    }
    for (i = 1; i <= n; ++i) {
        vmap[i].insert(val[i]);
    }

    for (int i = 1; i <= n; i++) {
        for (multisetIter it = edges[i].begin(); it != edges[i].end(); it++) {
            union_set(i, (*it));
        }
    }
}

void updateMap(int root, int toval, int add) {
    if (add == 1) {
        vmap[root].insert(toval);
    }
    else {
        vmap[root].erase(vmap[root].find(toval));
    }
}
void postProcess() {
    ansval = anscnt = 0;
    int i;
    for (i = q - 1; i >= 0; --i) {
        if (T[i].ot == 'F') {
            processQuery(find_set(T[i].a), T[i].b);
        }
        else if (T[i].ot == 'U') {
            int fx = find_set(T[i].a);

            updateMap(fx, val[T[i].a], -1);
            val[T[i].a] = T[i].b;
            updateMap(fx, val[T[i].a], 1);
        }
        else if (T[i].ot == 'E')  {
            union_set(T[i].a, T[i].b);
        }

    }
}

int main() {

    int i, cas = 0;
    int x, y;
    //freopen("in.txt", "r", stdin);
    while (scanf("%d %d %d", &n, &m, &q) != EOF) {
        init_set(n);

        for (i = 1; i <= n; ++i) {
            scanf("%d", &x);
            val[i] = x;
        }

        initEdge();
        initQuery(); 
        postProcess();

        printf("Case %d: %.3lf\n", ++cas, ansval * 1.0 / anscnt);

    }

    return 0;
}
/*

int main() {

    freopen("in.txt", "w", stdout);
    int Q = 10;
    while (Q--) {
        int n = 20000, m = 60000, q = 300000;
        printf("%d %d %d\n", n, m, q);
        for (int i = 1; i <= n; ++i) {
            printf("%d\n", rand() % 10000);
        }
        for (int i = 1; i <= m; ++i) {
            printf("%d %d\n", rand() % n + 1, rand() % n + 1);
        }
        while (q--) {
            int v = rand() % 3;
            if (v == 0) {
                printf("F ");
            }
            else if (v == 1) {
                printf("E ");
            }
            else if (v == 2) {
                printf("U ");
            }
            printf("%d %d\n", rand() % n + 1, rand() % n + 1);
        }
    }


    return 0;
}*/

/*
10 5 7
9 8 7 6 5 -5 -6 -7 -8 -9
1 2
2 3
3 4
4 5

F 1 8
U 5 10
E 4 5
F 2 5
U 2 10
E 2 1
F 2 5
*/