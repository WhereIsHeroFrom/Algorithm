#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

//****** 二分图最大匹配模板(链式前向星) ******

const int VMAX = 210;
const int EMAX = 40010;

struct Edge {
    int to, next;

    Edge() {}
    Edge(int _t, int _n) : to(_t), next(_n) {}
};

class BipartiteGraph {
public:
    BipartiteGraph();
    virtual ~BipartiteGraph();
    void initialize(int n);
    void addEdge(int u, int v);
    int getMaxMatch();
    void getMaxMatchPath(int& maxMatch, int left[], int right[]);
private:
    bool findMatch(int u);               // 匈牙利算法找增广路
    void dye();
    void dyeDFS(int fat, int u, int c);  // dfs 对顶点进行染色
    void doAddEdge(int u, int v);
private:
    // 注意这是：左、右点集加起来的数目
    int vertexcount_;

    //  链式前向星  
    Edge *edges_;                // 边集
    int edgecount_;              // 已用边数
    int head_[VMAX];             // 每个节点边集的链表头

    // 染色
    int color_[VMAX];

    int pre_[VMAX];              // 匈牙利算法找增广路时的 pre
    bool visit_[VMAX];           // 匈牙利算法找增广路时的 visit
};

BipartiteGraph::BipartiteGraph() :
edges_(NULL), vertexcount_(0)
{
    edges_ = new Edge[EMAX];
}

BipartiteGraph::~BipartiteGraph() {
    if (edges_) {
        delete[] edges_;
    }
}

bool BipartiteGraph::findMatch(int u) {
    // u -> v
    for (int e = head_[u]; ~e; e = edges_[e].next) {
        int v = edges_[e].to;
        if (!visit_[v]) {
            visit_[v] = true;
            int vpre = pre_[v];
            pre_[v] = u;
            if (vpre == -1 || findMatch(vpre)) {
                return true;
            }
            pre_[v] = vpre;
        }
    }
    return false;
}


void BipartiteGraph::dye() {
    memset(color_, -1, sizeof(color_));
    for (int i = 0; i <= vertexcount_; ++i) {
        dyeDFS(-1, i, 0);
    }
}

void BipartiteGraph::dyeDFS(int fat, int u, int c) {
    if (color_[u] != -1) {
        return;
    }
    color_[u] = c;
    for (int e = head_[u]; ~e; e = edges_[e].next) {
        int v = edges_[e].to;
        dyeDFS(u, v, 1 - c);
    }
}

void BipartiteGraph::doAddEdge(int u, int v) {
    edges_[edgecount_] = Edge(v, head_[u]);
    head_[u] = edgecount_++;
}

void BipartiteGraph::initialize(int n) {
    vertexcount_ = n;
    edgecount_ = 0;
    memset(head_, -1, sizeof(head_));
}

void BipartiteGraph::addEdge(int u, int v) {
    doAddEdge(u, v);
    doAddEdge(v, u);
}

int BipartiteGraph::getMaxMatch() {
    dye();
    int cnt = 0;
    memset(pre_, -1, sizeof(pre_));
    for (int i = 0; i <= vertexcount_; ++i) {
        if (color_[i] == 0) {
            memset(visit_, false, sizeof(visit_));
            if (findMatch(i)) {
                ++cnt;
            }
        }
    }
    return cnt;
}

void BipartiteGraph::getMaxMatchPath(int& maxMatch, int left[], int right[]) {
    maxMatch = getMaxMatch();
    int matchCnt = 0;
    for (int i = 0; i <= vertexcount_; ++i) {
        if (color_[i] == 1 && pre_[i] != -1) {
            left[matchCnt] = pre_[i];
            right[matchCnt] = i;
            ++matchCnt;
        }
    }
}

//****** 二分图最大匹配模板(链式前向星) ******

#define MAXN 110

int n, k;
int mat[MAXN][MAXN];
int has[MAXN];

BipartiteGraph bg;

int main() {
    int i, j;
    while (scanf("%d %d", &n, &k) != EOF && (n || k)) {
        memset(has, 0, sizeof(has));

        for (i = 1; i <= n; ++i) {
            for (j = 1; j <= n; ++j) {
                scanf("%d", &mat[i][j]);
                has[mat[i][j]] = 1;
            }
        }

        int ans[55] = { 0 };

        for (int r = 0; r <= 50; ++r) {
            if (has[r]) {
                bg.initialize(n + n);
                for (int i = 1; i <= n; ++i) {
                    for (int j = 1; j <= n; ++j) {
                        if (mat[i][j] == r) {
                            bg.addEdge(i, n + j);
                        }
                    }
                }
                if (bg.getMaxMatch() > k) {
                    ans[++ans[0]] = r;
                }

            }
        }

        if (ans[0] == 0) {
            printf("-1\n");
        }
        else {
            for (int i = 1; i <= ans[0]; ++i) {
                if (i > 1) printf(" ");
                printf("%d", ans[i]);
            }
            puts("");
        }
    }

    return 0;
}