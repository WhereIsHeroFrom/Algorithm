#include <iostream>

using namespace std;

#define MAXN 10010

int c[MAXN], hashv[MAXN], x[MAXN];
int n;

int lowbit(int x) {
    return x & (-x);
}

void add(int x) {
    while(x <= n) {
        ++ c[x];
        x += lowbit(x);
    }    
}

int sum(int x) {
    int s = 0;
    if(x > n) x = n;
    while(x) {
        s += c[x];
        x ^= lowbit(x);
    }
    return s;
}

bool findv(int depth, int x, int checkVal) {
    int nCount = sum(n);
    int xCount = sum(x);
    if(nCount - xCount == 0 || depth > 10) {
        return false;
    }
    
    int low = x+1, high = n;
    int ans = -1;
    while(low <= high) {
        int mid = (low + high) >> 1;
        if(sum(mid) - xCount > 0) {
            ans = mid;
            high = mid - 1;
        }else {
            low = mid + 1;
        }
    }
    //printf("?? %d %d %d\n", x, checkVal, ans);
    int result = 2*checkVal - ans;
    
    if(result <= 0) {
        return false;
    }else if(result > n || hashv[result]) {
        return findv(depth+1, ans, checkVal);
    }
    //printf("%d %d %d\n", ans, checkVal, result);
    return true;
}

bool check() {
    int i, p[3];
    for(i = 0; i < n; i++) {
        hashv[x[i]] = i; 
    }
    
    for(i = n; i >= 3; --i) {
        int d = 1;
        while(i > 2*d) {
            p[0] = hashv[i];
            p[1] = hashv[i - d];
            p[2] = hashv[i - 2*d];
            //printf("%d %d %d>>>\n", p[0], p[1], p[2]);
            if(p[0] < p[1] && p[1] < p[2]) {
                return true;
            }
            if(p[0] > p[1] && p[1] > p[2]) {
                return true;
            }
            ++d;
         }
    }
    return false;
}

int main() {
    int t;
    int i;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++) {
            scanf("%d", &x[i]);
            //x[i] = i+1;
        }
        bool f = check();
        if(f) {
            printf("Y\n");
        }else {
            printf("N\n");
        }
    }
    return 0;
} 

/*
10
10
7 1 3 2 9 8 5 10 4 6
5
3 4 5 1 2

3
1 3 2
4
3 2 4 1
*/
