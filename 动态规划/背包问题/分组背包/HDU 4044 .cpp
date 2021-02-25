#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ 分组背包 模板 ************************************
const int MAXN = 510;             // 物品数量 
const int MAXC = 3010;            // 背包容量 
typedef double ValueType;         // 背包价值的类型 
const ValueType inf = -1e9;       // 求最大值则最小，求最小值则最大 
const ValueType init = 0;         // 一般无论求最大值还是最小值，都固定为 0 

ValueType dp[MAXN][MAXC];
int pre[MAXN][MAXC];

struct Knapsack {
    int groupId;
    int capacity;
    int count;
    ValueType weight;
    Knapsack(){
    }
    Knapsack(int g, int c, int cnt, ValueType w) : groupId(g), capacity(c), count(cnt), weight(w) {
    }

    bool operator < (const Knapsack& knap) const {
        return groupId < knap.groupId;
    }
}Knap[MAXN];

struct GroupKnapsack {
    vector <Knapsack> items;
    void clear() {
        items.clear();
    }
    void add(const Knapsack& knap) {
        items.push_back(knap);
    }
    int size() const {
        return items.size();
    }
    int getGroupId() {
        if (size()) {
            return items[0].groupId;
        }
        return -1;
    }
    const Knapsack& get(int idx) const {
        return items[idx];
    }
}GKnap[MAXN];

ValueType opt(ValueType x, ValueType y) {
    return x > y ? x : y;
}

void groupKnapsackInit(int maxCapacity) {
    for (int i = 0; i <= maxCapacity; ++i) {
        dp[0][i] = (!i) ? init : inf;
        pre[0][i] = -1;
    }
}

int groupKnapsackRegroup(int knapsackSize, Knapsack *knap) {
    sort(knap, knap + knapsackSize);
    int groupId = -1;
    for (int i = 0; i < knapsackSize; ++i) {
        if (groupId == -1 || knap[i].groupId != GKnap[groupId].getGroupId())
            GKnap[++groupId].clear();

        GKnap[groupId].add(knap[i]);
    }
    return ++groupId;
}

int groupKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
    groupKnapsackInit(maxCapacity);
    int groupSize = groupKnapsackRegroup(knapsackSize, knap);
    for (int k = 1; k <= groupSize; ++k) {
        for (int j = maxCapacity; j >= 0; --j) {

            dp[k][j] = inf;
            pre[k][j] = -1;

            for (int i = 0, s = GKnap[k-1].size(); i < s; ++i) {
                const Knapsack &item = GKnap[k-1].get(i);

                if (dp[k - 1][j] > dp[k][j]) {
                    dp[k][j] = dp[k - 1][j];
                    pre[k][j] = MAXC * (k - 1) + j;
                }

                if (j >= item.capacity) {
                    if (dp[k - 1][j - item.capacity] + item.weight > dp[k][j]) {
                        dp[k][j] = dp[k - 1][j - item.capacity] + item.weight;
                        pre[k][j] = MAXC * (k - 1) + j - item.capacity;
                    }
                }
            }
        }
    }
    return groupSize;
}

//************************************ 分组背包 模板 ************************************

/*
    题意：n(n <= 1000) 个结点的树，结点1是野怪的初始位置，野怪走到任何一个叶子结点就算赢了，你可以通过以下方式
    阻止野怪进入叶子结点；

    1）每个结点都可以造至多 1 个塔；
    2）当野怪经过这个结点，塔只能进行一次射击；
    3）每个塔有 50种选择，以 价值v，伤害p 的形式给出；
    4）当野怪的血量小于等于0，野怪被击败；
    5）你可以在叶子结点和1号结点建立塔，也是有效的；
   
    问给出 m 的金额让你随便造塔，当野怪的 HP 超过多少时，你无能为力；

    题解：几个思路。
    1）野怪足够聪明，肯定会选择任意一条从 1号结点 到 叶子结点 的路，而不会折回；
    2）基于 1），伤害最小的那条路径就成为了瓶颈，所以我们需要使得伤害最小的路径尽量大；
    3）用 dp[i][j] 表示从 i 结点出发，拥有 j 的金钱 能够造成的 "最大最小伤害"；
    3）对于以 u 为根的树，二分一个它的所有子节点到叶子结点能够造成伤害的下界 K 
    
    也就是从 u 的所有子树往下走能够承受的伤害 >= K，满足这个的情况下，对每个子结点
    求一个最小消耗，如果总消耗加起来小于等于当前

    
*/

