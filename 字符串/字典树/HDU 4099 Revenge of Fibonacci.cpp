/*
    2 MLE 结点数开小，这题是预处理，所以一开始开出了多少个结点是已知的， 模板里把 TrieNode* 替换成 int
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

typedef int TrieData;                        // 修改点 1
typedef const char ValueType;                // 修改点 2
const int TRIE_WORD_COUNT = 100000;          // 修改点 3
const int TRIE_WORD_LENGTH = 36;             // 修改点 4
const int TRIE_NODE_COUNT = 10;              // 修改点 5

const TrieData TRIE_DATA_INIT = -1;
const int TRIE_NODE_NULL = -1;
const int TRIE_NODE_CACHES = TRIE_WORD_COUNT * TRIE_WORD_LENGTH;


int trieNodeValueHash(ValueType v) {         // 修改点 6
    return v - '0';
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

    TrieNode *root() const { return node(root_); }
    TrieNode *node(int idx) const { return &(nodes_[idx]); }

public:
    void insert_word(int vSize, ValueType v[], TrieData data);
    bool query_word(int vSize, ValueType v[]);                // 询问是否存在单词 v
    int query_prefix_num(int vSize, ValueType v[]);           // 询问以 v 为首的前缀数量
    TrieData query_triedata(int vSize, ValueType v[]);        // 询问单词 v 的权值
    void delete_prefex(int vSize, ValueType v[]);
    void query_prefix(int vSize, ValueType v[], char *ans);


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







const unsigned int MAXDIGITS = 22002;        // 大数的位数，即 10^MAXDIGITS
const unsigned int MAXN = 9999;             // 每个a[i]表示的最大数字  
const unsigned int DLEN = 4;                // MAXN的最大位数 


class BigNum {
public:
    int a[(MAXDIGITS + DLEN - 1) / DLEN + 1];
    int len;
    BigNum(){ len = 1; memset(a, 0, sizeof(a)); }
    BigNum(const int b);
    BigNum(const char * buffer);
    BigNum(const BigNum & T);
    void Attach(const char * buffer);
    bool Bigger(const BigNum &) const;
    BigNum & operator=(const BigNum &);
    BigNum & Add(const BigNum &);
    BigNum & Sub(const BigNum &);
    BigNum operator+(const BigNum &) const;
    BigNum operator-(const BigNum &) const;
    BigNum operator*(const BigNum &) const;
    BigNum operator/(const int &) const;
    void Print();
    string ToString();
};

BigNum::BigNum(const int b) {
    int c, d = b;
    len = 0;
    memset(a, 0, sizeof(a));
    while (d > MAXN) {
        c = d % (MAXN + 1);
        d = d / (MAXN + 1);
        a[len++] = c;
    }
    a[len++] = d;
}

BigNum::BigNum(const char * buffer) {
    Attach(buffer);
}

void BigNum::Attach(const char * buffer) {
    int i, j;
    int lst[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000 };
    j = len = 0;
    memset(a, 0, sizeof(a));
    for (i = strlen(buffer) - 1; i >= 0; --i, ++j) {
        if (j >= DLEN) {
            j = 0;
            len++;
        }
        a[len] += lst[j] * (buffer[i] - '0');
    }
    len++;
    // 处理前导零 
    while (len > 1 && a[len - 1] == 0) len--;
}

BigNum::BigNum(const BigNum & T) : len(T.len)
{
    memcpy(a, T.a, sizeof(a));
}

bool  BigNum::Bigger(const BigNum & T) const {
    int ln;
    if (len > T.len) return true;
    else if (len == T.len){
        ln = len - 1;
        while (ln >= 0 && a[ln] == T.a[ln]) ln--;
        if (ln >= 0 && a[ln] > T.a[ln]) return true;
        else return false;
    }
    else return false;
}

BigNum & BigNum::operator=(const BigNum & n){
    len = n.len;
    memcpy(a, n.a, sizeof(a));
    return *this;
}
BigNum & BigNum::Add(const BigNum & T){
    int i, big;
    big = T.len > len ? T.len : len;
    for (i = 0; i < big; i++)
    {
        a[i] = a[i] + T.a[i];
        if (a[i] > MAXN)
        {
            a[i + 1]++;
            a[i] = a[i] - MAXN - 1;
        }
    }
    if (a[big] != 0) len = big + 1;
    else len = big;
    return *this;
}
BigNum & BigNum::Sub(const BigNum & T){
    int i, j, big;
    big = T.len > len ? T.len : len;
    for (i = 0; i < big; i++)
    {
        if (a[i] < T.a[i])
        {
            j = i + 1;
            while (a[j] == 0) j++;
            a[j--]--;
            while (j > i) a[j--] += MAXN;
            a[i] = a[i] + MAXN + 1 - T.a[i];
        }
        else a[i] -= T.a[i];
    }
    len = big;
    while (len > 1 && a[len - 1] == 0) len--;
    return *this;
}
BigNum BigNum::operator+(const BigNum & n) const{
    BigNum a = *this;
    a.Add(n);
    return a;
}
BigNum BigNum::operator-(const BigNum & T) const{
    BigNum b = *this;
    b.Sub(T);
    return b;
}

BigNum BigNum::operator*(const BigNum & T) const{
    BigNum ret;
    int i, j, up, temp1, temp;
    for (i = 0; i < len; i++)
    {
        up = 0;
        for (j = 0; j < T.len; j++)
        {
            temp = a[i] * T.a[j] + ret.a[i + j] + up;
            if (temp > MAXN)
            {
                temp1 = temp % (MAXN + 1);
                up = temp / (MAXN + 1);
                ret.a[i + j] = temp1;
            }
            else
            {
                up = 0;
                ret.a[i + j] = temp;
            }
        }
        if (up != 0) ret.a[i + j] = up;
    }
    ret.len = i + j;
    while (ret.len > 1 && ret.a[ret.len - 1] == 0) ret.len--;
    return ret;
}
BigNum BigNum::operator/(const int & b) const{
    BigNum ret;
    int i, down = 0;
    for (i = len - 1; i >= 0; i--)
    {
        ret.a[i] = (a[i] + down * (MAXN + 1)) / b;
        down = a[i] + down * (MAXN + 1) - ret.a[i] * b;
    }
    ret.len = len;
    while (ret.a[ret.len - 1] == 0) ret.len--;
    return ret;
}
void BigNum::Print() {
    int i;
    char format[10];
    sprintf(format, "%%0%dd", DLEN);
    printf("%d", a[len - 1]);
    for (i = len - 2; i >= 0; i--)
    {
        printf(format, a[i]);
    }
    putchar('\n');
}

string BigNum::ToString() {
    char c[MAXDIGITS + DLEN + 1], tmp[DLEN + 1];
    char format[10];
    
    sprintf(c, "%d", a[len - 1]);
    sprintf(format, "%%0%dd", DLEN);
    
    for (int i = len - 2; i >= 0; --i) {
        sprintf(tmp, format, a[i]);
        strcat(c, tmp);
        if (len - i > 50) break;
    }

    return string(c);
}

int Min(int a, int b) {
    return a < b ? a : b;
}

BigNum Pre, PrePre, Now;

int main() {
    TrieTree tt;
    tt.initialize();

    tt.insert_word(1, "1", 0);

    // 字典树 1 的位置插入 0
    Pre = 1;
    PrePre = 1;
    for (int i = 2; i < 100000; ++i) {
        Now = Pre + PrePre;
        // 字典树 处理 Now
        PrePre = Pre;
        Pre = Now;

        string s = Now.ToString();
        
        tt.insert_word(Min(40, s.length()), s.c_str(), i);
    }
    int t, cas = 0;
    char ans[100];
    scanf("%d", &t);
    while (t--) {
        scanf("%s", ans);
        printf("Case #%d: %d\n", ++cas, tt.query_triedata(strlen(ans), ans));
    }
    return 0;
}