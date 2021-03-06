#include <iostream>

using namespace std;

int t;

int e[14][14], w[14][14];
int n;
int first[14];
int Max;
int hash[14];

void dfs(int exp, int cre, int depth) {

    int i;

    if(depth == n - 1) {
        if(cre > Max)
            Max = cre;
        return ;
    }

    int sum = 0, tea = 0;
    for(i = 1; i < n; i++) {
        if(!hash[i]) {
            sum += e[0][i];
            tea += w[0][i];
        }
    }

    if(tea + cre <= Max)
        return ;

    for(i = 1; i < n; i++) {
        if(hash[i])
            continue;
        if(exp + sum - e[0][i] > first[i])
            break;
    }

    if(i == n)
        return;

    for(i = 1; i < n; i++) {
        if(hash[i])
            continue;
        hash[i] = 1;
        if(exp > first[i]) {
            dfs(exp + e[0][i], cre + w[0][i], depth + 1);
        }else
            dfs(exp + e[0][i], cre, depth + 1);
        hash[i] = 0;
    }
}

int main() {
    int i, j;

    scanf("%d", &t);

    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                scanf("%d", &e[i][j]);
            }
        }

        for(i = 0; i < n; i++) {
            for(j = 0; j < n ;j++) {
                scanf("%d", &w[i][j]);
            }
        }
        memset(hash, 0, sizeof(hash));

        Max = 0;

        for(i = 0; i < n; i++) 
            scanf("%d", &first[i]);
        dfs(first[0], 0, 0);
        printf("%d\n", Max);

    }
}
