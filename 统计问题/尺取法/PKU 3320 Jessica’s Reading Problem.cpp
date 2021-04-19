#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 1000010;
int a[maxn];
int n;

int b[maxn], bsize;
int has[maxn];

void sortIt()
{
    sort(b, b + bsize);
    int tmpbsize = 0;
    for (int i = 0; i < bsize; ++i) {
        if (tmpbsize == 0 || b[tmpbsize - 1] != b[i]) {
            b[tmpbsize++] = b[i];
        }
    }
    bsize = tmpbsize;
}

int binVal(int val) {
    int l = 0, r = bsize - 1; 
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (b[mid] == val) {
            return mid;
        }
        else if (val > b[mid]) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
}

int solve() {
    int ans = n;
    int s = 0, i = 1, j = 0;
    while (j < n) {
        ++j;
        if (++has[a[j]] == 1) {
            ++s;
            while (s == bsize) {
                ans = min(ans, j - i + 1);
                if (--has[a[i]] == 0) {
                    --s;
                }
                ++i;
            }
        }
    }
    return ans;
}

int main() {
    int t;
    while (scanf_s("%d", &n) != EOF) {
        bsize = 0;
        for (int i = 1; i <= n; ++i) {
            scanf_s("%d", &a[i]);
            b[bsize++] = a[i];
        }
        sortIt();
        
        has[0] = 0;
        for (int i = 1; i <= n; ++i) {
            a[i] = binVal(a[i]);
            has[i] = 0;
        }
        
        printf("%d\n", solve());
    }
    return 0;
}
