#include <iostream>
#include <cstring>

using namespace std;

char str[100];


struct Node {
    int p, l, r;
    int num;
    int sontype;
    // 0:   root   1: leftson   2: rightson

    void addRight(Node& s) {
        r = s.num;
        s.p = num;
        s.sontype = 2;
    }

    void addLeft(Node& s) {
        l = s.num;
        s.p = num;
        s.sontype = 1;
    }
}N[100];

char stk[100];
int tp;

void dfs(int now) {
    if (now == -1) {
        return;
    }

    stk[tp++] = now + '0';

    dfs(N[now].l);
    dfs(N[now].r);

}

int findStr(int p, char *str, char *res) {
    char l[15], r[15];
    int ls = 0, rs = 0;
    int len = strlen(str);

    if (len == 0) {
        return -1;
    }
    int root = str[0] - '0';

    for (int i = 1; i < len; ++i) {
        if (str[i] < str[0]) {
            l[ls++] = str[i];
        }
        else if (str[i] > str[0]){
            r[rs++] = str[i];
        }
    }
    l[ls] = '\0';
    r[rs] = '\0';

    N[root].l = findStr(root, l, res);
    N[root].r = findStr(root, r, res);

    if (p == -1) {
        tp = 0;
        dfs(root);
        strcpy(res, stk);
    }

    return root;
}

char res[100], re[100];

int main() {
    int n;
    while (scanf("%d", &n) != EOF && n) {
        scanf("%s", str);
        findStr(-1, str, res);
        for (int i = 0; i < n; ++i) {
            scanf("%s", str);
            findStr(-1, str, re);
            //printf("->:"); puts(re);
            if (strcmp(res, re) == 0) {
                puts("YES");
            }
            else {
                puts("NO");
            }
        }
    }
    return 0;
}

/*
2
21435
24351
24531

1
12345670
12345670

*/
