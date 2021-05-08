#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;
#pragma warning(disable : 4996)

char l[100], r[100];
char op[20];

void getv(char* c, vector<string>& ans) {
    char ctmp[101];
    int s = 0;
    for (int i = 1; c[i]; ++i) {
        if (c[i] == ',' || c[i] == ']') {
            if (s == 0) continue;
            ctmp[s] = '\0';
            s = 0;
            ans.push_back(ctmp);
        }
        else {
            ctmp[s++] = c[i];
        }
    }
}

vector<string> a, b;
int has[110];

void outs(vector<string>& ans) {
    printf("[");
    for (int i = 0; i < ans.size(); ++i) {
        if (i) printf(",");
        printf("%s", ans[i].c_str());
    }
    puts("]");
}

int main() {
    while (scanf("%s", l) != EOF) {
        if (l[0] == '.') {
            break;
        }
        scanf("%s", op);
        scanf("%s", r);
        a.clear();
        b.clear();

        getv(l, a);
        getv(r, b);

        if (op[0] == '+') {
            for (int i = 0; i < b.size(); ++i) {
                a.push_back(b[i]);
            }
            outs(a);
        }
        else {
            memset(has, 0, sizeof(has));
            for (int i = 0; i < b.size(); ++i) {

                for (int j = 0; j < a.size(); ++j) {

                    if (!has[j]) {
                        if (b[i] == a[j]) {
                            has[j] = 1;
                            break;
                        }
                    }
                }
            }
            b.clear();
            for (int i = 0; i < a.size(); ++i) {
                if (!has[i]) {
                    b.push_back(a[i]);
                }
            }
            outs(b);
        }

    }
    return 0;
}
