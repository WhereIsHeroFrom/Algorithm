/*
    2 MLE 结点数开小，这题是预处理，所以一开始开出了多少个结点是已知的， 模板里把 TrieNode* 替换成 int
*/

#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;


const int NODECACHES = 3600000;              // 修改点 1
const int TREENODE = 10;                     // 修改点 2
const int TRIEHASH_BASE = '0';               // 修改点 3
const int TRIEDATA_INIT = -1;                // 修改点 4
const int TRIENODE_NULL = -1;
typedef int TrieData;                        // 修改点 5
typedef const char ValueType;                // 修改点 6

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
    if (data_ == TRIEDATA_INIT) {
        data_ = d;
    }
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
    virtual void insert(int vSize, ValueType v[], int data, TrieNodeInsertType tntt);
    virtual TrieData query(int vSize, ValueType v[]);                     // 修改点 8

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

void TrieTree::insert(int vSize, ValueType v[], int data, TrieNodeInsertType tntt) {
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
    TrieNode *pkNow = Node(root_);
    for (int i = 0; i < vSize; ++i) {
        int sonIdx = getSonIndex(v[i]);
        if (!pkNow->hasSon(sonIdx)) {
            return -1;
        }
        pkNow = Node(pkNow->getSon(sonIdx));
    }
    return pkNow->getData();
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
    TrieTree tt(NODECACHES);
    tt.initialize();

    tt.insert(1, "1", 0, TrieNodeInsertType::TNTT_INSIDE);

    // 字典树 1 的位置插入 0
    Pre = 1;
    PrePre = 1;
    for (int i = 2; i < 100000; ++i) {
        Now = Pre + PrePre;
        // 字典树 处理 Now
        PrePre = Pre;
        Pre = Now;

        string s = Now.ToString();
        
        tt.insert(Min(40, s.length()), s.c_str(), i, TrieNodeInsertType::TNTT_INSIDE);
    }
    int t, cas = 0;
    char ans[100];
    scanf("%d", &t);
    while (t--) {
        scanf("%s", ans);
        printf("Case #%d: %d\n", ++cas, tt.query(strlen(ans), ans));
    }
    return 0;
}