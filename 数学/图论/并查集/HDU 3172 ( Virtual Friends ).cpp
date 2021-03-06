#include <iostream>
#include <string>
using namespace std;

#define mod 300007

int hash[mod], Case;
string key[mod];
int id[mod], T;

int prev[mod], num[mod];

int HASH(string str) {
    int i;
    int S = 0;
    for(i = 0; i < str.length(); i++) {
        S = (S * 307 + str[i]) % mod;
    }
    if(S < 0)
        S += mod;

    while(1) {
        if(hash[S] != Case) {
            hash[S] = Case;
            key[S] = str;
            id[S] = ++T;
            return id[S];
        }else {
            if(key[S] == str) {
                return id[S];
            }
            S++;
            if(S == mod)
                S = 0;
        }
    }
}

int Find(int x) {
    while(x != prev[x]) {
        x = prev[x];
    }
    return x;
}

int Union(int x, int y) {
    int fx = Find(x);
    int fy = Find(y);

    if(fx == fy) {
        return num[fx];
    }

    if(num[fx] > num[fy]) {
        prev[fy] = fx;
        num[fx] += num[fy];
        return num[fx];
    }else {
        prev[fx] = fy;
        num[fy] += num[fx];
        return num[fy];
    }

}

char str[2][100];
int n;

int main() {
    int t, i;
    while( scanf("%d", &t) != EOF ) {
        while(t--) {
            scanf("%d", &n);
            T = 0;
            Case ++;
            for(i = 1; i <= 2 * n; i++) {
                prev[i] = i;
                num[i] = 1;
            }

            while(n--) {
                scanf("%s %s", str[0], str[1]);
                int id1 = HASH(str[0]);
                int id2 = HASH(str[1]);
                //printf("%d %d\n", id1, id2);
                printf("%d\n", Union(id1, id2));
            }
        }
    }
    return 0;
}
