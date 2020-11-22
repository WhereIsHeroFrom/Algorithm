#include <iostream>

using namespace std;

int gcd(int a, int b) {
    return b ? gcd(b, a % b): a; 
}

int month_day[] = {
    0,
    31,
    28,
    31,
    30,
    31,
    30,
    31,
    31,
    30,
    31,
    30,
    31
};

bool check_ymd(int year, int month, int day) {
    int run_nian = (year % 4 == 0 && year % 100 || year % 400 == 0) ? 1 : 0;
    if (month == 2) {
        return day <= month_day[month] + run_nian;
    }
    return day <= month_day[month];
}

int solve(int x, int y, int z) {
    int i;
    if(y % x) {
        return -1;
    }
    int m, d, md = y * x;
    int ans_m = -1, ans_d;
    // Ã¶¾ÙÔÂ·İ

    for(m = 1; m <= 12; m++) {
        if(md % m == 0) {
            d = md / m;
            int GCD = gcd(m, d);
            int LCM = md / GCD;
            if(GCD == x && LCM == y) {
                if( check_ymd(z, m, d) ) {
                    if(ans_m > 0) {
                        return 1;
                    }
                    ans_m = m;
                    ans_d = d;
                }
            }
        }
    }
    if(ans_m > 0) {
        printf("%d/%02d/%02d\n", z, ans_m, ans_d);
        return 0;
    }
    return -1;
}
int main() {
    int i;
    int t, cases = 0;
    scanf("%d", &t);
    while(t--) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        printf("Case #%d: ", ++cases);
        int v = solve(x, y, z);
        if(v == 1 || v == -1) {
            printf("%d\n", v);
        }
    }
    return 0;
}

