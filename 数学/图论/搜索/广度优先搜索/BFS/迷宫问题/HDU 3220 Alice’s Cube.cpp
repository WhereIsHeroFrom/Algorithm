#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

//************ 整数散列哈希模板 ************
// 静态哈希数组大小
const int MAXH = ((1 << 20) - 1);
#define StateType long long 

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
    // 设置获取给定值的哈希值
    int setKey(StateType val);
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

int Hash::setKey(StateType val) {
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

int Hash::getKey(StateType val) {
    return setKey(val);
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


//************ 广度优先搜索模板 ************

const int inf = -1;

class IBFSState {
protected:
    StateType nowstate_;
    static StateType finalstate_;
public:
    IBFSState() {}
    virtual bool isValidState() = 0;                // 1. 判断这个状态 [位置] 是否合法，是否越界或者不可达之类的
    virtual void DeSerialize(StateType state) = 0;  // 2. 必须子类继承，因为实际反序列化成什么数据，只有子类知道

    virtual StateType Serialize() {                 // 3. 序列化的数据只有一个，就是长整型 StateType
        return nowstate_;
    }
    virtual bool isFinalState() {                   // 4. 终止态可能有多个，所以不确定的，要用 virtual
        return nowstate_ == finalstate_;
    }
    static void setFinalState(StateType s_) {
        finalstate_ = s_;
    }
};

StateType IBFSState::finalstate_ = 0;

class BFSGraphBase {
public:
    BFSGraphBase();
    virtual ~BFSGraphBase();
private:
    virtual void bfs_initialize(IBFSState* pkInitState);
public:
    virtual int bfs(IBFSState* pkInitState, IBFSState* pkFinalState);
    virtual void bfs_state_initialize();
    virtual int bfs_get_step(IBFSState* pkState);

public:
    virtual void bfs_extendstate(int bfsHashState, IBFSState* bfsState) = 0;
    virtual void bfs_outputpath(IBFSState* pkState);

protected:
    queue <int> queue_;               // 用于广搜的队列
    Hash hash_;                       // 标记状态的hash表
    int* step_;                       // 标记初始状态到某个状态的步数
    int* pre_;                        // 记录每个状态的前驱状态 
};


BFSGraphBase::BFSGraphBase() : step_(NULL) {
    step_ = new int[MAXH + 1];
    pre_ = new int[MAXH + 1];
}

BFSGraphBase::~BFSGraphBase() {
    if (step_) {
        delete[] step_;
        step_ = NULL;
    }
    if (pre_) {
        delete[] pre_;
        pre_ = NULL;
    }
}

void BFSGraphBase::bfs_state_initialize() {
    memset(step_, inf, (MAXH + 1) * sizeof(int));           // 1. 步数初始化
    memset(pre_, inf, (MAXH + 1) * sizeof(int));            // 2. 状态前驱初始化
    hash_.initialize();                                     // 3. 哈希表初始化
}

int BFSGraphBase::bfs_get_step(IBFSState* pkState) {
    int initState = hash_.getKey(pkState->Serialize());
    return step_[initState];
}

void BFSGraphBase::bfs_outputpath(IBFSState* pkState) {

}

void BFSGraphBase::bfs_initialize(IBFSState* pkInitState) {
    bfs_state_initialize();
    while (!queue_.empty()) {                              // 1. 队列清空
        queue_.pop();
    }
    int initState = hash_.getKey(pkInitState->Serialize()); // 2. 获取初始状态哈希key
    queue_.push(initState);                                 // 3. 塞入队列
    step_[initState] = 0;                                   // 4. 标记初始步数为 0
}

int BFSGraphBase::bfs(IBFSState* pkState, IBFSState* pkFinalState) {
    bfs_initialize(pkState);                    // 1. 初始状态压入队列
    if (pkFinalState) {                         // 2. 设置终止状态
        IBFSState::setFinalState(pkFinalState->Serialize());
    }
    else {
        IBFSState::setFinalState(inf);
    }

    while (!queue_.empty()) {
        int bfsState = queue_.front();          // 3. 从队列弹出一个状态
        StateType s = hash_.getValue(bfsState); // 4. 通过下标反算状态（通过哈希的 值value 获取 哈希值）
        pkState->DeSerialize(s);                // 5. 通过哈希值得到关键字key，关键字是一个 BFSState 类
        queue_.pop();
        if (pkState->isFinalState()) {          // 6. 判断是否终止状态
            bfs_outputpath(pkState);
            return step_[bfsState];             //    是则返回走过的步数
        }
        bfs_extendstate(bfsState, pkState);     // 7. 对状态进行扩展，压入队列
    }
    return inf;
}


// 继承类实现特殊功能
class BFSState : public IBFSState {
public:
    virtual bool isValidState() {
        return true;
    }
    virtual void DeSerialize(StateType state);

    virtual bool isFinalState() {
        return false;
    }
};

class BFSGraph : public BFSGraphBase {
public:
    BFSGraph() {}
    virtual ~BFSGraph() {}
    virtual void bfs_extendstate(int bfsHashState, IBFSState* bfsState);
};

//************ 广度优先搜索模板 ************


//************ 需要实现的接口 ************

const int MAXV = 16;
const int MAXD = 4;

// 注意减1  ！！！！！
int adj[MAXV][MAXD] = {
    { 2, 3, 5, 9 },//1
    { 1, 4, 6, 10 },//2
    { 1, 4, 7, 11 },//3
    { 2, 3, 8, 12 },//4
    { 1, 6, 7, 13 },//5
    { 2, 5, 8, 14 },//6
    { 3, 5, 8, 15 },//7
    { 4, 6, 7, 16 },//8
    { 1, 10, 11, 13 },//9
    { 2, 9, 12, 14 },//10
    { 3, 9, 12, 15 },//11
    { 4, 10, 11, 16 },//12
    { 5, 9, 14, 15 },//13
    { 6, 10, 13, 16 },//14
    { 7, 11, 13, 16 },//15
    { 8, 12, 14, 15 }//16
};

void BFSState::DeSerialize(StateType state) {
    nowstate_ = state;
}

bool has(int state, int bit) {
    return state & (1 << bit);
}

void BFSGraph::bfs_extendstate(int bfsHashState, IBFSState* bfsState) {
    BFSState bs;
    for (int i = 0; i < MAXV; ++i) {
        for (int j = 0; j < MAXD; ++j) {
            int toState = bfsState->Serialize();
            if (has(toState, i) != has(toState, adj[i][j])) {
                toState ^= (1 << i);
                toState ^= (1 << adj[i][j]);

                bs.DeSerialize(toState);

                int sState = hash_.getKey(toState);
                if (step_[sState] == inf) {
                    queue_.push(sState);
                    step_[sState] = step_[bfsHashState] + 1;
                }
            }
        }
    }
}


//************ 需要实现的接口 ************

BFSGraph bfs;

int main() {

    for (int i = 0; i < MAXV; ++i) {
        for (int j = 0; j < MAXD; ++j) {
            adj[i][j] -= 1;
        }
    }
    BFSState S;
    S.DeSerialize(65280);
    bfs.bfs(&S, NULL);

    int t, cas = 0;
    scanf("%d", &t);

    while (t--) {
        int ans = 0;
        for (int i = 0; i < MAXV; ++i) {
            int v;
            scanf("%d", &v);
            if (v) {
                ans |= (1 << i);
            }
        }
        BFSState bs;
        bs.DeSerialize(ans);
        int ss = bfs.bfs_get_step(&bs);
        if (ss > 3) {
            printf("Case #%d: more\n", ++cas);
        }
        else
            printf("Case #%d: %d\n", ++cas, ss);

    }
    return 0;
}