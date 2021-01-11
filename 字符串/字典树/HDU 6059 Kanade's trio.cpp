/*
    6   TLE   对数组访问特别耗时
    （比如 500000 * 64 的数组，取元素的时候非常耗时）
*/

#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

typedef int TrieData;
typedef long long AnsType;                   // 修改点 1
typedef int ValueType;                       // 修改点 2
const int MAXBIT = 32;                       // 修改点 3

const int TRIE_NODE_CACHES = MAXBIT * 500010;
const int TRIE_NODE_COUNT = 2;
const int TRIE_DATA_INIT = 0;
const int TRIE_NODE_NULL = -1;

#define samebit(i) ((v & ((ValueType)1 << i)) ? 1 : 0)
#define diffbit(i) ((v & ((ValueType)1 << i)) ? 0 : 1)


// 字典树结点类
class TrieNode {
private:
    bool isword_;                 // 是否是1个完整单词
    int num_;                     // 有多少个单次经过这个结点
    TrieData td_;                 // 每个结点的权值，用来作一些特殊用途
    int nodes_[TRIE_NODE_COUNT];  // 注意这里存的是结点内存池的下标，相比存指针的好处是：字节数少一半

public:
    inline void setNode(int nodeIdx, int node) {
        nodes_[nodeIdx] = node;
    }
    inline int getNode(int nodeIdx) {
        return nodes_[nodeIdx];
    }
    inline bool hasNode(int nodeIdx) {
        // 结点范围判断
        if (nodeIdx < 0 || nodeIdx >= TRIE_NODE_COUNT) {
            return false;
        }
        return nodes_[nodeIdx] != TRIE_NODE_NULL;
    }
    inline void reset() {
        resetData();
        memset(nodes_, TRIE_NODE_NULL, sizeof(nodes_));
    }
    inline void resetData(){
        num_ = 0;
        isword_ = false;
        td_ = TRIE_DATA_INIT;
    }
    inline void addNum(int d) {
        num_ += d;
    }
    inline int  getNum() {
        return num_;
    }
    inline void setTrieData(TrieData v){
        if (td_ == TRIE_DATA_INIT)
            td_ = v;
    }
    inline TrieData  getTrieData() {
        return td_;
    }
    inline void setWord(bool isw) {
        isword_ = isw;
    }
    inline bool isWord(){
        return isword_;
    }
};


// 字典树类
class TrieTree {
public:
    TrieTree(int nodeCacheCount = TRIE_NODE_CACHES);
    virtual ~TrieTree();
    void initialize() {
        nodeId_ = 0;
        root_ = genNode();
    }

public:
    TrieNode *root() const { return node(root_); }
    TrieNode *node(int idx) const { return &(nodes_[idx]); }

    // 插入 1 个值为 v 的数
    virtual void insert_value(ValueType v);
    // 删除 1 个值为 v 的数
    virtual void delete_value(ValueType v);
    // 查询值为 v 的数的个数
    virtual TrieData query_value(ValueType v);
    // 查询字典树中和给定数值 XOR 后最大的那个数
    virtual void query_xor_max(ValueType v, AnsType &ans);

    AnsType ijk();
    AnsType jik();
private:
    int genNode() {
        TrieNode *pkNode = &(nodes_[nodeId_]);
        pkNode->reset();
        return nodeId_++;
    }

    bool hasNode(TrieNode *pkNow, int nodeIdx) {
        if (pkNow->hasNode(nodeIdx)) {
            TrieNode *pkNode = node(pkNow->getNode(nodeIdx));
            if (pkNode->getNum() > 0) {
                return true;
            }
        }
        return false;
    }

    void checkNode(TrieNode *pkNow, int nodeIdx) {
        if (!pkNow->hasNode(nodeIdx)) {
            pkNow->setNode(nodeIdx, genNode());
        }
    }

    int nodeCount(TrieNode *pkNow, int sonIdx) {
        if (!hasNode(pkNow, sonIdx)) {
            return 0;
        }
        TrieNode *pkSon = node(pkNow->getNode(sonIdx));
        return pkSon->getNum();
    }
private:
    int nodeId_;
    int root_;
    TrieNode *nodes_;
};

TrieTree::TrieTree(int nodeCacheCount) : nodes_(NULL), root_(0), nodeId_(0) {
    nodes_ = new TrieNode[nodeCacheCount];
}

TrieTree::~TrieTree() {
    if (nodes_) {
        delete[] nodes_;
    }
}

// 从最高位开始插入 01字典树
void TrieTree::insert_value(ValueType v) {
    TrieNode *pkNow = root();
    for (int i = MAXBIT - 1; i >= 0; --i) {
        int nodeIdx = samebit(i);
        checkNode(pkNow, nodeIdx);
        pkNow = node(pkNow->getNode(nodeIdx));
        pkNow->addNum(1);
    }
}

