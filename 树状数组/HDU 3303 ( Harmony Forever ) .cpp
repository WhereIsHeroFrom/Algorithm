#include <iostream>

using namespace std;

#define mod_split 6208
#define maxn 500010
int n;
int ans[mod_split + 1], tim[ mod_split + 1 ];
int c[maxn];
int nt[maxn];

inline int lowbit(int x) {
    return x & (-x);
}

void add(int pos) {
    while(pos < maxn) {
        ++c[pos];
        pos += lowbit(pos);
    }
    return ;
}

int sum(int pos) {
    int s = 0;
    while(pos > 0) {
        s += c[pos];
        pos -= lowbit(pos);
    }
    return s;
}

int Bin(int l, int r) {
    if(!l) l++;
    if(l >= maxn) l = maxn - 1;
    if(r >= maxn) r = maxn - 1;

    int ans = -1;
    int pre = sum(l - 1);
    while(l <= r) {
        int m = (l + r) >> 1;
        if(sum(m) - pre > 0) {
            r = m - 1;
            ans = m;
        }else
            l = m + 1;
    }
    return ans;
}

int main() {
    int i, j;
    int Case = 1;
    while(scanf("%d", &n) != EOF && n) {
        if(Case != 1)
            puts("");

        for(j = 0; j <= mod_split; j++) {
            ans[j] = mod_split + 1;
            tim[j] = -1;
        }
        memset(c, 0, sizeof(c));
        printf("Case %d:\n", Case ++ );
        int Time = 0;
        for(i = 1; i <= n; i++) {
            char str[10];
            int x;
            scanf("%s %d", str, &x);
            if(str[0] == 'B') {
                Time ++;
                for(j = 1; j <= mod_split; j++) {
                    int p = x % j;
                    if(p <= ans[j]) {
                        ans[j] = p;
                        tim[j] = Time;
                    }
                }
                add(x);
                nt[x] = Time;
            }else {
                if(x <= mod_split) {
                    printf("%d\n", tim[x]);
                }else {
                    int l = 0, r = x - 1;
                    int MinVal = -1;
                    int MinTime;
                    while(1) {
                        int v = Bin(l, r);
                        if(v != -1) {
                            int Mod = v % x;
                            if(Mod < MinVal ||  MinVal == -1) {
                                MinVal = Mod;
                                MinTime = nt[v];
                            }else if(Mod == MinVal) {
                                if(MinTime < nt[v])
                                    MinTime = nt[v];
                            }
                        }
                        if(l >= maxn || r >= maxn)
                            break;
                        l += x;
                        r += x;
                    }

                    if(MinVal != -1)
                        printf("%d\n", MinTime);
                    else
                        printf("-1\n");
                }
            }
        }

    }
    return 0;
}
