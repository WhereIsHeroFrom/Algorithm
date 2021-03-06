#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 100010
#define MAXNODES (1<<18)
#define INF -100000000
/////////////////////////////////////////////////////
//////////////////线段树-区间最值//////////////////// 
/////////////////////////////////////////////////////

typedef int TypeVal;
struct Node {
    Node* son[2];
    TypeVal max;
    
    Node() {
        reset();
    }
    void reset() {
        max = INF;
        son[0] = son[1] = NULL;
    }
};
typedef Node* NodePtr;

class SegTree {
    NodePtr nodes;
    NodePtr treeRoot;
    int nodeCount;
    int intervalLength;
    
    NodePtr get_node(); 
    void insert(NodePtr&, int, int, int, int, TypeVal);
    void query(NodePtr&, int, int, int, int, NodePtr);
public:
    
    SegTree () {
        // MAXNODES为比MAXN大，且最小2的幂的两倍 
        nodes = new Node[MAXNODES];
    }
    
    ~SegTree() {
        delete [] nodes; 
    } 
    void build_tree(int len);
    void insert_tree(int l, int r, TypeVal val);
    void query_tree(int l, int r, NodePtr ans);
    
    static SegTree& Instance() {
        static SegTree inst;
        return inst;
    }
};

NodePtr SegTree::get_node() {
    return &nodes[nodeCount++];
}

/*
    将区间[l, r]插入到 以root为根的子树（区间为 [treeL, treeR]）  
*/
void SegTree::insert(NodePtr& root, int treeL, int treeR, int l, int r, TypeVal val) {
    // 区间无交集，非法插入 
    if(treeR < l || r < treeL) {
        return ;
    }
    // 如果这个结点未定义，则生成新结点 
    if(root == NULL) {
        root = get_node();
        root->reset();
    }
    // 更新最优解 
    if(val > root->max) root->max = val;
    
    // 叶子结点 
    if(treeL == l && treeR == r) {
        return ;
    }
    
    int treeMid = (treeL + treeR) >> 1;
    insert(root->son[0], treeL, treeMid, l, r, val);
    insert(root->son[1], treeMid+1, treeR, l, r, val);
}

void SegTree::query(NodePtr& root, int treeL, int treeR, int l, int r, NodePtr ans) {
    // 区间无交集，非法插入 
    if(treeR < l || r < treeL) {
        return ;
    }
    // 当前区间中无数据，无法更新 
    if(root == NULL) {
        return ;
    }
    if(root->max <= ans->max) {
        return ;
    }
    
    // 完全包含，更新最值 
    if(l <= treeL && treeR <= r) {
        ans->max = root->max;
        return ;
    }
    int treeMid = (treeL + treeR) >> 1;
    query(root->son[0], treeL, treeMid, l, r, ans);
    query(root->son[1], treeMid+1, treeR, l, r, ans);
}

void SegTree::build_tree(int len) {
    intervalLength = len;
    nodeCount = 0;
    treeRoot = NULL;
}

void SegTree::insert_tree(int l, int r, TypeVal val) {
    insert(treeRoot, 1, intervalLength, l, r, val);
}

void SegTree::query_tree(int l, int r, Node* ans) {
    query(treeRoot, 1, intervalLength, l, r, ans);
}

int p, q;
int women[MAXN], men[MAXN];
int menPos[MAXN];
int womenLike[MAXN];

vector <int> womenRelatives[MAXN];

void init() {
    int i;
    for(i = 1; i < MAXN; ++i) {
        womenRelatives[i].clear();
    }
}

int womenHash[MAXN], cases;
int relativeWomen[MAXN];

struct Men {
    int id;
    int pos;
    Men() {}
    Men(int _id, int _pos) {
        id = _id;
        pos = _pos;
    }

    bool operator < (const Men& other) {
        return pos > other.pos;
    }
}likeMen[MAXN];
int likeMenCnt;

void resetWomen() {
    ++cases;
    relativeWomen[0] = 0;
    likeMenCnt = 0;
}

bool womenExist(int w) {
    return womenHash[w] == cases;
}

void addWomen(int w) {
    womenHash[w] = cases;
    relativeWomen[ ++relativeWomen[0] ] = w;
}

void addLikeMen(int m) {
    likeMen[ likeMenCnt++ ] = Men(m, menPos[m]);
}

void dfs(int u) {
    if(womenExist(u)) {
        return;
    }
    addWomen(u);
    for(int i = womenRelatives[u].size()-1; i >= 0; --i) {
        dfs(womenRelatives[u][i]);
    }
}

int dp[MAXN];

int main() {
    int i, j;
    while(scanf("%d %d", &p, &q) != EOF) {
        init();
        SegTree& st = SegTree::Instance();
        st.build_tree(q);
        for(i = 1; i <= p; ++i) {
            scanf("%d", &women[i]);
        }
        for(i = 1; i <= q; ++i) {
            scanf("%d", &men[i]);
            dp[i] = 0;
            menPos[ men[i] ] = i;
        }

        for(i = 1; i <= p; ++i) {
            scanf("%d", &womenLike[i]);
        }

        int t;
        scanf("%d", &t);
        while(t--) {
            int x, y;
            scanf("%d %d", &x, &y);
            womenRelatives[x].push_back(y);
            womenRelatives[y].push_back(x);
        }

        int Max = 0;
        for(i = 1; i <= p; ++i) {
            resetWomen();
            dfs(women[i]);
            for(j = 1; j <= relativeWomen[0]; j++) {
                int w = relativeWomen[j];
                addLikeMen(womenLike[w]);
            }
            sort(likeMen, likeMen + likeMenCnt);
            //printf("<<<<<<%d>>>>>\n", women[i]);
            //for(j = 0; j < likeMenCnt; ++j) { 
                //printf("%d ", likeMen[j].pos);
            //}
            //puts("");
            for(j = 0; j < likeMenCnt; ++j) {
                if(j && likeMen[j].pos == likeMen[j-1].pos) continue;
                Node ans;
                st.query_tree(1, likeMen[j].pos-1, &ans);
                int v = 0;
                if(ans.max == INF) {
                    v = 1;
                }else {
                    v = ans.max + 1;
                }
                int ps = likeMen[j].pos;
                if(v > dp[ps]) {
                    dp[ps] = v;
                    st.insert_tree(ps, ps, v);
                }

                if(v > Max) {
                    Max = v;
                }
            } 
        }
        printf("%d\n", Max);
    }
    return 0;
} 
/*
10 5
1 5 6 7 4 3 2 9 10 8
5 4 1 2 3
1 1 2 5 4 3 3 2 1 4
5
1 2
1 9
4 10
7 10
6 8
*/
