#include <iostream>
#include <vector>
using namespace std;

#define maxn 10011
#define maxm 802

bool f[maxn];
int prime[maxn], size;
int prime_idx[maxn];

struct PrimeFactor {
    short num;    // 素因子数量
    short pri;    // 素因子在prime[]的下标
    PrimeFactor() {}
    PrimeFactor(int _n, int _p) {
        num = _n;
        pri = _p;
    }
};
vector < PrimeFactor > PriFac[maxn];
int preAns[maxn][maxm];

int DFS(int n, int p) {
    if(p < maxm)
        return preAns[n][p];
    p = prime[p];
    int s = 0;
    while(n >= p) {
        int tmp = n / p;
        s += tmp;
        n = tmp;
    }
    return s;
}

void Init() {
    int i, j;
    for(i = 2; i < maxn; i++) {
        if(!f[i]) {
            PriFac[i].push_back(PrimeFactor(1, size));
            for(j = i+i; j < maxn; j += i) {
                f[j] = 1;

                PrimeFactor pf;
                pf.num = 1;
                pf.pri = size;
                int v = j / i;

                while(!(v % i)) {
                    v /= i;
                    pf.num ++;
                }
                PriFac[j].push_back(pf);
            }
            prime[size] = i;
            prime_idx[i] = size;
            
            size++;
        }
    }

    int nCount = 0;
    for(i = 2; i <= 10006; i++) {
        for(j = 0; j < PriFac[i].size(); j++) {
            if(PriFac[i][j].pri < maxm)
                preAns[i][ PriFac[i][j].pri ] = PriFac[i][j].num;
        }
        for(j = 0; j < maxm; j++)
            preAns[i][j] += preAns[i-1][j];
    }
}

int n, m;
int prime_num[maxn];
int tmp_num[maxn];

vector < PrimeFactor > vecAns;

int Min(int a, int b) {
    return a < b ? a : b;
}

void Calc(int nMax) {
    int i, j;
    int MaxDeg = INT_MAX;
    for(i = nMax; i >= 2; i--) {
        MaxDeg = INT_MAX;
        for(j = 0; j < size && prime[j] <= i; j++) {
            if(DFS(i, j)) 
                MaxDeg = Min(MaxDeg, prime_num[j] / DFS(i, j));
            if(MaxDeg == 0)
                break;
        }

        if(MaxDeg) {
            break;
        }
    }

    if(i >= 2) {
        nMax = i;
        vecAns.push_back(PrimeFactor(MaxDeg, nMax));
        for(i = 0; i < size && prime[i] <= nMax; i++) {
            prime_num[i] -= MaxDeg * DFS(nMax, i);
        }
        if(nMax > 2)
            Calc(nMax - 1);
    }
}

int p[maxn], q[maxn];
int c[20 + maxn];
int lowbit(int x) {
    return x & (-x);
}

int sum(int pos) {
    int s = 0;
    while(pos > 0) {
        s += c[pos];
        pos -= lowbit(pos);
    }
    return s;
}

void add(int pos, int v) {
    while(pos < maxn) {
        c[pos] += v;
        pos += lowbit(pos);
    }
}

int main() {
    Init();
    int t, i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        for(i = 0; i < size; i++)
            prime_num[i] = 0;
            
        memset(c, 0, sizeof(c));
        for(i = 0; i < n; i++) {
            scanf("%d", &p[i]);
            //p[i] = 10000;
            add(1, 1);
            add(p[i]+1, -1);
        }
        for(i = 2; i <= 10000; i++) {
            int v = sum(i);
            if(v) {
                for(j = 0; j < PriFac[i].size(); j++) {
                    prime_num[ PriFac[i][j].pri ] += PriFac[i][j].num * v;
                }
            }
        }

        memset(c, 0, sizeof(c));
        bool flag = true;
        for(i = 0; i < m; i++) {
            scanf("%d", &q[i]);
            //q[i] = 1;
            add(1, 1);
            add(q[i]+1, -1);
        }

        for(i = 2; i <= 10000; i++) {
            int v = sum(i);
            if(v) {
                for(j = 0; j < PriFac[i].size(); j++) {
                    prime_num[ PriFac[i][j].pri ] -= PriFac[i][j].num * v;
                    if(prime_num[ PriFac[i][j].pri ] < 0) {
                        flag = false;
                        break;
                    }
                }
            }
            if(!flag)
                break;
        }


        if(!flag) {
            printf("-1\n");
        }else {
            vecAns.clear();
            Calc(10006);
            
            printf("%d\n", vecAns.size());
            for(i = 0; i < vecAns.size(); i++) {
                printf("%d %d\n", vecAns[i].pri, vecAns[i].num);
            }
        }
    }

    return 0;
}

/*
23213
1000 1000
1000 1000
1000 1000
1000 1000
1000 1000
1000 1000
1000 1000
1000 1000
1000 1000
*/
