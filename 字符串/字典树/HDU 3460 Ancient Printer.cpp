/*
字典树 + 树形DP

2 WA   对叶子结点判断出了问题，当某个字符串是另一个前缀时，出现误判叶子结点；
是否是叶子结点应该从是否拥有子结点来判断

2 WA   单次会重复，有几个重复单次就要 print 几次

*/

#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

typedef int TrieData;                        // 修改点 1
typedef const char ValueType;                // 修改点 2

const int NODECACHES = 500020;               // 修改点 3
const int TREENODE = 26;                     // 修改点 4
const int TRIEHASH_BASE = 'a';               // 修改点 5
const TrieData TRIEDATA_INIT = 0;            // 修改点 6
const int TRIENODE_NULL = -1;

// 字典树结点类
class TrieNode {
private:
    TrieData data_;
    // 注意这里存的是结点内存池的下标，相比存指针的好处是：字节数少一半
    int nodes_[TREENODE];

public:
    // 模板中不变的接口
    inline void setSon(int sonIdx, int son) {
        nodes_[sonIdx] = son;
    }
    inline int getSon(int sonIdx) {
        return nodes_[sonIdx];
    }
    inline bool hasSon(int sonIdx) {
        // 结点范围判断
        if (sonIdx < 0 || sonIdx >= TREENODE) {
            return false;
        }
        return nodes_[sonIdx] != TRIENODE_NULL;
    }
    inline void reset() {
        resetData();
        memset(nodes_, TRIENODE_NULL, sizeof(nodes_));
    }

public:
    // 模板中根据不同的题型进行稍适修改        // 修改点 7
    void resetData();
    void updateData(TrieData d);
    TrieData getData();
};

void TrieNode::resetData() {
    data_ = TRIEDATA_INIT;
}


void TrieNode::updateData(TrieData d) {
    data_ += d;
}

TrieData TrieNode::getData() {
    return data_;
}

enum TrieNodeInsertType {
    TNTT_INSIDE = 0,
    TNTT_LEAF = 1,
};

// 字典树类
class TrieTree {
public:
    TrieTree(int nodeCacheCount);
    virtual ~TrieTree();
    void initialize() {
        nodeId_ = 0;
        root_ = genNode();
    }

    TrieNode *root() const { return node(root_); }
    TrieNode *node(int idx) const { return &(nodes_[idx]); }

public:
    virtual void insert(int vSize, ValueType v[], TrieData data, TrieNodeInsertType tntt);
    virtual TrieData query(int vSize, ValueType v[]);                     // 修改点 8
    virtual void delete_prefex(int vSize, ValueType v[]);


    virtual void query_prefix(int vSize, ValueType v[], char *ans);

    void gen_graph(int u, TrieNode *pkNow);
private:
    int genNode() {
        TrieNode *pkNode = &(nodes_[nodeId_]);
        pkNode->reset();
        return nodeId_++;
    }

    int getSonIndex(ValueType v) {
        return v - TRIEHASH_BASE;
    }
private:
    int nodeId_;
    int root_;
    TrieNode *nodes_;
};

TrieTree::TrieTree(int nodeCacheCount) : nodes_(NULL), root_(NULL), nodeId_(0) {
    nodes_ = new TrieNode[nodeCacheCount];
}

TrieTree::~TrieTree() {
    if (nodes_) {
        delete[] nodes_;
    }
}

void TrieTree::insert(int vSize, ValueType v[], TrieData data, TrieNodeInsertType tntt) {
    TrieNode *pkNow = root();
    for (int i = 0; i < vSize; ++i) {
        // 1. 查找对应字母所在的子结点是否存在，没有则创建
        int sonIdx = getSonIndex(v[i]);
        if (!pkNow->hasSon(sonIdx)) {
            pkNow->setSon(sonIdx, genNode());
        }
        // 2. 进入子结点
        pkNow = node(pkNow->getSon(sonIdx));

        // 3. 如果是内部插入类型，则更新标记
        if (tntt == TNTT_INSIDE) {
            pkNow->updateData(data);
        }
    }
    // 4. 如果是叶子插入类型，则更新标记
    if (tntt == TNTT_LEAF) {
        pkNow->updateData(data);
    }

}

