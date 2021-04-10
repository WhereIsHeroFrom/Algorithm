#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn = 110;
char v[maxn];
int power[maxn], val[maxn];
int sum, stk[maxn];
int k;
int sumhash[6][110][10010];

bool dfs(int depth, int maxdep, int pre, int tot, int sum) {

    if (depth == maxdep) {
        if (sum == 0) {
            //  找到解，输出答案
            puts(v);
        }
        return sum == 0;
    }

    if (sumhash[depth][pre][sum]) {
       return false;
    }
    sumhash[depth][pre][sum] = 1;

    for (int i = pre; i <= tot; ++i) {
        char tp = v[i];
        int s = (i == 0) ? 1 : 0;
        for (int j = s; j < tp - '0'; ++j) {
            int to = j + '0';
            int dsum = (to - tp) * power[tot - i] % k;
            if (dsum < 0) dsum += k;
            v[i] = to;
            if (dfs(depth + 1, maxdep, i + 1, tot, (sum + dsum) % k)) {
                return 1;
            }
        }
        v[i] = tp;
        if (dfs(depth, maxdep, i + 1, tot, sum)) {
            return 1;
        }
    }


    for (int i = pre; i <= tot; ++i) {
        char tp = v[i];
        if (i == 0 && tp == '0') tp = '1';
        for (int j = tp-'0'; j <= 9; ++j) {
            int to = j + '0';
            int dsum = (to - tp) * power[tot - i] % k;
            if (dsum < 0) dsum += k;
            v[i] = to;
            if (dfs(depth + 1, maxdep, i + 1, tot, (sum + dsum) % k)) {
                return 1;
            }
        }

        v[i] = tp;
    }
    return 0;
}

int main() {
    while (scanf("%s %d", v, &k) != EOF) {
        int len = strlen(v);
        sum = 0;
        for (int cnt = 0, i = len - 1; i >= 0; ++cnt, --i) {
            if (cnt == 0) {
                power[cnt] = 1;
            }
            else {
                power[cnt] = power[cnt - 1] * 10 % k;
            }
            val[cnt] = power[cnt] * (v[i] - '0') % k;
            sum = (sum + val[cnt]) % k;
        }

        

        for (int i = 0;; ++i) {
            memset(sumhash, 0, sizeof(sumhash));
            if (dfs(0, i, 0, len - 1, sum)) {
                //printf("%d\n", i);
                break;
            }
        }
    }

    return 0;
}
/*
1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
3260

1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
4375

1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
4500

1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
6250

1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
8750

1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
9600

1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
9999
*/
