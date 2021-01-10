/*
2 WA    删除的时候需要考虑子结点回溯
*/

#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

typedef int TrieData;                        // 修改点 1
typedef const char ValueType;                // 修改点 2

const int NODECACHES = 3000020;              // 修改点 3
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


public:
    virtual void insert(int vSize, ValueType v[], TrieData data, TrieNodeInsertType tntt);
    virtual TrieData query(int vSize, ValueType v[]);                     // 修改点 8
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

void TrieTree::delete_prefex(int vSize, ValueType v[]) {
    TrieData nCnt = query(vSize, v);
    if (nCnt == TRIEDATA_INIT) {
        // 先询问一次，有没有这个前缀，没有就不用删除
        return;
    }
    // 删除对应前缀的所有字符串
    TrieNode *pkNow = Node(root_);
    for (int i = 0; i < vSize; ++i) {
        int sonIdx = getSonIndex(v[i]);
        // 引用计数机制来进行结点删除
        TrieNode *pkSon = Node(pkNow->getSon(sonIdx));
        pkSon->updateData(-nCnt);
        if (pkSon->getData() == TRIEDATA_INIT) {
            pkNow->setSon(sonIdx, TRIENODE_NULL);
            return;
        }
        pkNow = pkSon;
    }
}

char cmd[2][55];

int main() {
    TrieTree tt(NODECACHES);


    int t;
    scanf("%d", &t);

    {
        tt.initialize();

        while (t--) {


            scanf("%s %s", cmd[0], cmd[1]);

            if (!strcmp(cmd[0], "insert")) {
                tt.insert(strlen(cmd[1]), cmd[1], 1, TrieNodeInsertType::TNTT_INSIDE);
            }
            else if (!strcmp(cmd[0], "search")) {
                bool is = (tt.query(strlen(cmd[1]), cmd[1]) != TRIEDATA_INIT);
                printf("%s\n", is ? "Yes" : "No");
            }
            else if (!strcmp(cmd[0], "delete")) {
                tt.delete_prefex(strlen(cmd[1]), cmd[1]);
            }

        }
    }
    return 0;
}

/*
40
insert ae
search ae
insert af
search ae
delete af
search ae

*/