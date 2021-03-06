#include <iostream>

using namespace std;

#define MAXN 1010

char str[MAXN];
int c;
int hashv[MAXN];

int main() {
    int i, j, k;
    while(scanf("%s %d", str, &c) != EOF) {
        memset(hashv, 0, sizeof(hashv));
        int start = 0;
        int end = -1;
        while(str[start] != '\0') {
            int cnt = 0;
            for(i = start; str[i] != '0' && str[i]; i++) {
                ++cnt;
            }
            if(cnt > c) {
                end = i;
                break;
            }else {
                c -= cnt;
                for(i = start; str[i] != '0' && str[i]; ++i) {
                    hashv[i] = 1;
                }
                while(str[i] == '0') {
                    hashv[i] = 1;
                    ++i;
                }
                start = i;
            }
        }
        //  1.a 全是0的情况，直接输出0
        if(str[start] == '\0') {
            printf("0\n");
            continue;
        }

        for(i = 0; i < c; ++i) {
            int maxIdx = -1;
            for(j = start; j < end; ++j) {
                if(hashv[j]) continue;
                int flag = 0;
                for(k = j+1; k < end; ++k) {
                    if(hashv[k]) continue;
                    if(str[j] > str[k]) {
                        flag = 1;
                    }
                    break;
                }
                if(k == end || flag) {
                    maxIdx = j;
                    break;
                }
            }
            if(maxIdx == -1) {
                break;
            }
            hashv[maxIdx] = 1;
        }
        for(i = 0; str[i]; ++i) {
            if(hashv[i]) continue;
            if(str[i] != '0') break;
        }

        if(str[i] == '\0') {
            printf("0\n");
        }else {
            for(; str[i]; ++i) {
                if(hashv[i]) continue;
                printf("%c", str[i]);
            }
            puts("");
        }
    }
    return 0;
}
/*
11100101023456 0
11100101023456 1
11100101023456 2
11100101023456 3
11100101023456 4
11100101023456 5
11100101023456 5
11100101023456 6
11100101023456 7
11100101023456 8
11100101023456 9
11100101023456 10
11100101023456 11
11100101023456 12
11100101023456 13
11100101023456 14

00032100123056017 0
00032100123056017 1
00032100123056017 2
00032100123056017 3
00032100123056017 4
00032100123056017 5
00032100123056017 6
00032100123056017 7
00032100123056017 8
00032100123056017 9
00032100123056017 10
00032100123056017 11
00032100123056017 12
00032100123056017 13
00032100123056017 14
00032100123056017 15
00032100123056017 16
00032100123056017 17

0004323400012300000 0
0004323400012300000 1
0004323400012300000 2
0004323400012300000 3
0004323400012300000 4
0004323400012300000 5
0004323400012300000 6
0004323400012300000 7
0004323400012300000 8
0004323400012300000 9
0004323400012300000 10
0004323400012300000 11
0004323400012300000 12
*/
