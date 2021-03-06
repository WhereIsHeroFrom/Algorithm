/*
    1WA  输出下标需要判重
*/

#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

typedef int TrieData;                        // 修改点 1
typedef const char ValueType;                // 修改点 2

const int NODECACHES = 600100;               // 修改点 3
const int TREENODE = 28;                     // 修改点 4
const int TRIEHASH_BASE = 'a';               // 修改点 5
const TrieData TRIEDATA_INIT = -1;           // 修改点 6
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
    data_ = d;
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

    TrieNode *root() const { return node(root_); }
    TrieNode *node(int idx) const { return &(nodes_[idx]); }

public:
    virtual void insert(int vSize, ValueType v[], TrieData data, TrieNodeInsertType tntt);
    virtual TrieData query(int vSize, ValueType v[]);                     // 修改点 8
    virtual void delete_prefex(int vSize, ValueType v[]);
    virtual void query_prefix(int vSize, ValueType v[], char *ans);


    void query_match(TrieNode *pkNow, int vSize, ValueType v[], int depth, int *ans, int& ansSize);
private:
    int genNode() {
        TrieNode *pkNode = &(nodes_[nodeId_]);
        pkNode->reset();
        return nodeId_++;
    }

    int getSonIndex(ValueType v) {
        if (v == '?') return 26;
        if (v == '*') return 27;
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

int pre[100010];

void TrieTree::insert(int vSize, ValueType v[], TrieData data, TrieNodeInsertType tntt) {
    TrieNode *pkNow = root();
    for (int i = 0; i < vSize; ++i) {
        // 1. 查找对应字母所在的子结点是否存在，没有则创建
        int sonIdx = getSonIndex(v[i]);
        if (!pkNow->hasSon(sonIdx)) {
            pkNow->setSon(sonIdx, genNode());
        }
        // 2. 进入子结点
        pkNow = node(pkNow->getSon(sonIdx));

        // 3. 如果是内部插入类型，则更新标记
        if (tntt == TNTT_INSIDE) {
            pkNow->updateData(data);
        }
    }
    // 4. 如果是叶子插入类型，则更新标记
    if (tntt == TNTT_LEAF) {
        if (pkNow->getData() != TRIEDATA_INIT) {
            pre[data] = pkNow->getData();
        }
        pkNow->updateData(data);
    }

}

TrieData TrieTree::query(int vSize, ValueType v[]) {
    // 查找对应字典中，是否有字符串的前缀等于 v[]
    TrieNode *pkNow = root();
    for (int i = 0; i < vSize; ++i) {
        int sonIdx = getSonIndex(v[i]);
        if (!pkNow->hasSon(sonIdx)) {
            return TRIEDATA_INIT;
        }
        pkNow = node(pkNow->getSon(sonIdx));
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
    TrieNode *pkNow = root();
    for (int i = 0; i < vSize; ++i) {
        int sonIdx = getSonIndex(v[i]);
        // 引用计数机制来进行结点删除
        TrieNode *pkSon = node(pkNow->getSon(sonIdx));
        pkSon->updateData(-nCnt);
        if (pkSon->getData() == TRIEDATA_INIT) {
            pkNow->setSon(sonIdx, TRIENODE_NULL);
            return;
        }
        pkNow = pkSon;
    }
}

void TrieTree::query_prefix(int vSize, ValueType v[], char *ans) {
    // 查找对应字典中，最短能够表示 v[] 的字符串存储在 ans 中
    TrieNode *pkNow = root();
    for (int i = 0; i < vSize; ++i) {
        int sonIdx = getSonIndex(v[i]);
        if (!pkNow->hasSon(sonIdx)) {
            return;
        }
        pkNow = node(pkNow->getSon(sonIdx));
        ans[i] = v[i];
        if (pkNow->getData() == 1) {
            ans[i + 1] = 0;
            return;
        }
    }
    ans[vSize] = 0;
}

void TrieTree::query_match(TrieNode *pkNow, int vSize, ValueType v[], int depth, int *ans, int& ansSize) {
    if (pkNow == NULL) {
        pkNow = root();
    }
    int sonIndex = getSonIndex('*');
    if (pkNow->hasSon(sonIndex)) {
        TrieNode *pkSon = node(pkNow->getSon(sonIndex));
        for (int i = depth; i <= vSize; ++i) {
            query_match(pkSon, vSize, v, i, ans, ansSize);
        }
    }

    if (depth == vSize) {
        if (pkNow->getData() != TRIEDATA_INIT) {
            ans[ansSize++] = pkNow->getData();
        }
        return;
    }
    sonIndex = getSonIndex(v[depth]);

    if (pkNow->hasSon(sonIndex)) {
        query_match(node(pkNow->getSon(sonIndex)), vSize, v, depth + 1, ans, ansSize);
    }

    sonIndex = getSonIndex('?');
    if (pkNow->hasSon(sonIndex)) {
        query_match(node(pkNow->getSon(sonIndex)), vSize, v, depth + 1, ans, ansSize);
    }


}

char patternStr[10];
char matchStr[100];
int ans[100010], ansSize;
int ansHash[100010], ansCase = 0;

int main() {
    int n, m;
    TrieTree tt(NODECACHES);

    while(scanf("%d %d", &n, &m)!=EOF)
    {
        tt.initialize();
        memset(pre, -1, sizeof(pre));
        for (int i = 0; i < n; ++i) {
            scanf("%s", patternStr);
            tt.insert(strlen(patternStr), patternStr, i, TNTT_LEAF);
        }


        while (m--) {
            ++ansCase;
            scanf("%s", matchStr);
            ansSize = 0;
            tt.query_match(NULL, strlen(matchStr), matchStr, 0, ans, ansSize);

            if (ansSize == 0) {
                printf("Not match\n");
            }
            else {
                for (int i = ansSize - 1; i >= 0; --i) {
                    if (ansHash[ans[i]] < ansCase) {
                        int now = ans[i];
                        ansHash[now] = ansCase;
                        while (pre[now] != -1) {
                            now = pre[now];
                            ans[ansSize++] = now;
                            ansHash[now] = ansCase;
                        }
                    }
                }

                sort(ans, ans + ansSize);
                for (int i = 0; i < ansSize; ++i) {
                    if (i) {
                        if (ans[i] == ans[i - 1]) {
                            continue;
                        }
                        printf(" ");
                    }

                    printf("%d", ans[i]);
                }
                puts("");
            }
        }

    }
    return 0;
}

/*
7 5
t*
?h*s
??e*
*s
?*e
*??uk*
*??uk*
this
the
an
is
ggukjdfgfffgfds

11 50
t*
?h*s
??e*
*??uk*
*s
?*e
*s
*s
*s
*??uk*
*??uk*

*/