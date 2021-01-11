/*
    字典树 - 内部结点累加标记
    - 增加每个结点标记的初始化值 TRIEDATA_INIT
    
    字典树 + 深搜枚举答案

    1WA   -  权值应该累加，写成了更新
*/

/*
    模板需要修改的地方：
        1、TrieData 作为字典树的权值，是有特殊用途的，比如作为下标，索引到某个其他数据，或者直接是一个权值用于计算；
        2、ValueType 用作标识字符串类型，可能是 字符类型char， 也可能是整型 int，或者 long long 等等；
        3、TRIE_WORD_COUNT 代表字符串集合数量；
        4、TRIE_WORD_LENGTH 代表单个字符串最大长度；
        5、TRIE_DATA_INIT 用于对 TrieData 赋初始值；
        6、trieNodeValueHash 通过这个哈希函数实现 字符 到 下标 的映射；
*/


#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
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

typedef int TrieData;                        // 修改点 1
typedef const char ValueType;                // 修改点 2
const int TRIE_WORD_COUNT = 1000;            // 修改点 3
const int TRIE_WORD_LENGTH = 100;            // 修改点 4
const int TRIE_NODE_COUNT = 26;              // 修改点 5

const TrieData TRIE_DATA_INIT = -1;
const int TRIE_NODE_NULL = -1;
const int TRIE_NODE_CACHES = TRIE_WORD_COUNT * TRIE_WORD_LENGTH;


int trieNodeValueHash(ValueType v) {         // 修改点 6
    return v - 'a';
}

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
        td_ += v;
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

    TrieNode *root() const { return node(root_); }
    TrieNode *node(int idx) const { return &(nodes_[idx]); }

public:
    void insert_word(int vSize, ValueType v[], TrieData data);
    bool query_word(int vSize, ValueType v[]);                // 询问是否存在单词 v
    int query_prefix_num(int vSize, ValueType v[]);           // 询问以 v 为首的前缀数量
    TrieData query_triedata(int vSize, ValueType v[]);        // 询问单词 v 的权值
    void delete_prefex(int vSize, ValueType v[]);
    void query_prefix(int vSize, ValueType v[], char *ans);

    void query_dfs(TrieNode *now, int vSize, ValueType v[], int depth, int& answ, char *stk, char *ans);
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

TrieTree::TrieTree(int nodeCacheCount) : nodes_(NULL), root_(NULL), nodeId_(0) {
    nodes_ = new TrieNode[nodeCacheCount];
}

TrieTree::~TrieTree() {
    if (nodes_) {
        delete[] nodes_;
    }
}

void TrieTree::insert_word(int vSize, ValueType v[], TrieData data) {
    // 插入字符串到字典树
    TrieNode *pkNow = root();
    for (int i = 0; i < vSize; ++i) {
        int nodeIdx = trieNodeValueHash(v[i]);
        checkNode(pkNow, nodeIdx);
        pkNow = node(pkNow->getNode(nodeIdx));
        pkNow->addNum(1);
        pkNow->setTrieData(data);
    }
    pkNow->setWord(true);
}

bool TrieTree::query_word(int vSize, ValueType v[]) {
    // 查找对应字典中，是否有字符串等于 v[]
    TrieNode *pkNow = root();
    for (int i = 0; i < vSize; ++i) {
        int nodeIdx = trieNodeValueHash(v[i]);
        if (!hasNode(pkNow, nodeIdx)) {
            return false;
        }
        pkNow = node(pkNow->getNode(nodeIdx));
    }
    return pkNow->isWord();
}

int TrieTree::query_prefix_num(int vSize, ValueType v[]) {
    // 查找对应字典中，是否有字符串等于 v[]
    TrieNode *pkNow = root();
    for (int i = 0; i < vSize; ++i) {
        int nodeIdx = trieNodeValueHash(v[i]);
        if (!hasNode(pkNow, nodeIdx)) {
            return 0;
        }
        pkNow = node(pkNow->getNode(nodeIdx));
    }
    return pkNow->getNum();
}

TrieData TrieTree::query_triedata(int vSize, ValueType v[]) {
    TrieNode *pkNow = root();
    for (int i = 0; i < vSize; ++i) {
        int nodeIdx = trieNodeValueHash(v[i]);
        if (!hasNode(pkNow, nodeIdx)) {
            return TRIE_DATA_INIT;
        }
        pkNow = node(pkNow->getNode(nodeIdx));
    }
    return pkNow->getTrieData();
}

void TrieTree::delete_prefex(int vSize, ValueType v[]) {
    int cnt = query_prefix_num(vSize, v);
    if (cnt == 0) {
        // 先询问一次，有没有这个前缀，没有就不用删除
        return;
    }
    // 删除对应前缀的所有字符串
    TrieNode *pkNow = root();
    for (int i = 0; i < vSize; ++i) {
        int nodeIdx = trieNodeValueHash(v[i]);
        // 引用计数机制来进行结点删除
        TrieNode *pkSon = node(pkNow->getNode(nodeIdx));
        pkSon->addNum(-cnt);
        pkNow = pkSon;
    }
}

void TrieTree::query_prefix(int vSize, ValueType v[], char *ans) {
    // 查找对应字典中，最短能够表示 v[] 的字符串存储在 ans 中
    TrieNode *pkNow = root();
    for (int i = 0; i < vSize; ++i) {
        int nodeIdx = trieNodeValueHash(v[i]);
        if (!hasNode(pkNow, nodeIdx)) {
            return;
        }
        pkNow = node(pkNow->getNode(nodeIdx));
        ans[i] = v[i];
        if (pkNow->getNum() == 1) {
            ans[i + 1] = '\0';
            return;
        }
    }
    ans[vSize] = '\0';
}


void TrieTree::query_dfs(TrieNode *now, int vSize, ValueType v[], int depth, int& answ, char *stk, char *ans) {
    if (now == NULL) {
        now = root();
    }
    if (depth == vSize) {
        if (now->getTrieData() > answ) {
            answ = now->getTrieData();
            stk[depth] = 0;
            strcpy(ans, stk);
        }
        return;
    }
    int number = (v[depth] - '0');
    int cnt = strlen(alpHash[number]);

    for (int i = 0; i < cnt; ++i) {
        int sonIdx = trieNodeValueHash(alpHash[number][i]);
        if (hasNode(now, sonIdx)) {
            TrieNode *son = node(now->getNode(sonIdx));
            if (son) {
                stk[depth] = alpHash[number][i];
                query_dfs(son, vSize, v, depth + 1, answ, stk, ans);
            }
        }
    }
}


int main() {
    TrieTree tt;
    int t, cas = 0;
    scanf("%d", &t);

    while (t--) {
        tt.initialize();
        int n, w;
        char ch[120];
        scanf("%d", &n);
        while (n--) {
            scanf("%s %d", ch, &w);
            tt.insert_word(strlen(ch), ch, w);
        }
        printf("Scenario #%d:\n", ++cas);
        scanf("%d", &n);
        while (n--) {
            scanf("%s", ch);

            for (int i = 0; ch[i] != '1'; ++i) {
                int answ = TRIE_DATA_INIT;
                char ans[120], stk[120];
                tt.query_dfs(NULL, i + 1, ch, 0, answ, stk, ans);
                if (answ == TRIE_DATA_INIT) {
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
