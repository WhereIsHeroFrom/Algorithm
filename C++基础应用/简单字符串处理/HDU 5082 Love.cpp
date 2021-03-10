#include <iostream>
#include <cstring>
using namespace std;

char a[2][110];
char r[2][110];
int rsize[2];

int main() {
    while (scanf("%s %s", a[0], a[1]) != EOF) {
        rsize[0] = rsize[1] = 0;
        for (int i = 0; i < 2; ++i) {
            int len = strlen(a[i]);
            int c = 0;
            for (int j = 0; j <= len; ++j) {
                if (a[i][j] == '_' || a[i][j] == '\0') {
                    ++c;
                }
                else {
                    if (i == 0 && c == 1) {
                        r[0][rsize[0]++] = a[i][j];
                    }
                    else if (i == 1 && c == 1) {
                        r[1][rsize[1]++] = a[i][j];
                    }
                }
            }

        }
        r[0][rsize[0]] = '\0';
        r[1][rsize[1]] = '\0';
        printf("%s_small_%s\n", r[0], r[1]);
    }

    return 0;
}