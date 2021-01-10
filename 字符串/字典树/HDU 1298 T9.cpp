/*
    字典树 - 内部结点累加标记
           - 增加每个结点标记的初始化值 TRIEDATA_INIT

    字典树 + 深搜枚举答案

    1WA   -  权值应该累加，写成了更新
*/

#include <iostream>
#include <cstring>

using namespace std;

char alpHash[10][10] = {
    "",
    "",
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno",
    "pqrs",
    "tuv",
    "wxyz"
};


const int NODECACHES = 200100;
const int TREENODE = 26;
const int TRIEDATA_INIT = -1;

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
    TrieData query(int vSize, ValueType v[]);
    void query_dfs(TrieNode *now, int vSize, ValueType v[], int depth, int& answ, char *stk, char *ans);
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
        pkNow->addValue(w);
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

void TrieTree::query_dfs(TrieNode *now, int vSize, ValueType v[], int depth, int& answ, char *stk, char *ans) {
    if (depth == 0) {
        now = root_;
    }
    if (depth == vSize) {
        if (now->getValue() > answ) {
            answ = now->getValue();
            stk[depth] = 0;
            strcpy(ans, stk);
        }
        return;
    }
    int number = (v[depth] - '0');
    int cnt = strlen(alpHash[number]);

    for (int i = 0; i < cnt; ++i) {
        int sonIdx = getSonIndex(alpHash[number][i]);
        TrieNode *son = now->getSon(sonIdx);
        if (son) {
            stk[depth] = alpHash[number][i];
            query_dfs(son, vSize, v, depth + 1, answ, stk, ans);
        }
    }
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
    int t, cas = 0;
    scanf("%d", &t);

    while (t--) {
        tt.initialize();
        int n, w;
        char ch[120];
        scanf("%d", &n);
        while (n--) {
            scanf("%s %d", ch, &w);
            tt.insert(strlen(ch), ch, w);
        }
        printf("Scenario #%d:\n", ++cas);
        scanf("%d", &n);
        while (n--) {
            scanf("%s", ch);

            for (int i = 0; ch[i] != '1'; ++i) {
                int answ = TRIEDATA_INIT;
                char ans[120], stk[120];
                tt.query_dfs(NULL, i + 1, ch, 0, answ, stk, ans);
                if (answ == TRIEDATA_INIT) {
                    printf("MANUALLY\n");
                }
                else {
                    printf("%s\n", ans);
                }
            }
            puts("");
        }
        puts("");
    }
    


    

    return 0;
}
