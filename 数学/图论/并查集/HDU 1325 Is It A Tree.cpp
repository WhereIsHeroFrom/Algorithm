/*
并查集 : 判有向树

考虑空树也是树
非空树，入度为0的点只允许有1个
*/

#include <iostream>

using namespace std;


const int MAXN = 1000010;
int fset[MAXN], has[MAXN], deg[MAXN];
bool bWrong = false;
int vertexCnt, edgeCnt;
int sampleVertex;

void init_set(int n) {
    for (int i = 1; i <= n; ++i) {
        fset[i] = i;
        has[i] = 0;
        deg[i] = 0;
    }
    bWrong = false;
    vertexCnt = edgeCnt = 0;
}

int find_set(int x) {
    return (fset[x] == x) ? x : (fset[x] = find_set(fset[x]));
}

bool union_set(int x, int y) {
    int fx = find_set(x);
    int fy = find_set(y);
    if (fx != fy) {
        fset[fy] = fx;
        return true;
    }
    return false;
}



int main() {
    int x, y;
    int cas = 0;
    int n = MAXN - 1;
    init_set(n);
    while (scanf("%d %d", &x, &y) != EOF) {
        if (x < 0 && y < 0) break;
        if (!x && !y) {
            if (!bWrong) {

                if (vertexCnt){
                    // 点数 - 1 != 边数
                    if (vertexCnt - 1 != edgeCnt) {
                        bWrong = true;
                    }
                    int c = 0;
                    // 非连通图
                    for (int i = 1; i <= n; ++i) {
                        if (!has[i]) continue;
                        if (find_set(sampleVertex) != find_set(i)) {
                            bWrong = true;
                            break;
                        }
                        if (!deg[i]) ++c;
                    }
                    if (c != 1) bWrong = true;
                }
                else{
                    // 空树 也是树
                }
            }
            if (bWrong) {
                printf("Case %d is not a tree.", ++cas);
            }
            else {
                printf("Case %d is a tree.", ++cas);
            }
            puts("");

            init_set(n);
        }
        else {
            if (bWrong) {
                continue;
            }
            if (!has[x]) {
                sampleVertex = x;
                has[x] = 1;
                ++vertexCnt;
            }
            if (!has[y]) {
                sampleVertex = y;
                has[y] = 1;
                ++vertexCnt;
            }

            ++edgeCnt;
            ++deg[y];

            if (!union_set(x, y)) {
                bWrong = true;
            }
        }
    }

    return 0;
}