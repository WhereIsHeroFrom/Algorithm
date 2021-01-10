/*
    两个字典树贪心匹配：

    1. 0 - 0
    2. 1 - 1
    3. 0 - 1
    4. 1 - 0

    3 TLE
    1 WA
*/

#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

typedef int TrieData;
typedef int AnsType;                         // 修改点 1
typedef int ValueType;                       // 修改点 2
const int MAXBIT = 30;                       // 修改点 3
const int NODECACHES = MAXBIT * 100010;      // 修改点 4
const int TREENODE = 2;                      // 修改点 5
const int TRIEHASH_BASE = 0;                 // 修改点 6
const int TRIEDATA_INIT = 0;                 // 修改点 7
const int TRIENODE_NULL = -1;

#define samebit(i) ((v & ((ValueType)1 << i)) ? 1 : 0)
#define diffbit(i) ((v & ((ValueType)1 << i)) ? 0 : 1)


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
        /*if (sonIdx < 0 || sonIdx >= TREENODE) {
        return false;
        }*/
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

// 字典树类
class TrieTree {
public:
    TrieTree(int nodeCacheCount);
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

    AnsType jik();
    AnsType ijk();

    bool hasSon(TrieNode *pkNow, int sonIdx) {
        if (pkNow->hasSon(sonIdx)) {
            TrieNode *pkSon = node(pkNow->getSon(sonIdx));
            if (pkSon->getData() != TRIEDATA_INIT) {
                return true;
            }
        }
        return false;
    }
private:
    int genNode() {
        TrieNode *pkNode = &(nodes_[nodeId_]);
        pkNode->reset();
        return nodeId_++;
    }



    void addSon(TrieNode *pkNow, int sonIdx) {
        if (!pkNow->hasSon(sonIdx)) {
            pkNow->setSon(sonIdx, genNode());
        }
    }

    int sonCount(TrieNode *pkNow, int sonIdx) {
        if (!hasSon(pkNow, sonIdx)) {
            return 0;
        }
        TrieNode *pkSon = node(pkNow->getSon(sonIdx));
        return pkSon->getData();
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
        int sonIdx = samebit(i);
        addSon(pkNow, sonIdx);
        pkNow = node(pkNow->getSon(sonIdx));
        pkNow->updateData(1);
    }
}

// 查询 01字典树 中 v 数字出现的个数
TrieData TrieTree::query_value(ValueType v) {
    TrieNode *pkNow = root();
    for (int i = MAXBIT - 1; i >= 0; --i) {
        int sonIdx = samebit(i);
        if (!hasSon(pkNow, sonIdx)) {
            return TRIEDATA_INIT;
        }
        pkNow = node(pkNow->getSon(sonIdx));
    }
    return pkNow->getData();
}

// 从最高位开始插入 删除 01字典树 中 v 数字一次 
void TrieTree::delete_value(ValueType v) {
    TrieData nCnt = query_value(v);
    if (nCnt == TRIEDATA_INIT) {
        return;
    }
    TrieNode *pkNow = root();
    for (int i = MAXBIT - 1; i >= 0; --i) {
        int sonIdx = samebit(i);
        pkNow = node(pkNow->getSon(sonIdx));
        pkNow->updateData(-1);
    }
}

// 从根结点开始找 32 次
// 根据异或的性质，尽量找和当前数的第i位相反的数，如果找不到才找相同的；
void TrieTree::query_xor_max(ValueType v, AnsType &ans) {
    TrieNode *pkNow = root();
    ans = 0;
    for (int i = MAXBIT - 1; i >= 0; --i) {
        int sonIdx = diffbit(i);
        if (hasSon(pkNow, sonIdx)) {
            ans |= ((ValueType)1 << i);
        }
        else {
            sonIdx = 1 - sonIdx;
        }
        pkNow = node(pkNow->getSon(sonIdx));
    }
}

int n, a[100010], b[100010];
TrieTree L(NODECACHES), R(NODECACHES);

void get_value(TrieNode *pkLeftNode, TrieNode *pkRightNode, AnsType& LValue, AnsType& minValue, AnsType LAns, AnsType ans, int depth) {
    if (ans >= minValue) {
        return;
    }
    if (depth == -1) {
        if (ans < minValue) {
            minValue = ans;
            LValue = LAns;
        }
        return;
    }
    bool bLHas[2] = { L.hasSon(pkLeftNode, 0), L.hasSon(pkLeftNode, 1) };
    bool bRHas[2] = { R.hasSon(pkRightNode, 0), R.hasSon(pkRightNode, 1) };

    bool bFind = false;
    for (int i = 0; i < 2; ++i) {
        if (bLHas[i] && bRHas[i]) {
            bFind = true;
            get_value(L.node(pkLeftNode->getSon(i)), R.node(pkRightNode->getSon(i)), LValue, minValue, (LAns | (1 << depth)*i), ans, depth - 1);
            return;
        }
    }

    if (!bFind) {
        for (int i = 0; i < 2; ++i) {
            if (bLHas[i] && bRHas[1 - i]) {
                get_value(L.node(pkLeftNode->getSon(i)), R.node(pkRightNode->getSon(1 - i)), LValue, minValue, (LAns | (1 << depth)*i), (ans | (1 << depth)), depth - 1);
                return;
            }
        }
    }
}

int c[100010], csize;

int main() {
    int t;
    int i;
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);
        L.initialize();
        R.initialize();
        for (i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            //a[i] = rand() * rand();
            L.insert_value(a[i]);
        }
        for (i = 0; i < n; ++i) {
            scanf("%d", &b[i]);
            //b[i] = rand() * rand();
            R.insert_value(b[i]);
        }

        int cnt = n;
        csize = 0;

        while (cnt--) {
            AnsType ans = INT_MAX;
            AnsType lans;
            get_value(L.root(), R.root(), lans, ans, 0, 0, MAXBIT - 1);
            c[csize++] = ans;

            L.delete_value(lans);
            R.delete_value(ans ^ lans);

        }
        sort(c, c + csize);
        for (i = 0; i < csize; ++i) {
            if (i) printf(" ");
            printf("%d", c[i]);
        }
        puts("");
    }
    return 0;
}