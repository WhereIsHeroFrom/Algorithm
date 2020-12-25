#include <iostream>
#include <algorithm>
using namespace std;

#define ll long long
#define maxn 200010

ll pow2[64];
ll a[maxn], b[maxn];
ll as[2][maxn], assize[2];
ll bs[2][maxn], bssize[2];

/*

a[i]的x位 | b[] 的x位 | a[i]和b[]x-1位之和有无进位|影响
-|-|-|-
0|0|0|无
0|0|1|有 -
0|1|0|有 -
0|1|1|无
1|0|0|有 -
1|0|1|无
1|1|0|无
1|1|1|有 -

*/

// 求满足  (tar[j] < src[i])，所有 (i,j) 对个数；
ll getTotalSmallThan(int srcSize, ll *src, int tarSize, ll *tar) {
    sort(src, src + srcSize);
    sort(tar, tar + tarSize);
    int idx = 0, cnt = 0;
    ll ans = 0;
    for (int i = 0; i < srcSize; ++i) {
        for (; idx < tarSize && tar[idx] < src[i]; ++idx) {
            ++cnt;
        }
        ans += cnt;
    }
    return ans;
}


// 求满足  (tar[j] >= src[i])，所有 (i,j) 对个数；
ll getTotalBiggerEqualThan(int srcSize, ll *src, int tarSize, ll *tar) {
    sort(src, src + srcSize);
    sort(tar, tar + tarSize);
    int idx = 0, cnt = 0;
    ll ans = 0;
    for (int i = 0; i < srcSize; ++i) {
        for (; idx < tarSize && tar[idx] < src[i]; ++idx) {
        }
        ans += (tarSize - idx);
        if (tarSize == idx) {
            break;
        }
    }
    return ans;
}


int main() {
    int t, cas = 0;
    int n, i, j;

    for (i = 0; i < 64; ++i) {
        pow2[i] = ((ll)1) << i;
    }

    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);

        for (i = 0; i < n; ++i) {
            scanf("%lld", &a[i]);
        }

        for (i = 0; i < n; ++i) {
            scanf("%lld", &b[i]);
        }

        ll ans = 0;
        for (i = 0; i <= 61; ++i) {

            bssize[0] = bssize[1] = 0;
            for (j = 0; j < n; ++j) {
                int p = (pow2[i] & b[j]) ? 1 : 0;
                ll lv = ((pow2[i] - 1) & b[j]);

                bs[p][bssize[p]++] = lv;
            }

            assize[0] = assize[1] = 0;
            for (j = 0; j < n; ++j) {
                int p = (a[j] & pow2[i]) ? 1 : 0;
                ll lv = pow2[i] - ((pow2[i] - 1) & a[j]);

                as[p][assize[p]++] = lv;
            }



            ll bit = 0;
            for (int p = 0; p < 2; ++p) {
                bit += getTotalSmallThan(assize[p], as[p], bssize[1 - p], bs[1 - p]) +
                    getTotalBiggerEqualThan(assize[p], as[p], bssize[p], bs[p]);
            }

            ans |= pow2[i] * (bit & 1);
        }

        printf("Case #%d: %lld\n", ++cas, ans);
    }
    return 0;
}

/*
13
1152921504606846976 1152900504606846976 3242 111545 0 554645656 111121 6545657 4564564563 1112  6765 211112 0
11529 215046068469 0 1052921504606846976 111435345353 454574574 1152921504606846916 11116 1117 888 999 10000 0

13
1152921504606846976 1152900504606846976 3111242 111545 110 554645656 111121 6545657 4564564563 1112  6765 211112 0
1111529 215046068469 0 1052921504606846976 111435345353 454574574 1152921504606846916 11116 1117 888 999 10000 0

5
1 2 3 4 5
1 2 3 4 5

6
1 2 3 4 5 6
2 3 4 5 6 7

17
1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768 65536
0 0 0 0  0  0  0   0   0   0    0    0    0    0     0     0     0
*/