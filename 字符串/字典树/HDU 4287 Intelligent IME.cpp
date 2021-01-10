/*
*/

#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;


char mobiles[][6] = {
    "",
    "",
    "abc", // 2
    "def", // 3
    "ghi", // 4
    "jkl", // 5
    "mno", // 6
    "pqrs",// 7
    "tuv", // 8
    "wxyz" // 9
};

typedef int TrieData;                        // 修改点 1
typedef const char ValueType;                // 修改点 2

const int NODECACHES = 60020;                // 修改点 3
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
    void updateData(TrieData& d);
    TrieData getData();
};

void TrieNode::resetData() {
    data_ = TRIEDATA_INIT;
}


void TrieNode::updateData(TrieData& d) {
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


public:
    virtual void insert(int vSize, ValueType v[], TrieData data, TrieNodeInsertType tntt);
    virtual TrieData query(int vSize, ValueType v[]);                     // 修改点 8
    virtual TrieData query_dfs(TrieNode* pkNode, int vSize, ValueType v[], int vDepth);
    virtual void delete_prefex(int vSize, ValueType v[]);

private:
    int genNode() {
        TrieNode *pkNode = &(nodes_[nodeId_]);
        pkNode->reset();
        return nodeId_++;
    }
    TrieNode *Node(int idx) {
        return &(nodes_[idx]);
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
    TrieNode *pkNow = Node(root_);
    for (int i = 0; i < vSize; ++i) {
        // 1. 查找对应字母所在的子结点是否存在，没有则创建
        int sonIdx = getSonIndex(v[i]);
        if (!pkNow->hasSon(sonIdx)) {
            pkNow->setSon(sonIdx, genNode());
        }
        // 2. 进入子结点
        pkNow = Node(pkNow->getSon(sonIdx));

        // 3. 如果是内部插入类型，则更新标记
        if (tntt == TrieNodeInsertType::TNTT_INSIDE) {
            pkNow->updateData(data);
        }
    }
    // 4. 如果是叶子插入类型，则更新标记
    if (tntt == TrieNodeInsertType::TNTT_LEAF) {
        pkNow->updateData(data);
    }

}

TrieData TrieTree::query(int vSize, ValueType v[]) {
    // 查找对应字典中，是否有字符串的前缀等于 v[]
    TrieNode *pkNow = Node(root_);
    for (int i = 0; i < vSize; ++i) {
        int sonIdx = getSonIndex(v[i]);
        if (!pkNow->hasSon(sonIdx)) {
            return TRIEDATA_INIT;
        }
        pkNow = Node(pkNow->getSon(sonIdx));
    }
    return pkNow->getData();
}

TrieData TrieTree::query_dfs(TrieNode* pkNow, int vSize, ValueType v[], int vDepth) {
    if (vDepth == 0) {
        pkNow = Node(root_);
    }
    if (vSize == vDepth) {
        return pkNow->getData();
    }

    int clen = strlen(mobiles[v[vDepth] - '0']);
    TrieData s = 0;
    for (int i = 0; i < clen; ++i) {
        char c = mobiles[v[vDepth] - '0'][i];
        int sonIdx = getSonIndex(c);
        if (!pkNow->hasSon(sonIdx)) {
            continue;
        }
        s += query_dfs(Node(pkNow->getSon(sonIdx)), vSize, v, vDepth + 1);
    }
    return s;
}

void TrieTree::delete_prefex(int vSize, ValueType v[]) {
    // 删除对应前缀的所有字符串
    TrieNode *pkNow = Node(root_);
    TrieNode *pkPre = NULL;
    for (int i = 0; i < vSize; ++i) {

        int sonIdx = getSonIndex(v[i]);
        if (!pkNow->hasSon(sonIdx)) {
            return;
        }
        pkPre = pkNow;
        pkNow = Node(pkNow->getSon(sonIdx));
    }
    if (pkPre) {
        int sonIdx = getSonIndex(v[vSize - 1]);
        pkPre->setSon(sonIdx, TRIENODE_NULL);
    }
}

char cmd[2][55];
int n, m;

char digits[5010][10];
char words[5010][10];

int main() {
    TrieTree tt(NODECACHES);

    int t;
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; ++i) {
            scanf("%s", digits[i]);
        }

        for (int i = 0; i < m; ++i) {
            scanf("%s", words[i]);
        }

        tt.initialize();

        for (int i = 0; i < m; ++i) {
            tt.insert(strlen(words[i]), words[i], 1, TrieNodeInsertType::TNTT_INSIDE);
        }

        for (int i = 0; i < n; ++i) {
            int len = strlen(digits[i]);


            printf("%d\n", tt.query_dfs(NULL, len, digits[i], 0));
        }
    }
    return 0;
}