TrieData TrieTree::query(int vSize, ValueType v[]) {
    // 查找对应字典中，是否有字符串的前缀等于 v[]
    TrieNode *pkNow = root();
    for (int i = 0; i < vSize; ++i) {
        int sonIdx = getSonIndex(v[i]);
        if (!pkNow->hasSon(sonIdx)) {
            return TRIEDATA_INIT;
        }
        pkNow = node(pkNow->getSon(sonIdx));
    }
    return pkNow->getData();
}

void TrieTree::delete_prefex(int vSize, ValueType v[]) {
    TrieData nCnt = query(vSize, v);
    if (nCnt == TRIEDATA_INIT) {
        // 先询问一次，有没有这个前缀，没有就不用删除
        return;
    }
    // 删除对应前缀的所有字符串
    TrieNode *pkNow = root();
    for (int i = 0; i < vSize; ++i) {
        int sonIdx = getSonIndex(v[i]);
        // 引用计数机制来进行结点删除
        TrieNode *pkSon = node(pkNow->getSon(sonIdx));
        pkSon->updateData(-nCnt);
        if (pkSon->getData() == TRIEDATA_INIT) {
            pkNow->setSon(sonIdx, TRIENODE_NULL);
            return;
        }
        pkNow = pkSon;
    }
}

void TrieTree::query_prefix(int vSize, ValueType v[], char *ans) {
    // 查找对应字典中，最短能够表示 v[] 的字符串存储在 ans 中
    TrieNode *pkNow = root();
    for (int i = 0; i < vSize; ++i) {
        int sonIdx = getSonIndex(v[i]);
        if (!pkNow->hasSon(sonIdx)) {
            return;
        }
        pkNow = node(pkNow->getSon(sonIdx));
        ans[i] = v[i];
        if (pkNow->getData() == 1) {
            ans[i + 1] = 0;
            return;
        }
    }
    ans[vSize] = 0;
}

// 树形DP - 
// 0 dp[i][0] 表示从结点i遍历完所有子结点回到i的最小值
// 1 dp[i][1] 表示从结点i遍历完所有子结点，并且留在叶子结点的最小值 
long long dp[NODECACHES][2];


void TrieTree::gen_graph(int u, TrieNode *pkNow) {
    // 是叶子结点

    dp[u][0] = 0;
    dp[u][1] = -1;

    for (int i = 0; i < TREENODE; ++i) {
        if (pkNow->hasSon(i)) {
            int v = pkNow->getSon(i);
            //printf("(%d -> %d)\n", u, v);
            gen_graph(v, node(v));
            dp[u][0] += (dp[v][0] + 2); // +2 是因为下去回来
        }
    }

    for (int i = 0; i < TREENODE; ++i) {
        if (pkNow->hasSon(i)) {
            int v = pkNow->getSon(i);
            long long s = (dp[u][0] - dp[v][0] - 2 + dp[v][1] + 1);  // 选择其中一个结点，去了不回来
            if (dp[u][1] == -1 || s < dp[u][1]) {
                dp[u][1] = s;
            }
        }
    }

    if (dp[u][0] == 0 && dp[u][1] == -1) {
        dp[u][0] = 0;
        dp[u][1] = 0;
    }

    if (pkNow->getData()) {
        dp[u][0] += pkNow->getData();
        dp[u][1] += pkNow->getData();
    }


    //printf("%d %d %d\n", u, dp[u][0], dp[u][1]);

}

char str[100];

int main() {
    int t;
    int N;
    TrieTree tt(NODECACHES);

    while (scanf("%d", &N) != EOF) {
        tt.initialize();
        while (N--) {
            scanf("%s", str);
            tt.insert(strlen(str), str, 1, TrieNodeInsertType::TNTT_LEAF);
        }
        tt.gen_graph(0, tt.root());
        printf("%lld\n", dp[0][1]);
    }

    return 0;
}


/*
6
ade
adfg
bac
bad
baf
c
*/