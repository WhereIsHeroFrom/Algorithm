/*
2 RE
每次删除结点，会导致底下一大颗子树都被删除 （即删除了32个结点）
所以在进行删除的时候，最好只是标记删除，然后判断是否有子结点的时候加上 Data 域

1 WA
hasSon 和 addSon 接口都要让 字典树类 去实现，保证结点删除以后结点本身还在，
保证下次检测计数为 0 的情况不再增加新的 son 结点
*/

#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

typedef int TrieData;
typedef int AnsType;                         // 修改点 1
typedef int ValueType;                       // 修改点 2
const int MAXBIT = 32;                       // 修改点 3

const int TRIE_NODE_CACHES = MAXBIT * 100010;
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
        int nodeIdx = samebit(i);
        if (!hasNode(pkNow, nodeIdx)) {
            return 0;
        }
        pkNow = node(pkNow->getNode(nodeIdx));
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
        int nodeIdx = samebit(i);
        pkNow = node(pkNow->getNode(nodeIdx));
        pkNow->addNum(-1);
    }
}

// 从根结点开始找 32 次
// 根据异或的性质，尽量找和当前数的第i位相反的数，如果找不到才找相同的；
void TrieTree::query_xor_max(ValueType v, AnsType &ans) {
    TrieNode *pkNow = root();
    ans = 0;
    for (int i = MAXBIT - 1; i >= 0; --i) {
        int nodeIdx = diffbit(i);
        if (hasNode(pkNow, nodeIdx)) {
            ans |= ((ValueType)1 << i);
        }
        else {
            nodeIdx = 1 - nodeIdx;
        }
        pkNow = node(pkNow->getNode(nodeIdx));
    }
}



int n, V[1010];

int main() {
    int t;
    TrieTree tt;

    scanf("%d", &t);

    while (t--) {

        tt.initialize();

        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &V[i]);
        }

        for (int i = 0; i < n; ++i) {
            tt.insert_value(V[i]);
        }
        AnsType MaxValue = 0;
        for (int i = 0; i < n; ++i) {
            tt.delete_value(V[i]);

            for (int j = i + 1; j < n; ++j) {
                tt.delete_value(V[j]);

                AnsType ans = 0;
                tt.query_xor_max(V[i] + V[j], ans);

                if (ans > MaxValue) {
                    MaxValue = ans;
                }

                tt.insert_value(V[j]);
            }

            tt.insert_value(V[i]);
        }

        printf("%u\n", MaxValue);
    }

    return 0;
}

/*
10
1 2 3 4 5 6 7 8 9 10

500
546546 45456 456546 45445 5556 24234 4545345 536870911
143534 143534 2435 2 3 3435345 4 4 5 5 435346 6 8 8 7435345 7 1043534 10 9435345 934534
1 1 2 2 3 3 4 4 5 5 6 6 8 8 7 7 10 10 9 9
11 11 12 13 14 15 16 17 18 19
20 21 22 23 24 25 26 27 28 29
1 1 2 2 3 3 4 4 5 5 6 6 8 8 7 7 10 10 9 9
11 11 12 13 14 15 16 17 18 19
20 21 22 23 24 25 26 27 28 29
999 999 998 997 996
5 4 9 5 12 5
787 342543 56 433 23432 5465464 23234234 1000000000 1000000000 657
1000000000 1000000000 1000000000 1000000000 9999999 999999 9999 999 99  9
1 1 2 2 3 3 4 4 5 5 6 6 8 8 7 7 10 10 9 9
11 11 12 13 14 15 16 17 18 19
20 21 22 23 24 25 26 27 28 29
1 1 2 2 3 3 4 4 5 5 6 6 8 8 7 7 10 10 9 9
11 11 12 13 14 15 16 17 18 19
20 21 22 23 24 25 26 27 28 29
999 999 998 997 996
5 4 9 5 12 5
787 342543 56 433 23432 5465464 23234234 1000000000 1000000000 657
1000000000 1000000000 1000000000 1000000000 9999999 999999 9999 999 99  9
546546 45456 456546 45445 5556 24234 4545345 536870911
143534 143534 2435 2 3 3435345 4 4 5 5 435346 6 8 8 7435345 7 1043534 10 9435345 934534
1 1 2 2 3 3 4 4 5 5 6 6 8 8 7 7 10 10 9 9
11 11 12 13 14 15 16 17 18 19
20 21 22 23 24 25 26 27 28 29
1 1 2 2 3 3 4 4 5 5 6 6 8 8 7 7 10 10 9 9
11 11 12 13 14 15 16 17 18 19
20 21 22 23 24 25 26 27 28 29
999 999 998 997 996
5 4 9 5 12 5
787 342543 56 433 23432 5465464 23234234 1000000000 1000000000 657
1000000000 1000000000 1000000000 1000000000 9999999 999999 9999 999 99  9
1 1 2 2 3 3 4 4 5 5 6 6 8 8 7 7 10 10 9 9
11 11 12 13 14 15 16 17 18 19
20 21 22 23 24 25 26 27 28 29
1 1 2 2 3 3 4 4 5 5 6 6 8 8 7 7 10 10 9 9
11 11 12 13 14 15 16 17 18 19
20 21 22 23 24 25 26 27 28 29
999 999 998 997 996
5 4 9 5 12 5
787 342543 56 433 23432 5465464 23234234 1000000000 1000000000 657
1000000000 1000000000 1000000000 1000000000 9999999 999999 9999 999 99  9


3
536870911

10
11 22 33 44 56 65 74 38 99 10

*/