#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

//****** 二分图最大匹配模板(链式前向星) ******
// 顶点范围  左边的点[1, X]，右边的点[1,Y]

const int VMAX = 1510;
const int EMAX = 100000;

struct Edge {
    int to, next;

    Edge() {}
    Edge(int _t, int _n) : to(_t), next(_n) {}
};

class BipartiteGraph {
public:
    BipartiteGraph();
    virtual ~BipartiteGraph();
    void initialize(int lefts, int rights);
    void addEdge(int u, int v);
    int getMaxMatch();
private:
    bool findMatch(int u);       // 匈牙利算法找增广路
private:
    int leftsize_, rightsize_;   // 左、右点集的数目

    //  链式前向星  
    Edge *edges_;                // 边集
    int edgecount_;              // 已用边数
    int head_[VMAX];             // 每个节点边集的链表头

    int pre_[VMAX];              // 匈牙利算法找增广路时的 pre
    bool visit_[VMAX];           // 匈牙利算法找增广路时的 visit
};

BipartiteGraph::BipartiteGraph() :
edges_(NULL), leftsize_(0), rightsize_(0)
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

void BipartiteGraph::initialize(int lefts, int rights) {
    leftsize_ = lefts;
    rightsize_ = rights;
    edgecount_ = 0;
    memset(pre_, -1, sizeof(pre_));
    memset(head_, -1, sizeof(head_));
}


void BipartiteGraph::addEdge(int u, int v) {

    edges_[edgecount_] = Edge(v, head_[u]);
    head_[u] = edgecount_++;
}

int BipartiteGraph::getMaxMatch() {
    int cnt = 0;
    for (int i = 1; i <= leftsize_; ++i) {
        memset(visit_, false, sizeof(visit_));
        if (findMatch(i)) {
            ++cnt;
        }
    }
    return cnt;
}
//****** 二分图最大匹配模板(链式前向星) ******


int getValue(char *str) {
    int s0 = (str[0] - '0');
    if (str[0] == 'T') {
        s0 = 10;
    }
    else if (str[0] == 'J') {
        s0 = 11;
    }
    else if (str[0] == 'Q') {
        s0 = 12;
    }
    else if (str[0] == 'K') {
        s0 = 13;
    }
    else if (str[0] == 'A') {
        s0 = 14;
    }
    int s1;
    if (str[1] == 'H') {
        s1 = 4;
    }
    else if (str[1] == 'S') {
        s1 = 3;
    }
    else if (str[1] == 'D') {
        s1 = 2;
    }
    else {
        s1 = 1;
    }
    return s0 << 5 | s1;
}

char str[2][100][2];

int main() {
    BipartiteGraph bg;
    int i, j;
    int n, m;
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        bg.initialize(n, n);
        for (i = 0; i < 2; ++i) {
            for (j = 1; j <= n; ++j) {
                scanf("%s", str[i][j]);
            }
        }

        for (i = 1; i <= n; ++i) {
            for (j = 1; j <= n; ++j) {
                if (getValue(str[0][i]) < getValue(str[1][j])) bg.addEdge(i, j);
            }
        }

        printf("%d\n", bg.getMaxMatch());
    }

    return 0;
}
