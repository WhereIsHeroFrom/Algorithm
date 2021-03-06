#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

//************ 整数散列哈希模板 ************
// 静态哈希数组大小
const int MAXH = ((1 << 22) - 1);
#define StateType unsigned long long 

class Hash {

public:
    Hash();
    virtual ~Hash();

private:
    bool *hashkey_;                   // 状态hash的key
    StateType *hashval_;              // 状态hash的val

public:
    // 销毁调用
    void finalize();
    // 初始化调用
    void initialize();
    // 获取给定值的哈希值
    int getKey(StateType val);
    // 查询是否有这个值在哈希表中
    bool hasKey(StateType val);
    // 获取给定哈希值的原值
    StateType getValue(int key);
};

Hash::Hash() : hashkey_(NULL), hashval_(NULL) {
    initialize();
}

Hash::~Hash() {
    finalize();
}

void Hash::finalize() {
    if (hashkey_) {
        delete[] hashkey_;
        hashkey_ = NULL;
    }
    if (hashval_) {
        delete[] hashval_;
        hashval_ = NULL;
    }
}
void Hash::initialize() {
    // 1. 释放空间避免内存泄漏
    // 2. 初始化哈希的key和val
    if (!hashkey_) {
        hashkey_ = new bool[MAXH + 1];
    }
    if (!hashval_) {
        hashval_ = new StateType[MAXH + 1];
    }
    memset(hashkey_, false, (MAXH + 1) * sizeof(bool));
}

int Hash::getKey(StateType val) {
    // 1. 采用 位与 代替 取模，位运算加速
    int key = (val & MAXH);
    while (1) {
        if (!hashkey_[key]) {
            // 2. 如果对应的key没有出现过，则代表没有冲突过；则key的槽位留给val；
            hashkey_[key] = true;
            hashval_[key] = val;
            return key;
        }
        else {
            if (hashval_[key] == val) {
                // 3. 如果key 的槽位正好和val匹配，则说明找到了，返回 key；
                return key;
            }
            // 4. 没有找到合适的 key， 进行二次寻址
            key = (key + 1) & MAXH;
        }
    }
}

bool Hash::hasKey(StateType val) {
    int key = (val & MAXH);
    while (1) {
        if (!hashkey_[key]) {
            return false;
        }
        else {
            if (hashval_[key] == val) {
                return true;
            }
            key = (key + 1) & MAXH;
        }
    }
}

StateType Hash::getValue(int key) {
    if (key < MAXH && hashkey_[key]) {
        return hashval_[key];
    }
    return -1;
}
//************ 整数散列哈希模板 ************



//************ 字符串哈希模板 ************
// 字符串最大长度
const int MAXS = 200010;
const int BASE[] = { 12289, 24593, 98317, 393241 };
const int MOD[] = { 25165843, 50331653, 100663319, 201326611 };

#define ValueType char
#define HashType unsigned long long

int valueTypeIndex(ValueType v) {
    return v - 'a' + 1;
}

class StringifyHash {
public:
    StringifyHash();
    virtual ~StringifyHash();

private:
    int mod_;
    HashType *hash_;
    HashType *power_;

public:
    void initialize(int size, ValueType v[], int b = BASE[2], int p = MOD[2]);
    HashType get(int l, int r);
};

StringifyHash::StringifyHash() : hash_(NULL), power_(NULL) {
    hash_ = new HashType[MAXS];
    power_ = new HashType[MAXS];

}

StringifyHash::~StringifyHash() {
    if (hash_) {
        delete[] hash_;
        hash_ = NULL;
    }
    if (power_) {
        delete[] power_;
        power_ = NULL;
    }
}

void StringifyHash::initialize(int size, ValueType v[], int b, int p) {
    mod_ = p;
    power_[0] = 1;
    hash_[0] = 0;
    for (int i = 1; i <= size; ++i) {
        power_[i] = power_[i - 1] * b;
        hash_[i] = (hash_[i - 1] * b + valueTypeIndex(v[i]));
    }
}

HashType StringifyHash::get(int l, int r) {
    HashType hst = (hash_[r] - hash_[l - 1] * power_[r - l + 1]);
    return hst;
}
//************ 字符串哈希模板 ************



//************ 双哈希模板 ************
class DoubleStringifyHash {
private:
    StringifyHash shash_[2];

public:
    void initialize(int size, ValueType v[], int b1 = BASE[2], int p1 = MOD[2], int b2 = BASE[3], int p2 = MOD[3]);
    HashType get(int l, int r);
};

void DoubleStringifyHash::initialize(int size, ValueType v[], int b1, int p1, int b2, int p2) {
    shash_[0].initialize(size, v, b1, p1);
    shash_[1].initialize(size, v, b2, p2);
}

HashType DoubleStringifyHash::get(int l, int r) {
    HashType high = shash_[0].get(l, r);
    HashType low = shash_[1].get(l, r);
    return  high << 32 | low;
}
//************ 双哈希模板 ************

#define  ull unsigned long long
#define MAXN 2000100

ull f[MAXN];

Hash h;
int a[MAXN];
char line[12000010];

void get() {
    int idx = 0, t = 0, s = 0;
    getchar();
    gets(line);
    int flag = 0, startinput = false;
    while (line[idx]) {

        if (line[idx] >= '0' && line[idx] <= '9') {
            startinput = true;
            s = s * 10 + line[idx] - '0';
        }
        else if (line[idx] == '-'){
            flag = 1;
        }
        else {
            if (startinput) {
                a[++t] = flag ? -s : s;
                startinput = false;
                s = 0;
                flag = 0;
            }
        }
        ++idx;
    }
    if (startinput) {
        a[++t] = flag ? -s : s;
    }
}

int main() {

    f[1] = 1;
    f[2] = 2;
    for (int i = 3; i < MAXN; ++i) {
        f[i] = f[i - 1] + f[i - 2];
    }

    int t;
    scanf("%d", &t);
    while (t--) {
        ull A = 0, B = 0, C = 0;
        scanf("%d", &a[0]);
        get();
        for (int i = 1; i <= a[0]; ++i) {
            if (a[i]) {
                A += f[i];
            }
        }
        scanf("%d", &a[0]);
        get();
        for (int i = 1; i <= a[0]; ++i) {
            if (a[i]) {
                B += f[i];
            }
        }
        scanf("%d", &a[0]);
        get();
        for (int i = 1; i <= a[0]; ++i) {
            if (a[i]) {
                C += f[i];
            }
        }
        A *= B;
        int k = 1;
        for (int i = 1; i <= a[0]; ++i) {
            if (!a[i]) {
                if (A == C + f[i]) {
                    k = i;
                    break;
                }
            }
        }
        printf("%d\n", k);

    }
    return 0;
}