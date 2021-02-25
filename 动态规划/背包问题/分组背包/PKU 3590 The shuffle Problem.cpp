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

            for (int i = 0, s = GKnap[k - 1].size(); i < s; ++i) {
                const Knapsack &item = GKnap[k - 1].get(i);

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


#define MAXP 3001
#define LL __int64

int primes[MAXP];
bool notprime[MAXP];
int pri[MAXP], cnt[MAXP];

void Eratosthenes() {
    memset(notprime, false, sizeof(notprime));
    notprime[1] = true;
    primes[0] = 0;
    for (int i = 2; i < MAXP; i++) {
        if (!notprime[i]) {
            primes[++primes[0]] = i;
            //需要注意i*i超出整型后变成负数的问题，所以转化成 __int64 
            for (LL j = (LL)i*i; j < MAXP; j += i) {
                notprime[j] = true;
            }
        }
        else {
            int v = i;
            for (int j = 1; j <= primes[0]; ++j) {
                if (v % primes[j] == 0) {
                    pri[i] = primes[j];
                    cnt[i] = 0;
                    while (v % primes[j] == 0) ++cnt[i], v /= primes[j];
                    break;
                }
            }
        }
    }
}

int a[MAXP], tp;

int main() {
    int tp = 0;
    Eratosthenes();
    for (int i = 1; i <= primes[0]; ++i) {
        int val = primes[i];
        int cnt = 1;
        while (val < MAXP) {
            Knap[tp++] = Knapsack(i, val, cnt, cnt * log(0.0 + primes[i]));
            val *= primes[i];
            ++cnt;
        }
    }
    int t = groupKnapsack(tp, Knap, 1000);

    int i, S, M;
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d", &S);

        if (S == 1) {
            printf("1 1\n");
            continue;
        }

        ValueType ans = inf;
        int cap;
        for (i = 0; i <= S; ++i) {
            if (dp[t][i] > ans) {
                ans = dp[t][i];
                cap = i;
            }
        }
        int group = t;
        int sum = 0, vans = 1;
        int tp = 0;
        while (1) {
            int preidx = pre[group][cap];
            if (preidx == -1) break;

            int lastgroup = preidx / MAXC;
            int lastcap = preidx % MAXC;
            int val = cap - lastcap;
            if (val) {
                sum += val;
                /*int c = cnt[val];
                if (c == 0) a[tp++] = val;
                for (i = 0; i < c; ++i)
                a[tp++] = pri[val];*/
                a[tp++] = val;

                vans *= val;
            }

            group = lastgroup;
            cap = lastcap;
        }

        // 注意补 1
        for (i = 0; i < S - sum; ++i)
            a[tp++] = 1;

        sort(a, a + tp);
        /*for (i = 0; i < tp; ++i) {
        printf("%d ", a[i]);
        } puts("");*/

        int now = 1;
        printf("%d", vans);
        for (i = 0; i < tp; ++i) {
            for (int j = now + 1; j < now + a[i]; ++j) {
                printf(" %d", j);
            }
            printf(" %d", now);
            now += a[i];
        }
        puts("");


    }
    return 0;
}

/*
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 15 16 17 18 19 20 25
*/