/*
    字典树 - 内部结点打标记

    1WA - 结点数开小导致 RE
*/

#include <iostream>
#include <cstring>

using namespace std;

const int NODECACHES = 500100;
const int TREENODE = 26;
typedef char ValueType;
typedef int TrieData;

class TrieNode {
private:
    TrieData td_;
    TrieNode *nodes_[TREENODE];

public:
    inline bool hasSon(int sonIdx) {
        return nodes_[sonIdx] != NULL;
    }

    inline void setSon(int sonIdx, TrieNode *pkSon) {
        nodes_[sonIdx] = pkSon;
    }

    inline TrieNode *getSon(int sonIdx) {
        return nodes_[sonIdx];
    }

    inline void addValue(int add) {
        td_ += add;
    }

    inline TrieData getValue() {
        return td_;
    }

    inline void reset() {
        td_ = 0;
        memset(nodes_, NULL, sizeof(nodes_));
    }
};

class TrieTree {
public:
    TrieTree(int nodeCacheCount);
    virtual ~TrieTree();
    
    void initialize();
    void insert(int vSize, ValueType v[]);
    TrieData query(int vSize, ValueType v[]);

private:
    TrieNode *genNode();
    int getSonIndex(ValueType v);

private:
    int nodeId_;
    TrieNode *nodes_;
    TrieNode *root_;
};

TrieTree::TrieTree(int nodeCacheCount) : nodes_(NULL), root_(NULL), nodeId_(0) {
    nodes_ = new TrieNode[nodeCacheCount];
}

TrieTree::~TrieTree() {
    if (nodes_) {
        delete[] nodes_;
    }
}

void TrieTree::initialize()
{
    nodeId_ = 0;
    root_ = genNode();
}

void TrieTree::insert(int vSize, ValueType v[]) {
    TrieNode *pkNow = root_;
    for (int i = 0; i < vSize; ++i) {
        int sonIdx = getSonIndex(v[i]);
        if (!pkNow->hasSon(sonIdx)) {
            pkNow->setSon(sonIdx, genNode());
        }
        pkNow = pkNow->getSon(sonIdx);
        pkNow->addValue(1);
    }
    
}

TrieData TrieTree::query(int vSize, ValueType v[]) {
    TrieNode *pkNow = root_;
    for (int i = 0; i < vSize; ++i) {
        int sonIdx = getSonIndex(v[i]);
        if (!pkNow->hasSon(sonIdx)) {
            return 0;
        }
        pkNow = pkNow->getSon(sonIdx);
    }
    return pkNow->getValue();
}

TrieNode *TrieTree::genNode() {
    TrieNode *pkNode = &(nodes_[nodeId_++]);
    pkNode->reset();
    return pkNode;
}

int TrieTree::getSonIndex(ValueType v) {
    return v - 'a';
}

int main() {
    TrieTree tt(NODECACHES);
    tt.initialize();

    char str[20];
    while (gets(str)) {
        if (strlen(str) == 0) break;

        tt.insert(strlen(str), str);
    }

    while (gets(str)) {
        printf("%d\n", tt.query(strlen(str), str));
    }

    return 0;
}
