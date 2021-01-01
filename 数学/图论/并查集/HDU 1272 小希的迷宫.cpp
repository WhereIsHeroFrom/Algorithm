/*
    并查集 : 判树
    
    * 1）连接的两个结点在同一个集合中，则必然存在环，不是树了
    * 2）否则，树需要满足 点数 - 1 == 边数 且为 连通图
    * 3）特别的，空树也是树

*/
#include <iostream>

using namespace std;


const int MAXN = 100010;
int fset[MAXN], has[MAXN];
bool bWrong = false;
int vertexCnt, edgeCnt;
int sampleVertex;

void init_set(int n) {
    for (int i = 1; i <= n; ++i) {
        fset[i] = i;
        has[i] = 0;
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
        fset[fx] = fy;
        return true;
    }
    return false;
}



int main() {
    int x, y;
    int n = 100000;
    init_set(n);
    while (scanf("%d %d", &x, &y) != EOF) {
        if (x == -1 && y == -1) break;
        if (!x && !y) {
            if (!bWrong) {
               
                if (vertexCnt){
                    // 点数 - 1 != 边数
                    if (vertexCnt - 1 != edgeCnt) {
                        bWrong = true;
                    }
                    // 非连通图
                    for (int i = 1; i <= n; ++i) {
                        if (!has[i]) continue;
                        if (find_set(sampleVertex) != find_set(i)) {
                            bWrong = true;
                            break;
                        }
                    }
                }
                else{
                    // 空树 也是树
                }
            }

            printf("%s\n", bWrong ? "No": "Yes");
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

            if (!union_set(x, y)) {
                bWrong = true;
            }
        }
    }

    return 0;
}