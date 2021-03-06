#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define MAXL 25
#define MAXN 510

char strLevel[3][10] = {
    "wonderful", "good", "so-so"
};


struct SortItem {
    char name[MAXL];
    char ori[MAXL];
    int level;

    void read() {
        char sl[MAXL];
        scanf("%s %s %s", name, ori, sl);

        for(int i = 0; i < 3; ++i) {
            if(strcmp(sl, strLevel[i]) == 0) level = i;
        }

    }        
    bool operator<(const SortItem& other) {
        int cmpOri = strcmp(ori, other.ori);

        if(cmpOri) {
            return cmpOri < 0;
        }

        if(level != other.level) {
            return level < other.level;
        }

        return strcmp(name, other.name) < 0;
    }
}SI[MAXN];

int main() {
    int i, n, cases = 0;
    while( scanf("%d", &n) != EOF ) {
        for(i = 0; i < n; ++i) {
            SI[i].read();
        }
        sort(SI, SI + n);
        printf("Case %d\n", ++cases);
        for(i = 0; i < n; ++i) {
            if(i == 0 || strcmp(SI[i].ori, SI[i-1].ori) ) {
                printf("%s:\n", SI[i].ori);
            }
            printf("          %s %s\n", SI[i].name, strLevel[SI[i].level]);
        }
    }
    return 0;
}

/*
5
knife qizhou so-so
gun qizhou wonderful
knife qizhou good
stick qizhou good
rope qizhou so-so
*/
