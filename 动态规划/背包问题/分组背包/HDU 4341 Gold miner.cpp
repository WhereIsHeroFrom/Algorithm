#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ 分组背包 模板 ************************************
const int MAXN = 210;             // 物品数量 
const int MAXC = 40010;           // 背包容量 
typedef int ValueType;            // 背包价值的类型 
const ValueType inf = -1e9;       // 求最大值则最小，求最小值则最大 
const ValueType init = 0;         // 一般无论求最大值还是最小值，都固定为 0 

ValueType dp[MAXC];

struct Knapsack {
    int groupId;
    int capacity;
    ValueType weight;
    Knapsack(){
    }
    Knapsack(int g, int c, ValueType w) : groupId(g), capacity(c), weight(w) {
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
        dp[i] = (!i) ? init : inf;
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

void groupKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
    groupKnapsackInit(maxCapacity);
    int groupSize = groupKnapsackRegroup(knapsackSize, knap);
    for (int i = 0; i < groupSize; ++i) {
        for (int j = maxCapacity; j >= 0; --j) {
            for (int k = 0, s = GKnap[i].size(); k < s; ++k) {
                const Knapsack &item = GKnap[i].get(k);
                if (j >= item.capacity)
                    dp[j] = opt(dp[j], dp[j - item.capacity] + item.weight);
            }
        }
    }
}

//************************************ 分组背包 模板 ************************************

int n, m;

struct Point {
    int x, y;
    int cap, val;
    int dist;
    Point() {}

    Point(int _x, int _y, int _c, int _v) : x(_x), y(_y), cap(_c), val(_v) {
        dist = x * x + y * y;
    }

    Point operator - (const Point& o) {
        return Point(x - o.x, y - o.y, 0, 0);
    }

    bool coline(const Point& o) const {
        return x * o.y - y * o.x == 0;
    }

    bool operator <(const Point o) const {
        return dist < o.dist;
    }
}P[210];

vector <Point> PSet[210];
int setId[210];

int main() {
    int i, j;
    int cas = 0;

    while (scanf("%d %d", &n, &m) != EOF) {
        for (i = 0; i < n; ++i) {
            int x, y, c, v;
            scanf("%d %d %d %d", &x, &y, &c, &v);
            P[i] = Point(x, y, c, v);
            setId[i] = i;
            PSet[i].clear();
        }
        for (i = 0; i < n; ++i) {
            for (j = i + 1; j < n; ++j) {
                if (P[i].coline(P[j])) {
                    setId[j] = setId[i];
                }
            }
        }

        for (i = 0; i < n; ++i) {
            PSet[setId[i]].push_back(P[i]);
        }

        int tp = 0;
        for (i = 0; i < n; ++i) {
            sort(PSet[i].begin(), PSet[i].end());
            int sumcap = 0, sumval = 0;
            for (j = 0; j < PSet[i].size(); ++j) {
                sumcap += PSet[i][j].cap;
                sumval += PSet[i][j].val;

                Knap[tp++] = Knapsack(i, sumcap, sumval);
            }
        }
        groupKnapsack(tp, Knap, m);
        int ans = inf;
        for (i = 0; i <= m; ++i) ans = opt(ans, dp[i]);
        printf("Case %d: %d\n", ++cas, ans);
    }
    return 0;
}

/*
5 10
1 1 1 1
2 2 2 1
3 3 6 1
4 4 2 1
5 5 3 1
*/