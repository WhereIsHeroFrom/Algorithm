#include <iostream>
#include <algorithm>

using namespace std;
int sor[] = {256664, 265664, 266564, 266654, 266663};
int le[100];

int stack[100], top;
int flag = 0;
int n;

void dfs(int depth, int sum) {
    int i;

    if(flag)
        return ;

    if(sum > n)
        return ;

    if(depth == 5) {
        if(sum == n) {
            if(flag ++)
                printf(" ");
            for(i = 0; i < top; i++) {
                printf("%d", stack[i]);
            }
        }
        return ;
    }

    for(i = 0; i <= 9; i++) {
        if(sum + 9 * le[depth] < n)
            return ;

        stack[top++] = i;
        dfs(depth+1, sum + sor[depth] * i);
        top --;
    }

}
int main() {

    int i;
    while(scanf("%d", &n) != EOF) {
        le[4] = 266663;
        for(i = 3; i >= 0; i--) {
            le[i] = le[i+1] + sor[i];
        }
        flag = 0;
        top = 0;
        dfs(0, 0);
        puts("");
    }
}

