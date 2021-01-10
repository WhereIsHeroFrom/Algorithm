/*
    字典树 - 叶子结点打标记

           - 查询的时候：
                    如果在叶子节点发现，表示是它自己，返回 true；
                    其中一个子结点找到有权值，返回 false；

    字典树性质 - 前缀树


*/

#include <iostream>
#include <cstring>

using namespace std;

const int NODECACHES = 700100;
const int TREENODE = 10;
const int TRIEDATA_INIT = 0;

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
        td_ = TRIEDATA_INIT;
        memset(nodes_, NULL, sizeof(nodes_));
    }
};

class TrieTree {
public:
    TrieTree(int nodeCacheCount);
    virtual ~TrieTree();
    
    void initialize();
    void insert(int vSize, ValueType v[], int w);
    bool query(int vSize, ValueType v[]);

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

void TrieTree::insert(int vSize, ValueType v[], int w) {
    TrieNode *pkNow = root_;
    for (int i = 0; i < vSize; ++i) {
        int sonIdx = getSonIndex(v[i]);
        if (!pkNow->hasSon(sonIdx)) {
            pkNow->setSon(sonIdx, genNode());
        }
        pkNow = pkNow->getSon(sonIdx);
    }
    pkNow->addValue(w);
}

bool TrieTree::query(int vSize, ValueType v[]) {
    TrieNode *pkNow = root_;
    for (int i = 0; i < vSize - 1; ++i) {
        int sonIdx = getSonIndex(v[i]);
        if (!pkNow->hasSon(sonIdx)) {
            return true;
        }
        pkNow = pkNow->getSon(sonIdx);
        if (pkNow->getValue() > TRIEDATA_INIT) {
            return false;
        }
    }
    return true;
}

TrieNode *TrieTree::genNode() {
    TrieNode *pkNode = &(nodes_[nodeId_++]);
    pkNode->reset();
    return pkNode;
}

int TrieTree::getSonIndex(ValueType v) {
    return v - '0';
}

char codes[10010][20];

int main() {
    TrieTree tt(NODECACHES);
    int i, t;
    int n;
    scanf("%d", &t);
    while ( t-- ) {
        tt.initialize();
        scanf("%d", &n);
        for (i = 0; i < n; ++i) {
            scanf("%s", codes[i]);
            tt.insert(strlen(codes[i]), codes[i], 1);
        }
        
        for (i = 0; i < n; ++i) {
            if (!tt.query(strlen(codes[i]), codes[i])) {
                break;
            }
        }

        if (i == n) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }
    }

    return 0;
}
