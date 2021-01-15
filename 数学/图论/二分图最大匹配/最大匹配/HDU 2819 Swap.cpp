/*
二分图左边代表行，右边代表列
*/
#include <iostream>

using namespace std;

int map[110][110];
int n;
int visit[110], pre[110], to[110];

struct point {
    char c;
    int a, b;
}p[1000];
int top;

int dfs(int key) {
    int i;
    for (i = 0; i < n; i++) {
        if (!visit[i] && map[key][i]) {
            visit[i] = 1;
            int k = pre[i];
            pre[i] = key;
            if (k == -1 || dfs(k))
                return 1;
            pre[i] = k;
        }
    }
    return 0;
}


int main() {
    int i, j;
    while (scanf("%d", &n) != EOF) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                scanf("%d", &map[i][j]);
            }
        }
        int Max = 0;
        memset(pre, -1, sizeof(pre));
        for (i = 0; i < n; i++) {
            memset(visit, 0, sizeof(visit));
            if (!dfs(i))
                break;
            Max++;
        }
        if (Max < n) {
            printf("-1\n");
        }
        else {
            for (i = 0; i < n; i++) {
                to[pre[i]] = i;
            }
            top = 0;
            for (i = 0; i < n; i++) {
                if (to[i] == i) {
                    continue;
                }
                p[top].c = 'C';
                p[top].a = to[i];
                p[top].b = i;
                top++;
                to[pre[i]] = to[i];
                pre[to[i]] = pre[i];
            }
            printf("%d\n", top);
            for (i = 0; i < top; i++) {
                printf("%c %d %d\n", p[i].c, p[i].a + 1, p[i].b + 1);
            }
        }
    }
    return 0;
}

/*
4
0 0 1 0
0 0 0 1
0 1 0 0
1 0 0 0
*/