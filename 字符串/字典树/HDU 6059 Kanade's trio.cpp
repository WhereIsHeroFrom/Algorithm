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
const int MAXBIT = 30;                       // 修改点 3
const int NODECACHES = MAXBIT * 500010;      // 修改点 4
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
private:
    int genNode() {
        TrieNode *pkNode = &(nodes_[nodeId_]);
        pkNode->reset();
        return nodeId_++;
    }

    bool hasSon(TrieNode *pkNow, int sonIdx) {
        if (pkNow->hasSon(sonIdx)) {
            // 没有删除的情况，直接 return 就行
            return true;

            TrieNode *pkSon = node(pkNow->getSon(sonIdx));
            if (pkSon->getData() != TRIEDATA_INIT) {
                return true;
            }
        }
        return false;
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
            ValueType tmp = sonCount(pkNow, ksbit);
            if (tmp && sumtmp)
                ans += tmp * sumtmp;

            if (hasSon(pkNow, sonIdx)) {
                pkNow = node(pkNow->getSon(sonIdx));
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
            ValueType tmp = sonCount(pkNow, iBit);
            if (tmp && sumtmp)
                ans += tmp * sumtmp;

            if (hasSon(pkNow, sonIdx)) {
                pkNow = node(pkNow->getSon(sonIdx));
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
    TrieTree tt(NODECACHES);

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