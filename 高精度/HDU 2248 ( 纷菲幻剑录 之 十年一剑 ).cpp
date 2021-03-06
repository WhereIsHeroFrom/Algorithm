#include <iostream>

using namespace std;

int f[10000];
char str[1000];
int prime[10000], size;
struct BigNum {
    int a[10000];
    int len;
}M, T, R;

void Swords() {
    int p;
    scanf("%s", str);
    p = strlen( str );
    printf("%s\n", !f[p] ? "Yes." : "No.");
}

void Multiply(BigNum a, BigNum b) {
    int i, j, k;
    for(i = 0; i < 10000; i++) {
        M.a[i] = 0;
    }
    M.len = 0;

    for(i = 0; i < a.len; i++) {
        for(j = 0; j < b.len; j++) {
            M.a[i+j] += a.a[i] * b.a[j];
        }
    }

    for(j = 9999; j >= 0; j--) {
        if(M.a[j])
            break;
    }
    for(i = 0; i <= j; i++) {
        if(M.a[i] >= 10) {
            M.a[i+1] += M.a[i] / 10;
            M.a[i] %= 10;
        }
    }

    if(M.a[j+1] != 0)
        M.len = j + 2;
    else
        M.len = j + 1;
}
void Bin(int n) {

    if(n == 0) {
        M.a[0] = 1;
        M.len = 1;
        return ;
    }

    int p = n / 2;
    Bin(p);
    T = M;
    Multiply(T, T);  //????M
    T = M;
    if(n & 1)
        Multiply(T, R);
}

void See() {
    int i, p;
    scanf("%d", &p);
    Bin(p);         //????M??
    for(i = M.len - 1; i >= 0; i--) {
        printf("%d", M.a[i]);
    }
    puts("");
}

int hash[200001];
int a[200001];
int Min, start, end;

void Stones() {
    int i, n;
    scanf("%d", &n);
    a[0] = 0;
    for(i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        a[i] %= n;
    }
    Min = 100000000;

    for(i = 1; i <= n; i++) {
        a[i] += a[i-1];
        a[i] %= n;
    }

    memset(hash, -1, sizeof(hash));

    hash[ 0 ] = 0;

    for(i = 1; i <= n; i++) {
        if(hash[ a[i] ] != -1) {
            if(i - hash[ a[i] ] == Min) {

                if(hash[ a[i] ] + 1 < start) {
                    Min = i - hash[ a[i] ];
                    start = hash[ a[i] ] + 1;
                    end = i;
                }
            }

            if(i - hash[ a[i] ] < Min) {
                Min = i - hash[ a[i] ];
                start = hash[ a[i] ] + 1;
                end = i;
            }
        }
        hash[ a[i] ] = i;
    }

    for(i = start; i <= end; i++) {
        if(i > start) printf(" ");
        printf("%d", i);
    }
    puts("");

}

void Search() {

    int i, x, k;

    scanf("%d %d", &x, &k);
    
    if(x == 1) {
        printf("0\n");
        return ;
    }

    int yu = 0;
    for(i = 0; i < size; i++) {
        if(x % prime[i] == 0) {
            k --;
            if(k == 0) {
                yu = 1;
                break;
            }
            x /= prime[i];

            int flag = 0;
            while(x % prime[i] == 0) {
                k --;
                x /= prime[i];
                if(k == 0) {
                    flag = 1;
                    break;
                }
            }
            yu = flag;
            if(flag == 1)
                break;
        }
    }

    if(!k)
        printf("%d\n", prime[i] );
    else {
        if(x > 1) {
            if(k == 1)
                printf("%d\n", x);
            else
                printf("no\n");
        }else {
            printf("no\n");
        }
    }
}

int main() {
    int i, j;
    f[0] = f[1] = 1;
    for(i = 2; i <= 8000; i++) {
        if(!f[i]) {
            prime[ size++ ] = i;
            for(j = i+i; j <= 8000; j += i)
                f[j] = 1;
        }
    }
    R.a[0] = 2;
    R.len = 1;

    while(scanf("%s", str) != EOF ){
        if(strcmp( str, "Swords" ) == 0)
            Swords();
        else if(strcmp( str, "See" ) == 0) 
            See();
        else if(strcmp( str, "Stones" ) == 0) 
            Stones();
        else if(strcmp( str, "Search" ) == 0) 
            Search();
    }
    return 0;
}


