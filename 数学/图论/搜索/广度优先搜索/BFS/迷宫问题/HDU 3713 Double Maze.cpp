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
    virtual void bfs_outputpath(IBFSState* pkState) = 0;

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
//************ 广度优先搜索模板 ************





//************ 需要实现的接口 ************
const int MAPN = 6;
int W, H;
int NOW;
int Map[100][10][10];

const int DIR_COUNT = 4;
const int dir[DIR_COUNT][2] = {
    // D, L, R, U
    // 下， 左， 右，上
    { 1, 0 }, { 0, -1 }, { 0, 1 }, { -1, 0 }
};
char CRT[DIR_COUNT + 1] = "DLRU";

int hasBarrior(int state, int diridx) {
    int dirto[] = { 1, 0, 2, 3 };
    return state & (1 << dirto[diridx]);
}

bool isSquare(int state) {
    return state & (1 << 4);
}

bool isHole(int state) {
    return !isSquare(state);
}

bool isStart(int state) {
    return state & (1 << 5);
}

bool isEnd(int state) {
    return state & (1 << 6);
}

class BFSState : public IBFSState {
public:
    int x1_, y1_, x2_, y2_;

    void print() {
        printf("(%d,%d),(%d,%d)\n", x1_, y1_, x2_, y2_);
    }
    virtual StateType Serialize(int x1, int y1, int x2, int y2) {
        x1_ = x1;
        y1_ = y1;
        x2_ = x2;
        y2_ = y2;
        nowstate_ = (x1_ << 9 | y1_ << 6 | x2_ << 3 | y2_);
        return nowstate_;
    }
    virtual void DeSerialize(StateType state) {
        nowstate_ = state;
        x1_ = (state >> 9) & 0x7;
        y1_ = (state >> 6) & 0x7;
        x2_ = (state >> 3) & 0x7;
        y2_ = (state >> 0) & 0x7;
    }

    virtual bool isFinalState() {
        return isEnd(Map[NOW][x1_][y1_]) && isEnd(Map[NOW - 1][x2_][y2_]);
    }

    virtual bool canMove(int d) {
        return !hasBarrior(Map[NOW][x1_][y1_], d) || !hasBarrior(Map[NOW - 1][x2_][y2_], d);
    }

    virtual StateType moveDir(BFSState *pre, int d) {
        *this = *pre;

        if (!hasBarrior(Map[NOW][x1_][y1_], d)) {
            x1_ += dir[d][0];
            y1_ += dir[d][1];
        }
        if (!hasBarrior(Map[NOW - 1][x2_][y2_], d)) {
            x2_ += dir[d][0];
            y2_ += dir[d][1];
        }
        return Serialize(x1_, y1_, x2_, y2_);
    }

    virtual bool isValidState() {
        if (x1_ < 0 || y1_ < 0 || x1_ >= MAPN || y1_ >= MAPN) {
            return false;
        }
        if (x2_ < 0 || y2_ < 0 || x2_ >= MAPN || y2_ >= MAPN) {
            return false;
        }
        int state1 = Map[NOW][x1_][y1_];
        int state2 = Map[NOW - 1][x2_][y2_];

        return (isSquare(state1) && isSquare(state2));
    }

    void operator=(const BFSState& bs) {
        x1_ = bs.x1_;
        y1_ = bs.y1_;

        x2_ = bs.x2_;
        y2_ = bs.y2_;
    }

    BFSState operator - (const BFSState& other) {
        BFSState tmp = *this;
        tmp.x1_ -= other.x1_;
        tmp.y1_ -= other.y1_;

        tmp.x2_ -= other.x2_;
        tmp.y2_ -= other.y2_;

        return tmp;
    }
};

class BFSGraph : public BFSGraphBase {
public:
    virtual void bfs_extendstate(int bfsHashState, IBFSState* bfsState);
    virtual void bfs_outputpath(IBFSState* pkState);
};

void BFSGraph::bfs_extendstate(int bfsHashState, IBFSState* bfsState) {
    BFSState to;
    for (int i = 0; i < DIR_COUNT; ++i) {
        BFSState *bs = (BFSState *)bfsState;

        if (!bs->canMove(i)) {
            continue;
        }

        StateType toStateValue = to.moveDir(bs, i);

        if (!to.isValidState()) {
            continue;
        }
        if (hash_.hasKey(toStateValue)) {
            continue;
        }
        int toStateKey = hash_.setKey(toStateValue);
        pre_[toStateKey] = bfsHashState;
        step_[toStateKey] = step_[bfsHashState] + 1;
        queue_.push(toStateKey);
    }
}

int getDir(BFSState *pkStart, BFSState *pkEnd) {
    BFSState now = *pkStart - *pkEnd;

    for (int i = 0; i < DIR_COUNT; ++i) {
        if (now.x1_ == dir[i][0] && now.y1_ == dir[i][1] || now.x2_ == dir[i][0] && now.y2_ == dir[i][1]) {
            return i;
        }
    }
}

void BFSGraph::bfs_outputpath(IBFSState* pkState) {
    int now = hash_.getKey(pkState->Serialize());
    BFSState nowstate, prestate;
    BFSState* pkPreState = NULL;
    BFSState* pkNowState = &nowstate;
    vector <int> ans;

    while (now != -1) {
        if (!hash_.hasKey(now)) while (1)
        {

        }
        StateType st = hash_.getValue(now);
        pkNowState->DeSerialize(st);
        if (pkPreState) {
            ans.push_back(getDir(pkPreState, pkNowState));
        }
        pkPreState = &prestate;
        *pkPreState = *pkNowState;

        now = pre_[now];
    }
    for (int i = ans.size() - 1; i >= 0; --i) {
        printf("%c", CRT[ans[i]]);
    }
    puts("");
}

//************ 需要实现的接口 ************


char str[100];
BFSGraph bfs;

int main() {
    int t;
    int i, j;
    scanf("%d", &t);
    int x2, y2, x1, y1;
    for (NOW = 0; NOW < t; ++NOW) {
        for (i = 0; i < MAPN; ++i) {
            for (j = 0; j < MAPN; ++j) {
                scanf("%d", &Map[NOW][i][j]);
                if (isStart(Map[NOW][i][j])) {
                    x1 = i;
                    y1 = j;
                }
            }
        }

        if (NOW) {
            BFSState bfsstate;
            bfsstate.Serialize(x1, y1, x2, y2);

            int step = bfs.bfs(&bfsstate, NULL);
            if (step == inf) printf("-1\n");
        }
        x2 = x1;
        y2 = y1;
    }



    return 0;
}
