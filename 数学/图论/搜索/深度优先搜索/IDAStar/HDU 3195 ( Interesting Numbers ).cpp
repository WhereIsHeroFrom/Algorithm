#include <iostream>

using namespace std;

#define LL __int64

int stack[110], top;
char ans[100][110];
int N;

void dfs(int depth, int maxDepth) {
    // 剪枝
    int i, j;
    int carryUp = 0;
    for(i = 0; i < top; ++i) {
        int a = carryUp;
        for(j = 0; j <= i; ++j) {
            a += stack[j] * stack[i-j];
        }
        if(a % 10 != stack[i]) {
            return ;
        }
        carryUp = a / 10;
    }

    // 确定最后答案的时候到啦
    if(depth == maxDepth) {
        // 有前导0的一律不算
        if(!stack[top-1] && maxDepth > 1) {
            return;
        }

        for(i = 0; i < top; ++i) 
            ans[N][i] = stack[top-1-i] + '0';
        ans[N][top] = '\0';
        N++;
        return;
    }
    for(i = 0; i <= 9; ++i) {
        stack[top] = i;
        ++top;
        dfs(depth+1, maxDepth);
        --top;
    }
}

char v[][100] = {
"0",
"1",
"5",
"6",
"25",
"76",
"376",
"625",
"9376",
"90625",
"109376",
"890625",
"2890625",
"7109376",
"12890625",
"87109376",
"212890625",
"787109376",
"1787109376",
"8212890625",
"18212890625",
"81787109376",
"918212890625",
"9918212890625",
"40081787109376",
"59918212890625",
};

int main() {
    int i;
    N = 0;
    for(i = 1; ; ++i) {
        dfs(0, i);
        if(N >= 26) break;
    }
    /*printf("char v[][100] = {\n");
    for(i = 0; i < 26; ++i) {
        printf("\"%s\",\n", ans[i]);
    }
    printf("};");*/
    while(scanf("%d", &N) != EOF) {
        printf("%s\n", v[N-1]);
    }
    return 0;
}
