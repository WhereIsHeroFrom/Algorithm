#include <iostream>

using namespace std;

#define MAXM 40010

int N, A, B, M;
int Median;
int hashv[MAXM], X[MAXM];
int cyclicStart, cyclicEnd, cyclicLen;

int countNumber(int v) {
    // X[0] 比较特殊，有坑，可能 >= M，所以单独算
    int cnt = X[0] == v ? 1 : 0;
    // 没有出现过
    if(!hashv[v]) {
        return cnt;
    }

    // 如果这个数字小于循环开始的位置
    if(hashv[v] < cyclicStart) {
        // 首先满足这个数是第N个数内的
        int addCnt = (hashv[v] <= N) ? 1 : 0;
        return cnt + addCnt;
    }else {
        if(N < cyclicStart) {
            return cnt;
        }
        int tot = (N - cyclicStart);
        int pos = hashv[v] - cyclicStart;
        return cnt + tot/cyclicLen + (pos <= (tot%cyclicLen) ? 1 : 0);
    }
}

int main() {
    int i;
    while( scanf("%d %d %d %d %d", &N, &A, &X[0], &B, &M) != EOF ) {
        Median = (N/2+1);
        --N;
        memset(hashv, 0, sizeof(hashv));
        for(i = 1; ; ++i) {
            X[i] = (X[i-1] * A + B) % M;
            if(hashv[X[i]]) {
                break;
            }
            hashv[X[i]] = i;
        }
        cyclicStart = hashv[X[i]];
        cyclicEnd = i-1;
        cyclicLen = cyclicEnd - cyclicStart + 1;

        //printf("cyclicStart=%d, cyclicEnd=%d\n", cyclicStart, cyclicEnd);
        //printf("X[] = ");
        //for(i = 0; i <= cyclicEnd + 1; ++i) {
        //    printf("%d ", X[i]);
        //}
        //puts("");


        for(i = 0; i < 40000; ++i) {
            int c = countNumber(i);
            //if(c)
            //    printf("countNumber(%d) = %d\n", i, c);
            Median -= c;
            if(Median <= 0) {
                break;
            }
        }
        printf("%d\n", i);
    }
    return 0;
}

/*
90 73 5 97 43
*/
