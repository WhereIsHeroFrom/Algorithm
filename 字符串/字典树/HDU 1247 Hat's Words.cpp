/*
    字典树 - 叶子结点打标记

           - 查询的时候：
                    搜索整棵树，一旦遇到有个结点被打标记，则进行 子树 和 根树 同步遍历，遇到就标记的就是满足条件的1个解

    字典树 - 


*/

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

 using namespace std;

const int NODECACHES = 700100;         // 修改点 1
const int TREENODE = 26;               // 修改点 2
const int TREEHASH_BASE = 'a';         // 修改点 3
const int TRIEDATA_INIT = 0;           // 修改点 4

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
        td_ += add;                   // 修改点 5
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
    virtual void insert(int vSize, ValueType v[], int w);  // 修改点 6
    virtual void query_dfs(int depth, TrieNode *pkNow);               // 修改点 7
    virtual void query_dfs(int depth, TrieNode *pkNow, TrieNode *pkRoot);
    void search();

private:
    TrieNode *genNode();
    int getSonIndex(ValueType v);

private:
    int nodeId_;
    TrieNode *nodes_;
    TrieNode *root_;
    char stk[1000];
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

void TrieTree::query_dfs(int depth, TrieNode *pkNow) {
    if (!pkNow) {
        return;
    }

    if (pkNow->getValue() != TRIEDATA_INIT) {
        query_dfs(depth, pkNow, root_);
    }

    for (int i = 0; i < TREENODE; ++i) {
        TrieNode *pkSon = pkNow->getSon(i);
        if (pkSon) {
            stk[depth] = i + 'a';
            query_dfs(depth + 1, pkSon);
        }
    }
}

vector<string> ans;

void TrieTree::query_dfs(int depth, TrieNode *pkNow, TrieNode *pkRoot) {
    if (!pkNow || !pkRoot) {
        return;
    }
    if (pkNow->getValue() != TRIEDATA_INIT && pkRoot->getValue() != TRIEDATA_INIT) {
        stk[depth] = '\0';
        ans.push_back(stk);
    }

    for (int i = 0; i < TREENODE; ++i) {
        TrieNode *pkSon = pkNow->getSon(i);
        if (pkSon) {
            stk[depth] = i + 'a';
            query_dfs(depth + 1, pkSon, pkRoot->getSon(i));
        }
    }
}

void TrieTree::search() {
    query_dfs(0, root_);
}

TrieNode *TrieTree::genNode() {
    TrieNode *pkNode = &(nodes_[nodeId_++]);
    pkNode->reset();
    return pkNode;
}

int TrieTree::getSonIndex(ValueType v) {
    return v - TREEHASH_BASE;
}

char codes[1001020];

int main() {
    TrieTree tt(NODECACHES);
    tt.initialize();

    int i, t;
    int n;
    int c = 60000000;

    while (scanf("%s", codes) != EOF && c --) {
        tt.insert(strlen(codes), codes, 1);
    }
    tt.search();
    sort(ans.begin(), ans.end());

    for (i = 0; i < ans.size(); ++i) {
        if (i == 0 || ans[i] != ans[i-1])
            printf("%s\n", ans[i].c_str());
    }

    return 0;
}
