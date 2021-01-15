#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

//****** 二分图最大匹配模板(链式前向星) ******

const int VMAX = 3010;
const int EMAX = 9060010;

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
    //doAddEdge(v, u);
}

int BipartiteGraph::getMaxMatch() {
    //dye();
    int cnt = 0;
    memset(pre_, -1, sizeof(pre_));
    for (int i = 0; i <= vertexcount_; ++i) {
        if (1) {
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

int sqr(int x) {
    return x * x;
}

struct Point {
    int x, y;
    Point() {
        x = y = 0;
    }
    void read() {
        scanf("%d %d", &x, &y);
    }

    int dist(const Point& o) {
        return sqr(x - o.x) + sqr(y - o.y);
    }
}P[3010], Q[3010];
int V[3010], QA[3010];
BipartiteGraph bg;


void randArray(int m) {
    for (int i = 1; i <= m / 2; ++i) {
        int x = rand() % m + 1;
        int y = rand() % m + 1;
        if (x != y) {
            int tmp = QA[x];
            QA[x] = QA[y];
            QA[y] = tmp;
        }
    }
}

int main() {
    int t, cas = 0, T;
    int n, m;

    scanf("%d", &t);

    while (t--) {
        scanf("%d", &T);
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            P[i].read();
            scanf("%d", &V[i]);
            //V[i] = 0;

            V[i] *= T;
            V[i] *= V[i];
        }
        scanf("%d", &m);
        for (int i = 1; i <= m; ++i) {
            Q[i].read();
            QA[i] = i;
        }

        bg.initialize(n);
        for (int i = 1; i <= n; ++i) {
            randArray(m);
            for (int j = m; j >= 1; --j) {
                if (V[i] >= P[i].dist(Q[QA[j]])) {
                    bg.addEdge(i, QA[j]);
                }
            }
        }
        printf("Scenario #%d:\n%d\n\n", ++cas, bg.getMaxMatch());
    }


    return 0;
}