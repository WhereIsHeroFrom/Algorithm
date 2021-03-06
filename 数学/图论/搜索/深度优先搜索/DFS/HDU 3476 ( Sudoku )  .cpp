#include <iostream>

using namespace std;

#define SD_CNT 2
#define SD_MAX (SD_CNT*SD_CNT)
#define SD_TOT (SD_MAX*SD_MAX)

// 行是否有1、2、3、4
int hashR[SD_MAX][SD_MAX+1];
// 列是否有1、2、3、4
int hashC[SD_MAX][SD_MAX+1];
// 宫是否有1、2、3、4
int hashRegion[SD_MAX][SD_MAX+1];
int ans[SD_TOT], ansCnt;
int ansTemp[SD_TOT], uniqueAns;
int ansCount;
int stack[SD_TOT];


void DFS(int depth) {

    if(uniqueAns > 1) {
        return;
    }
    if(depth == SD_TOT) {
        ++uniqueAns;
        for(int i = 0; i < SD_TOT; ++i) {
            stack[i] = ansTemp[i];
        }
        return;
    }    
    if(ansTemp[depth]) {
        DFS(depth + 1);
    }else {
        int i;
        int r = depth / SD_MAX;
        int c = depth % SD_MAX;
        int region = (r/SD_CNT)*SD_CNT + c/SD_CNT;
        for(i = 1; i <= SD_MAX; ++i) {
            if(hashR[r][i] || hashC[c][i] || hashRegion[region][i]) 
                continue;
            hashR[r][i] = hashC[c][i] = hashRegion[region][i] = 1;
            ansTemp[depth] = i;
            DFS(depth+1);
            ansTemp[depth] = 0;
            hashR[r][i] = hashC[c][i] = hashRegion[region][i] = 0;
        }
    }
}

void dfs(int depth) {
    int i;
    if (depth == SD_TOT) {

        for(i = 0; i < SD_TOT; ++i) {
            ansTemp[i] = ans[i];
        }
        uniqueAns = 0;
        DFS(0);
        if(uniqueAns == 1) {
            ansCount ++;
            /*printf("(%d)\n", uniqueAns);
            for(i = 0; i < SD_TOT; ++i) {
                printf("%d", ans[i]);
                if(i%4==3) puts("");
            }
            puts("");*/
            printf("%d -> ", ansCount);
        }
        ansCnt ++;
        
        return;
    }
    int r = depth / SD_MAX;
    int c = depth % SD_MAX;
    int region = (r/SD_CNT)*SD_CNT + c/SD_CNT;
    for(i = 0; i <= SD_MAX; i++) {
        if (i == 0) {
            ans[depth] = 0;
            dfs(depth+1);
            continue;
        }
        if(hashR[r][i] || hashC[c][i] || hashRegion[region][i]) 
            continue;
        hashR[r][i] = hashC[c][i] = hashRegion[region][i] = 1;
        ans[depth] = i;
        dfs(depth+1);
        hashR[r][i] = hashC[c][i] = hashRegion[region][i] = 0;
    }
}

int main() {
    printf("%d\n", 13579680);
    //ansCnt = 0;
    //dfs(0);
    //printf("%d %d\n", ansCnt, ansCount);
    // 61556225 13579680
    //while(1);
    return 0;
}
