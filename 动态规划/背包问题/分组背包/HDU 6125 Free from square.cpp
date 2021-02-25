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
typedef int ValueType;            // 背包价值的类型 
const ValueType inf = 0;          // 求最大值则最小，求最小值则最大 
const ValueType init = 1;         // 一般无论求最大值还是最小值，都固定为 0 

ValueType dp[MAXN][MAXC];

#define MAXP 501
#define LL __int64
#define MOD 1000000007
int Mask[MAXP];

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
    return (x + y) % MOD;
}

void groupKnapsackInit(int maxCapacity) {
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
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
        for (int j = maxCapacity; j >= 1; --j) {
            for (int s = 0; s < 256; ++s) {

                if (dp[j - 1][s] == 0) continue;

                for (int i = 0, size = GKnap[k - 1].size(); i < size; ++i) {
                    const Knapsack &item = GKnap[k - 1].get(i);
                    int d = Mask[item.weight];
                    if ((s & d) == 0) {
                        int ormask = (s | d);
                        dp[j][ormask] += dp[j - 1][s];

                        if (dp[j][ormask] >= MOD) dp[j][ormask] %= MOD;
                    }
                }
            }

        }
    }
    return groupSize;
}

//************************************ 分组背包 模板 ************************************



int primes[MAXP];
bool notprime[MAXP];
int primeIdx[MAXP];
const int MAXBIT = 8;

int gid[MAXP];
vector <int> group[MAXP];

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
    }
}

int PrimeIndex[MAXP];

int main() {
    int i, j;
    Eratosthenes();



    int n, k, t;
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &k);

        if (k > n) {
            k = n;
        }
        for (i = 1; i <= primes[0]; ++i) {
            PrimeIndex[primes[i]] = i - 1;
        }

        for (i = 1; i <= n; ++i) {
            gid[i] = i;
            if (i == 1) {
                continue;
            }
            if (!notprime[i]) {
                if (PrimeIndex[i] <= 7)
                    Mask[i] |= (1 << PrimeIndex[i]);
                continue;
            }
            for (j = 1; j <= 8; ++j) {
                int p = primes[j];

                if (gid[i] % (p*p) == 0) {
                    gid[i] = -1;
                    break;
                }
                if (gid[i] % p == 0) {
                    gid[i] /= p;
                    Mask[i] |= (1 << j - 1);
                }
            }
            if (gid[i] == 1) {
                gid[i] = i;
            }
        }
        int tp = 0;
        for (i = 1; i <= n; ++i) {
            if (gid[i] == -1) continue;
            Knap[tp++] = Knapsack(gid[i], 1, i);
        }
        groupKnapsack(tp, Knap, k);
        int ans = 0;
        for (i = 1; i <= k; ++i) {
            for (j = 0; j < 256; ++j)
                ans = (ans + dp[i][j]) % MOD;
        }
        printf("%d\n", ans);
    }
    return 0;
}
