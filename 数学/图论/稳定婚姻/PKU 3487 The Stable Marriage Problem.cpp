#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;


//***************************************** 稳定婚姻算法 模板 *****************************************
const int maxn = 1010;
const int NULL_MATCH = -1;

struct Male {
    // 当前枚举到的女性的排名
    int femaleIndex;
    // 男人的情人列表
    int females[maxn];

    // 最后输出路径的时候用
    int matchFemale;

    void init() {
        femaleIndex = 0;
    }

    void fillFemales(int n, int* femalesSort) {
        for (int i = 0; i < n; ++i) {
            females[i] = femalesSort[i];
        }
    }

    int getNextFemale() {
        return females[femaleIndex++];
    }
};

struct Female {
    // 最终配对的男性
    int matchMale;
    // 哈希数组，存储对应男性在自己心中的排名
    int maleRank[maxn];

    void init() {
        matchMale = NULL_MATCH;
    }

    void setMaleRank(int maleId, int rank) {
        maleRank[maleId] = rank;
    }

    int exchange(int maleId) {
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
};

class stateMarriage {
private:
    int count;
    Male *M;
    Female *F;

public:
    stateMarriage() : M(NULL), F(NULL) {
        M = new Male[maxn];
        F = new Female[maxn];
    }
    ~stateMarriage() {
        if (M) {
            delete[] M;
            M = NULL;
        }
        if (F) {
            delete[] F;
            F = NULL;
        }
    }

    void init(int n) {
        count = n;
        for (int i = 0; i < count; ++i) {
            F[i].init();
            M[i].init();
        }
    }

    void addFemaleListToMale(int maleId, int* femalesSort) {
        M[maleId].fillFemales(count, femalesSort);
    }

    void addMaleRankToFemale(int femaleId, int *malesSort) {
        Female &fm = F[femaleId];
        for (int i = 0; i < count; ++i) {
            fm.setMaleRank(malesSort[i], i);
        }
    }

    void work() {
        queue <int> que;
        for (int i = 0; i < count; ++i) {
            que.push(i);
        }
        while (!que.empty()) {
            int maleId = que.front();
            que.pop();
            int femaleId = M[maleId].getNextFemale();
            maleId = F[femaleId].exchange(maleId);

            if (maleId != NULL_MATCH) {
                que.push(maleId);
            }
        }
        for (int i = 0; i < count; ++i) {
            M[F[i].matchMale].matchFemale = i;
        }
        return;
    }

    void getCouples(int *males, int *females) {
        for (int i = 0; i < count; ++i) {
            males[i] = i;
            females[i] = M[i].matchFemale;
        }
    }
}SM;


string maleNames[maxn], femaleNames[maxn];

int findId(int n, string *names, string name) {
    for (int i = 0; i < n; ++i) {
        if (names[i] == name) {
            return i;
        }
    }
    return -1;
}

int findMaleId(int n, string name) {
    return findId(n, maleNames, name);
}

int findFemaleId(int n, string name) {
    return findId(n, femaleNames, name);
}

int idList[maxn];
int idMaleList[maxn], idFemaleList[maxn];

int main() {
    int t;
    int n;
    int i, j;
    char names[100];
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        SM.init(n);

        for (i = 0; i < n; ++i) {
            scanf("%s", names);
            maleNames[i] = names;
        }
        sort(maleNames, maleNames + n);
        for (i = 0; i < n; ++i) {
            scanf("%s", names);
            femaleNames[i] = names;
        }
        for (i = 0; i < n; ++i) {
            scanf("%s", names);
            string maleName = "";
            maleName.push_back(names[0]);
            int maleId = findMaleId(n, maleName);
            for (j = 2; j < 2 + n; ++j) {
                string femaleName = "";
                femaleName.push_back(names[j]);
                int femaleId = findFemaleId(n, femaleName);
                idList[j - 2] = femaleId;
            }
            SM.addFemaleListToMale(maleId, idList);
        }

        for (i = 0; i < n; ++i) {
            scanf("%s", names);
            string femaleName = "";
            femaleName.push_back(names[0]);
            int femaleId = findFemaleId(n, femaleName);
            for (j = 2; j < 2 + n; ++j) {
                string maleName = "";
                maleName.push_back(names[j]);
                int maleId = findMaleId(n, maleName);
                idList[j - 2] = maleId;
            }
            SM.addMaleRankToFemale(femaleId, idList);
        }

        SM.work();
        SM.getCouples(idMaleList, idFemaleList);
        for (i = 0; i < n; ++i) {
            printf("%s %s\n", maleNames[idMaleList[i]].c_str(), femaleNames[idFemaleList[i]].c_str());
        }

        if (t) puts("");
    }

    return 0;
}
