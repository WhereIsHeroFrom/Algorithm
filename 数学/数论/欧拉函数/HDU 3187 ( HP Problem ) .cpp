/*
    题意：给定n(n < 2^31)，求  k的欧拉函数=n，且k的素因子个数 <= 3, 满足条件的k的个数。
    k的素因子个数等于1个的情况   (p1-1)p1^(x1-1) = n
    k的素因子个数等于2个的情况   (p1-1)p1^(x1-1) * (p2-1)p2^(x2-1) = n
    k的素因子个数等于3个的情况   (p1-1)p1^(x1-1) * (p2-1)p2^(x2-1) * (p3-1)p3^(x3-1) = n

*/
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define MAXP 70000
#define LL __int64

int primes[MAXP];
bool notprime[MAXP];

struct factor {
    int prime, count;
    factor() {
    } 
    factor(int p, int c) {
        prime = p;
        count = c;
    }
    void print() {
        printf("(%d, %d)\n", prime, count);
    }
};

// 厄尔多塞素数筛选法 
void Eratosthenes() {
    memset(notprime, false, sizeof(notprime));
    notprime[1] = true;
    primes[0] = 0;
    for(int i = 2; i < MAXP; i++) {
        if( !notprime[i] ) {
            primes[ ++primes[0] ] = i;
            //需要注意i*i超出整型后变成负数的问题，所以转化成 __int64 
            for(LL j = (LL)i*i; j < MAXP; j += i) {
                notprime[j] = true;
            }
        }
    }
}

bool isPrime(int v) {
    if(v < MAXP) {
        return !notprime[v];
    }
    int i;
    for(i = 1; i <= primes[0]; ++i) {
        if(v % primes[i] == 0) {
            return false;
        }
    }
    return true;
}

int p[3], c[3], top;
int ans;

void dfs(int n, int preprime, int depth) {

    int i, j;
    if(n == 1) {        
        LL checkVal = 1;
        for(i = 0; i < top; ++i) {
            //if(i) printf("*");
            //printf("%d^%d", p[i], c[i]);
            for(j = 0; j < c[i]; ++j) {
                checkVal *= p[i];
                if(checkVal >= ((LL)1<<31)) {
                    return;
                }
            }
        }
        //puts("");
        ++ans;

        return;
    }

    if(depth == 3) {
        return ;
    }
    for(i = primes[0]; i >= 1; --i) {
        if(primes[i] <= preprime) {
            break;
        }
        p[top] = primes[i];

        LL oula = (p[top]-1);
        for(j = 1; oula <= n; ++j) {
            c[top] = j;
            if(n % oula == 0) {
                ++top;
                dfs(n/oula, primes[i], depth+1);
                --top;
            }else {
                break;
            }
            oula *= p[top];
        }
    }

    // n+1是个大素数的情况
    if(isPrime(n+1)) {
        if(n+1 > primes[ primes[0] ]) {
            p[top] = n+1;
            c[top] = 1;
            ++top;
            dfs(1, n+1, depth+1);
            --top;
        }
    }


}

int main() {
    Eratosthenes();
    int n;
    while( scanf("%d", &n) != EOF ) {
        if(n == 1) {
            // 欧拉函数是1的有两个：  1和2
            printf("2\n");
            continue;
        }
        ans = 0;
        dfs(n, 0, 0);
        printf("%d\n", ans);
    }
    return 0;
}



