/*
    字典树 - 叶子结点 打标记，标记为 下标ID

    字典树 - 对后面输入的字建立字典，然后去前面的矩阵里面查找；

    2 MLE 正向插入单次太多

*/

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

 using namespace std;

const int NODECACHES = 200100;         // 修改点 1
const int TREENODE = 26;               // 修改点 2
const int TREEHASH_BASE = 'A';         // 修改点 3
const int TRIEDATA_INIT = -1;          // 修改点 4

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
        if (td_ == TRIEDATA_INIT) td_ = add;                // 修改点 5
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
    virtual void insert(int vSize, ValueType v[], int w);   // 修改点 6
    virtual void query(int vSize, ValueType v[], int pos, int *out); // 修改点 7

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



void TrieTree::query(int vSize, ValueType v[], int pos, int *out) {
    TrieNode *pkNow = root_;
    for (int i = 0; i < vSize; ++i) {
        int sonIdx = getSonIndex(v[i]);
        if (!pkNow->hasSon(sonIdx)) {
            return ;
        }
        pkNow = pkNow->getSon(sonIdx);
        if (pkNow->getValue() != TRIEDATA_INIT) {
            if(out[pkNow->getValue()] == TRIEDATA_INIT)
                out[pkNow->getValue()] = pos;
        }
    }
}

TrieNode *TrieTree::genNode() {
    TrieNode *pkNode = &(nodes_[nodeId_++]);
    pkNode->reset();
    return pkNode;
}

int TrieTree::getSonIndex(ValueType v) {
    return v - TREEHASH_BASE;
}

char Map[510][510];
int R, C;

int dir[3][2] = {
    {1, 0},
    {0, 1},
    {1, 1}
};

bool isOutBound(int r, int c) {
    return r >= R || c >= C;
}

char ans[10010][25];
int out[10010];

int main() {
    TrieTree tt(NODECACHES);
    tt.initialize();
    
    scanf("%d %d", &R, &C);
    for (int i = 0; i < R; ++i) {
        scanf("%s", Map[i]);
    }

    int total = 0;

    while (scanf("%s", ans[total]) != EOF)
    {
        if (strcmp(ans[total], "-1") == 0) break;
        
        tt.insert(strlen(ans[total]), ans[total], total);

        ++total;
    }
    memset(out, TRIEDATA_INIT, sizeof(out));

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            for (int k = 0; k < 3; ++k) {
                int s = 0;
                char str[25];
                for (int l = 0; l < 20; ++l) {
                    int toi = i + dir[k][0] * l;
                    int toj = j + dir[k][1] * l;
                    if (isOutBound(toi, toj)) break;
                    str[s++] = Map[toi][toj];
                }
                str[s] = '\0';
                tt.query(s, str, 512*i+j, out);
            }
        }
    }

    for (int i = 0; i < total; ++i) {
        if (out[i] == TRIEDATA_INIT) printf("-1 -1\n");
        else {
            printf("%d %d\n", out[i]/512, out[i]%512);
        }
    }

    return 0;
}
