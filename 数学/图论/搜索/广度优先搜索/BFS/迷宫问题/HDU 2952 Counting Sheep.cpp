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
    virtual void bfs_extendstate(int bfsHashState, IBFSState* bfsState) = 0;
    virtual int bfs_get_step(IBFSState* pkState);
protected:
    queue <int> queue_;               // 用于广搜的队列
    Hash hash_;                       // 标记状态的hash表
    int* step_;                       // 标记初始状态到某个状态的步数
};


BFSGraphBase::BFSGraphBase() : step_(NULL) {
    step_ = new int[MAXH + 1];
}

BFSGraphBase::~BFSGraphBase() {
    if (step_) {
        delete[] step_;
        step_ = NULL;
    }
}

void BFSGraphBase::bfs_state_initialize() {
    memset(step_, inf, (MAXH + 1) * sizeof(int));           // 1. 状态初始化
    hash_.initialize();                                     // 2. 哈希表初始化
}

int BFSGraphBase::bfs_get_step(IBFSState* pkState) {
    int initState = hash_.getKey(pkState->Serialize());
    return step_[initState];
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
            return step_[bfsState];             //    是则返回走过的步数
        }
        bfs_extendstate(bfsState, pkState);     // 7. 对状态进行扩展，压入队列
    }
    return -1;
}
//************ 广度优先搜索模板 ************





//************ 需要实现的接口 ************
const int MAPN = 110;
int W, H;
char Map[110][110];

const int DIR_COUNT = 4;
const int dir[DIR_COUNT][2] = {
    { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 }
};

class BFSState : public IBFSState {
public:
    int x_, y_;

    virtual StateType Serialize(int x, int y) {
        x_ = x;
        y_ = y;
        nowstate_ = (x_ << 7 | y_);
        return nowstate_;
    }
    virtual void DeSerialize(StateType state) {
        nowstate_ = state;
        x_ = (state >> 7);
        y_ = state & 0x7f;
    }

    virtual bool isValidState() {
        if (x_ < 0 || y_ < 0 || x_ >= W || y_ >= H) {
            return false;
        }
        if (Map[x_][y_] != '#') {
            return false;
        }
        return true;
    }
};

class BFSGraph : public BFSGraphBase {
public:
    virtual void bfs_initialize(IBFSState* pkInitState);
    virtual void bfs_extendstate(int bfsHashState, IBFSState* bfsState);
};

void BFSGraph::bfs_initialize(IBFSState* pkInitState) {
    while (!queue_.empty()) {                              // 1. 队列清空
        queue_.pop();
    }
    int initState = hash_.getKey(pkInitState->Serialize()); // 2. 获取初始状态哈希key
    queue_.push(initState);                                 // 3. 塞入队列
    step_[initState] = 0;                                   // 4. 标记初始步数为 0
}

void BFSGraph::bfs_extendstate(int bfsHashState, IBFSState* bfsState) {
    BFSState to;
    for (int i = 0; i < DIR_COUNT; ++i) {
        BFSState *bs = (BFSState *)bfsState;
        StateType toStateValue = to.Serialize(bs->x_ + dir[i][0], bs->y_ + dir[i][1]);
        if (!to.isValidState()) {
            continue;
        }
        if (hash_.hasKey(toStateValue)) {
            continue;
        }
        int toStateKey = hash_.setKey(toStateValue);
        step_[toStateKey] = step_[bfsHashState] + 1;
        queue_.push(toStateKey);
    }
}


//************ 需要实现的接口 ************


char str[100];
BFSGraph bfs;

int main() {
    int t;
    int i, j;
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &W, &H);
        for (i = 0; i < W; ++i) {
            scanf("%s", Map[i]);
        }
        int c = 0;
        bfs.bfs_state_initialize();

        for (i = 0; i < W; ++i) {
            for (j = 0; j < H; ++j) {
                BFSState bfsstate;
                bfsstate.Serialize(i, j);
                if (Map[i][j] == '#' && bfs.bfs_get_step(&bfsstate) == inf) {
                    ++c;
                    bfs.bfs(&bfsstate, NULL);
                }
            }
        }
        printf("%d\n", c);
    }

    return 0;
}
