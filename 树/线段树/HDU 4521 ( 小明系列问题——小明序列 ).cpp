/*
    题意：给出N(N <= 10^5)个数的序列a[N](0<=a[i]<=10^5)和一个d(d <=10^5),求一个子序列
满足子序列任意两个数的差大于d，求序列的最长长度。 
    题解：线段树+DP。
    状态dp[i]表示第i个元素结尾，即第i个元素选中的最大长度。
    状态转移方程：dp[i] = {dp[j] + 1 | i-j>d && a[i]-a[j]>0 }
    那么令新序列中，这个元素前一个元素为a[j]，则需要满足 i - j > d。 
    在所有满足条件的j中，若dp[j]的最大值为T，那么dp[i] = T+1。
    于是，用线段树维护这个最大值，将所有输入的数+1，建立线段树的区间为[1, 100001]。 
    
    线段树和DP相互维护，线段树两步操作： 
    插入：循环枚举i，令 j=i-d-1，如果j>=0，则将dp[j]插入到线段树a[i]的位置。
    查询：在区间[1, a[i]-1]中找最大值T，如果没有则T=0，然后更新dp[i] = T+1。
     循环N次后，max{dp[i]| 0<=i<N}就是最后的答案。 
*/
#include <iostream>

using namespace std;

#define MAXN 100010
#define MAXNODES (1<<18)
#define INF 100000000
/////////////////////////////////////////////////////
//////////////////线段树-区间最值//////////////////// 
/////////////////////////////////////////////////////

typedef int TypeVal;
struct Node {
    Node* son[2];
    TypeVal min, max;
    
    Node() {
        reset();
    } 
    
    void reset() {
        min =  INF;
        max = -INF;
        son[0] = son[1] = NULL;
    }
    
    void update(TypeVal v) {
        if(v < min) {
            min = v;
        }
        if(v > max) {
            max = v;
        }
    }
    
    void update(Node* val) {
        if(val->min < min) {
            min = val->min;
        }
        if(val->max > max) {
            max = val->max;
        }
    }
};
typedef Node* NodePtr;

class SegTree {
    NodePtr nodes;

    int nodeCount;
    int intervalLength;
    
    NodePtr get_node(); 
    void insert(NodePtr&, int, int, int, int, TypeVal);
    void query(NodePtr&, int, int, int, int, NodePtr);
public:
    NodePtr treeRoot;
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
    root->update(val);
    
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
    
    // 完全包含，更新最值 
    if(l <= treeL && treeR <= r) {
        ans->update(root);
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

int n, d;
int a[MAXN];
int dp[MAXN];

int main() {
    int i, j;
    //freopen("in.txt", "r", stdin);
    //freopen("my.out.txt", "w", stdout); 
    while(scanf("%d %d", &n, &d) != EOF) {
        SegTree& st = SegTree::Instance();
        st.build_tree(100001);
        int Max = 0;
        for(i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            ++a[i];
            j = i-d-1;
            if(j >= 0) {
                st.insert_tree(a[j], a[j], dp[j]);
            }
            Node node;
            st.query_tree(1, a[i]-1, &node);
            
            dp[i] = 1;
            if(node.max != -INF) {
                dp[i] += node.max;
            }
            
            if( dp[i] > Max ) {
                Max = dp[i];
            }
        }
        printf("%d\n", Max);
    }
    return 0;
} 
