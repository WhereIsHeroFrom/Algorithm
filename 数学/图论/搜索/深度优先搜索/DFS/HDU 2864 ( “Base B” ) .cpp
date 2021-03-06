#include <iostream>

using namespace std;

int A, B;
int stack[110], top;

bool dfs(int sum) {
    if(sum == 0) {
        for(int i = 0; i < top; ++i) {
            printf(" %d", stack[top-1-i]);
        }
        return 1;
    }
    int x = sum % B;
    while(1) {
        if(A <= x && x < A+B) break;
        x += B;
    }
    for(; x < A+B; x += B) {
        int nsum = (sum - x) / B;
        if(nsum < 0) break;
        stack[top++] = x;
        if( dfs(nsum) ) {
            return 1;
        }
        top--;
    }
    return 0;
}

void solve(int N) {
    top = 0;
    dfs(N);
}

int main() {
    int N;
    int cases = 0;
    while(scanf("%d %d %d", &N, &A, &B) != EOF) {
        printf("Case %d:", ++cases);
        solve(N);
        puts("");
    }
    return 0;
}
