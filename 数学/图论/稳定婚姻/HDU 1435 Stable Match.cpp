#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
using namespace std;


//***************************************** 稳定婚姻算法 模板 *****************************************//
const int maxn = 1010;
const int NULL_MATCH = -1;

class Male {
    int femaleIndex;        // 当前枚举到的女性的排名
    int females[maxn];      // 男孩的追求列表，按照好感度顺序依次递减
public:
    void init();
    void fillFemales(int n, int* femalesSort);
    int popNextFemale();
};

void Male::init() {
    femaleIndex = 0;
}
void Male::fillFemales(int n, int* femalesSort) {
    for (int i = 0; i < n; ++i) {
        females[i] = femalesSort[i];
    }
}
int Male::popNextFemale() {
    return females[femaleIndex++];
}



struct Female {
    int matchMale;          // 最终配对的男性
    int maleRank[maxn];     // 哈希数组，存储对应男性在自己心中的排名
public:
    void init();
    void setMaleRanks(int n, int *malesSort);
    int exchange(int maleId);
};

void Female::init() {
    matchMale = NULL_MATCH;
}

void Female::setMaleRanks(int n, int *malesSort) {
    for (int i = 0; i < n; ++i) {
        maleRank[malesSort[i]] = i;
    }
}

int Female::exchange(int maleId) {
    if (matchMale == NULL_MATCH) {
        matchMale = maleId;
        return NULL_MATCH;
    }
    int pre = maleRank[matchMale];
    int now = maleRank[maleId];
    if (pre < now) {
        return maleId;
    }
    else {
        int tmp = matchMale;
        matchMale = maleId;
        return tmp;
    }
}

class stableMarriage {
private:
    int count;
    Male *M;
    Female *F;

public:
    stableMarriage() : M(NULL), F(NULL) {
        M = new Male[maxn];
        F = new Female[maxn];
    }
    ~stableMarriage();
    void init(int n);
    void addFemaleListToMale(int maleId, int* femalesSort);
    void addMaleRankToFemale(int femaleId, int *malesSort);
    void doStableMarriage();
    void getCouples(int *males, int *females);
}SM;

stableMarriage::~stableMarriage() {
    if (M) {
        delete[] M;
        M = NULL;
    }
    if (F) {
        delete[] F;
        F = NULL;
    }
}

void stableMarriage::init(int n) {
    count = n;
    for (int i = 0; i < count; ++i) {
        F[i].init();
        M[i].init();
    }
}

void stableMarriage::addFemaleListToMale(int maleId, int* femalesSort) {
    M[maleId].fillFemales(count, femalesSort);
}

void stableMarriage::addMaleRankToFemale(int femaleId, int *malesSort) {
    F[femaleId].setMaleRanks(count, malesSort);
}

void stableMarriage::doStableMarriage() {
    queue <int> que;
    for (int i = 0; i < count; ++i) {
        que.push(i);
    }
    while (!que.empty()) {
        int maleId = que.front();
        que.pop();
        int femaleId = M[maleId].popNextFemale();
        maleId = F[femaleId].exchange(maleId);
        if (maleId != NULL_MATCH) {
            que.push(maleId);
        }
    }
}

void stableMarriage::getCouples(int *males, int *females) {
    for (int i = 0; i < count; ++i) {
        males[i] = i;
        females[F[i].matchMale] = i;
    }
}
//***************************************** 稳定婚姻算法 模板 *****************************************//



double SQR(double x) {
    return x * x;
}

struct Sort {
    int index;
    double dist;
    int cap;

    Sort(){}
    Sort(int _index, double _dist, int _cap) : index(_index), dist(_dist), cap(_cap)
    {
    }

    bool operator < (const Sort& o) const {
        if (fabs(dist - o.dist) < 1e-8) {
            return cap > o.cap;
        }
        return dist < o.dist;
    }
}S[maxn];

struct Point {
    int index;
    int id;
    int cap;
    double x, y, z;

    void read(int i) {
        index = i;
        scanf("%d %d", &id, &cap);
        scanf("%lf%lf%lf", &x, &y, &z);
    }
    double dist(const Point& o) const {
        return SQR(x - o.x) + SQR(y - o.y) + SQR(z - o.z);
    }

    Sort get(const Point& o) {
        return Sort(o.index, dist(o), o.cap);
    }

}male[maxn], female[maxn];


int idList[maxn];
int maleIds[maxn], femaleIds[maxn];

int main() {
    int t;
    int n;
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);
        SM.init(n);
        for (int i = 0; i < n; ++i) {
            male[i].read(i);
        }
        for (int i = 0; i < n; ++i) {
            female[i].read(i);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                S[j] = male[i].get(female[j]);
            }
            sort(S, S + n);
            for (int j = 0; j < n; ++j) {
                idList[j] = S[j].index;
            }
            SM.addFemaleListToMale(i, idList);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                S[j] = female[i].get(male[j]);
            }
            sort(S, S + n);
            for (int j = 0; j < n; ++j) {
                idList[j] = S[j].index;
            }
            SM.addMaleRankToFemale(i, idList);
        }
        SM.doStableMarriage();
        SM.getCouples(maleIds, femaleIds);
        for (int i = 0; i < n; ++i) {
            printf("%d %d\n", male[maleIds[i]].id, female[femaleIds[i]].id);
        }

    }

    return 0;
}