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




string maleNames[maxn], femaleNames[maxn];
map <string, int> maleMaps, femaleMaps;

int findId(int& n, map <string, int>& names, string *nameList, string name) {
    if (names.find(name) == names.end()) {
        names[name] = n;
        nameList[n] = name;
        return n++;
    }
    return names[name];
}

int findMaleId(int& n, string name) {
    return findId(n, maleMaps, maleNames, name);
}

int findFemaleId(int& n, string name) {
    return findId(n, femaleMaps, femaleNames, name);
}

int idList[maxn];
int maleSize, femaleSize;
int idMaleList[maxn], idFemaleList[maxn];

int main() {
    int t;
    int n;
    int i, j;
    char names[100];

    while (scanf("%d", &n) != EOF) {
        SM.init(n);
        maleMaps.clear();
        femaleMaps.clear();
        maleSize = femaleSize = 0;

        for (i = 0; i < n; ++i) {
            scanf("%s", names);
            int maleId = findMaleId(maleSize, names);
            for (j = 0; j < n; ++j) {
                scanf("%s", names);
                int femaleId = findFemaleId(femaleSize, names);
                idList[j] = femaleId;
            }
            SM.addFemaleListToMale(maleId, idList);
        }

        for (i = 0; i < n; ++i) {
            scanf("%s", names);
            int femaleId = findFemaleId(femaleSize, names);
            for (j = 0; j < n; ++j) {
                scanf("%s", names);
                int maleId = findMaleId(maleSize, names);
                idList[j] = maleId;
            }
            SM.addMaleRankToFemale(femaleId, idList);
        }

        SM.doStableMarriage();
        SM.getCouples(idMaleList, idFemaleList);
        for (i = 0; i < n; ++i) {
            printf("%s %s\n", maleNames[idMaleList[i]].c_str(), femaleNames[idFemaleList[i]].c_str());
        }

        puts("");
    }

    return 0;
}