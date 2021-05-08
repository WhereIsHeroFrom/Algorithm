#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;
#pragma warning(disable : 4996)

int days[] = {
    0,
    31, 28, 31, 30, 31, 30,
    31, 31, 30, 31, 30, 31
};

#define ll long long
const int maxn = 4000003;

int anshigh[maxn];
short anslow[maxn];
ll tmp[maxn];
int anstot;
int digit = 4;
ll p10[19];

int getday(ll year, int month) {
    int day = days[month];
    if (month != 2) {
        return day;
    }
    if (year % 400 == 0 || (year % 4 == 0 && year % 100)) {
        ++day;
    }
    return day;
}

void init() {
    p10[0] = 1;
    for (int i = 1; i < 19; ++i) {
        p10[i] = p10[i - 1] * 10;
    }
}

int validyear4[10000], vy4;
int year42month[10000], year42day[10000];

int gethuiwen(int dcount, int val) {
    if (dcount <= 1) {
        return val;
    }
    int stk[20], tp = 0;
    int vv = val;
    int need = (dcount + 1) / 2;
    while (tp < need) {
        stk[tp++] = vv % 10;
        vv /= 10;
    }
    int ans = val * p10[dcount / 2];
    for (int i = dcount / 2 - 1; i >= 0; --i) {
        ans += stk[need - 1 - i] * p10[i];
    }
    return ans;
}

bool enumyear(int dcount) {
    for (int i = 0; i < vy4; ++i) {
        ll year4 = validyear4[i];
        ll yearpre = year4 * p10[dcount];
        int totalcnt = p10[(dcount + 1) / 2];
        for (int j = 0; j < totalcnt; ++j) {
            int num = gethuiwen(dcount, j);
            ll year = yearpre + num;
            int month = year42month[year4];
            int day = year42day[year4];
            if (day > getday(year, month))
                continue;
            ll ans = year * 10000 + month * 100 + day;
            if (anstot && (year / 10000 < anshigh[anstot - 1])) {
                int zz = 4;
                zz = zz - 1;
            }
            anshigh[anstot] = year / 10000;
            anslow[anstot++] = year % 10000;


            if (anstot >= maxn - 1) {
                return true;
            }
        }
    }
    return false;
}

ll gethuiwennum(int dcount, ll leftval, int midval) {
    if (dcount == 1) {
        return midval;
    }
    ll ans = 0;

    if (midval == -1) {
        int len = dcount / 2;
        ans = leftval * p10[len];

        for (int i = 0; i < len; ++i) {
            ll v = p10[i];
            ans += v * (leftval / p10[len - i - 1] % 10);
        }
    }
    else {
        int len = (dcount - 1) / 2;
        ans = leftval * p10[len + 1] + midval * p10[len];

        for (int i = 0; i < len; ++i) {
            ll v = p10[i];
            ans += v * (leftval / p10[len - i - 1] % 10);
        }
    }

    return ans;
}

int main() {
    init();
    for (int year = 1000; year <= 9999; ++year) {
        int month10 = year % 10;
        int month1 = year / 10 % 10;
        int month = month10 * 10 + month1;
        if (month <= 0 || month > 12) {
            continue;
        }
        year42month[year] = month;
        int day10 = year / 100 % 10;
        int day1 = year / 1000 % 10;
        int day = day10 * 10 + day1;
        if (day <= 0 || day >= 32) {
            continue;
        }
        year42day[year] = day;
        validyear4[vy4++] = year;
    }
    for (int i = 0; ; ++i) {
        if (enumyear(i)) {
            break;
        }
    }
    int t;
    scanf("%d", &t);

    while (t--) {
        int K;
        scanf("%d", &K);
        ll ans = (ll)anshigh[K - 1] * 10000 + anslow[K - 1];
        int stk[20], top = 0;
        ll anstmp = ans;
        while (anstmp) {
            stk[top++] = anstmp % 10;
            anstmp /= 10;
        }
        ans = ans * 10000 + (ll)stk[top - 1] + (ll)stk[top - 2] * 10 + (ll)stk[top - 3] * 100 + (ll)stk[top - 4] * 1000;

        printf("%lld\n", ans);
    }
    return 0;
}
/*
1111
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45

*/