// 查询 01字典树 中 v 数字出现的个数
TrieData TrieTree::query_value(ValueType v) {
    TrieNode *pkNow = root();
    for (int i = MAXBIT - 1; i >= 0; --i) {
        int sonIdx = samebit(i);
        if (!hasNode(pkNow, sonIdx)) {
            return 0;
        }
        pkNow = node(pkNow->getNode(sonIdx));
    }
    return pkNow->getNum();
}

// 从最高位开始插入 删除 01字典树 中 v 数字一次 
void TrieTree::delete_value(ValueType v) {
    TrieData cnt = query_value(v);
    if (cnt == 0) {
        return;
    }
    TrieNode *pkNow = root();
    for (int i = MAXBIT - 1; i >= 0; --i) {
        int sonIdx = samebit(i);
        pkNow = node(pkNow->getNode(sonIdx));
        pkNow->addNum(-1);
    }
}

// 从根结点开始找 32 次
// 根据异或的性质，尽量找和当前数的第i位相反的数，如果找不到才找相同的；
void TrieTree::query_xor_max(ValueType v, AnsType &ans) {
    TrieNode *pkNow = root();
    ans = 0;
    for (int i = MAXBIT - 1; i >= 0; --i) {
        int sonIdx = diffbit(i);
        if (hasNode(pkNow, sonIdx)) {
            ans |= ((ValueType)1 << i);
        }
        else {
            sonIdx = 1 - sonIdx;
        }
        pkNow = node(pkNow->getNode(sonIdx));
    }
}



int n, A[500010];

int sum[32][2];

AnsType TrieTree::jik() {
    int i, t, k;
    AnsType ans = 0;
    initialize();

    // 预处理 前i个数中，第t位为[0,1]的数的个数总和
    memset(sum, 0, sizeof(sum));

    for (int i = 1; i <= n; ++i) {
        for (t = 0; t < MAXBIT; ++t) {
            int v = A[i];
            int x = samebit(t);
            sum[t][x] = sum[t][x] + 1;
            sum[t][(1 - x)] = sum[t][(1 - x)];
        }
    }

    for (i = n; i >= 1; i--) {
        int v = A[i];

        TrieNode *pkNow = root();
        for (t = MAXBIT - 1; t >= 0; --t) {

            int sonIdx = samebit(t);
            int ksbit = (sonIdx ^ 1);   // k's  t bit

            int sumtmp = sum[t][sonIdx];
            ValueType tmp = nodeCount(pkNow, ksbit);
            if (tmp && sumtmp)
                ans += tmp * sumtmp;

            if (hasNode(pkNow, sonIdx)) {
                pkNow = node(pkNow->getNode(sonIdx));
            }
            else {
                break;
            }
        }

        for (t = 0; t < MAXBIT; ++t) {
            int x = samebit(t);
            sum[t][x] = sum[t][x] - 1;
            sum[t][(1 - x)] = sum[t][(1 - x)];
        }

        insert_value(v);
    }

    return ans;

}

AnsType TrieTree::ijk() {
    AnsType ans = 0;

    initialize();
    memset(sum, 0, sizeof(sum));

    for (int k = 1; k <= n; ++k) {
        int v = A[k];

        TrieNode *pkNow = root();
        for (int t = MAXBIT - 1; t >= 0; --t) {

            int sonIdx = samebit(t);
            int iBit = 1 - sonIdx;

            int sumtmp = sum[t][iBit];
            ValueType tmp = nodeCount(pkNow, iBit);
            if (tmp && sumtmp)
                ans += tmp * sumtmp;

            if (hasNode(pkNow, sonIdx)) {
                pkNow = node(pkNow->getNode(sonIdx));
            }
            else {
                break;
            }

        }

        for (int t = 0; t < MAXBIT; ++t) {
            int x = samebit(t);
            sum[t][x] = sum[t][x] + 1;
            sum[t][(1 - x)] = sum[t][(1 - x)];
        }


        insert_value(v);
    }


    int fg;
    fg = 1;
    return ans - jik();
}


int main() {
    int t;
    TrieTree tt;

    scanf("%d", &t);

    while (t--) {

        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &A[i]);
            //A[i] = rand() * rand();
        }

        /*int c = 0;
        for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
        for (int k = j + 1; k <= n; ++k) {
        if ((A[i]^A[j]) < (A[j] ^ A[k])) ++c;

        }
        }
        }*/


        long long ans = tt.ijk();
        printf("%lld\n", ans);
    }
    return 0;
}

/*

10
13
9 8 7 11 2 3 4 5 6 7 8 9 10

10
9 18 7 11 211 3 1411 8 1119 11110

5
8 7 5 1 6
*/