#include <iostream>
#include <queue>
using namespace std;

#define MAXN 200000
#define MAXM 200010
int pre[MAXN], h[MAXN], val[MAXN];
int head[MAXN], tot;
int determined[MAXN];
bool conflict;
int factCnt;

class Edge {
public:
    int u, v, next;

    Edge() {
    }
    Edge(int _u, int _v, int _n) {
        u = _u;
        v = _v;
        next = _n;
    }
}edges[ MAXM ];

int n;

void init() {
    factCnt = 0;
    conflict = false;
    tot = 0;
    for(int i = 0; i < n; i++) {
        pre[i] = i;
        h[i] = 0;
        val[i] = 0;
        determined[i] = -1;
        head[i] = -1;
    }
}

void addEdge(int u, int v) {
    edges[tot] = Edge(u, v, head[u]);
    head[u] = tot++;
}

int unionset_find(int p) {
    while(pre[p] != p) {
        p = pre[p];
    }
    return p;
}

// 从子结点一直到根结点的异或值
int getRealToRootVal(int p) {
    int sum = 0;
    while(pre[p] != p) {
        sum ^= val[p];
        p = pre[p];
    }
    return sum;
}

int unionset_union(int x, int y, int nowval) {
    int fx = unionset_find(x);
    int fy = unionset_find(y);
    if(fx == fy) {
        return false;
    }else {
        addEdge(fx, fy);
        addEdge(fy, fx);

        if( h[fx] == h[fy] ) {
            pre[fy] = fx;
            val[fy] = nowval;
            h[fx]++;
        }else if( h[fx] < h[fy] ) {
            pre[fx] = fy;
            val[fx] = nowval;
        }else {
            pre[fy] = fx;
            val[fy] = nowval;
        }

        /*printf("UNION result:\n");
        printf("%d = (pre = %d val = %d)\n", fx, pre[fx], val[fx]);
        printf("%d = (pre = %d val = %d)\n", fy, pre[fy], val[fy]);*/

        return true;
    }
}

char str[10000];
char kind[10];
int num[20], used[20];

bool isOneValConflict(int v, int nowval) {
    if(determined[v] != -1 && determined[v] != nowval) {
        return true;
    }
    return false;
}

void doConflict() {
    printf("The first %d facts are conflicting.\n", factCnt);
    conflict = true;    
}

void doBFS(int v, int nowval) {
    // 因为同一个集合的数情况要么都知道，要么都不知道
    // 所以，如果第v个数(即 Xv)已经知道，他们它所在集合必定都已经知道了。
    if (determined[v] != -1) {
        return ;
    }
    queue <int> Q;
    Q.push(v);

    determined[v] = nowval;

    while( !Q.empty() ) {
        int u = Q.front();
        Q.pop();


        for(int i = head[u]; i != -1; i = edges[i].next) {
             int v = edges[i].v;
             if( determined[v] == -1 ) {
                 if(pre[u] == v) {
                    determined[v] = determined[u] ^ val[u];
                 }else {
                     determined[v] = determined[u] ^ val[v];
                 }
                 Q.push(v);
             } 
        }
    }
    /*printf("BFS result:\n");
    for(int i = 0; i < n; i++) {
        printf("%d ", determined[i]);
    }
    puts("");*/
}

// 两个数的情况讨论
void joinTwoValue(int v1, int v2, int nowval) {
    if(determined[v1] == -1 && determined[v2] == -1) {
        // 1、两个数都未确定，找到两个数分别所在的集合:
        //         a) 如果在同一个集合,那么他们的异或和一定的等于 集合里 两个数各自相对于根结点的异或和 的 异或和。 
        //         b) 如果不在同一个集合，那么 合并v1和v2所在集合，更新相对于根结点的异或值
        int tmpsum = getRealToRootVal(v1) ^ getRealToRootVal(v2);

        if( unionset_find(v1) == unionset_find(v2) ) {
            if(tmpsum != nowval) {
                doConflict();
                return;
            }
        }
        unionset_union(v1, v2, nowval ^ tmpsum );
    }else if(determined[v1] == -1) {
        // 2、v1未确定，v2确定，根据v2和给定异或和，求出v1的值，然后对所有和v1在同一个集合的数求出对应的数
        int v = nowval ^ determined[v2];
        doBFS(v1, v); 
    }else if(determined[v2] == -1) {
        // 3、同 2)
        int v = nowval ^ determined[v1];
        doBFS(v2, v);
    }else {
        // 两个值都已知道，但是他们异或值不等于给定值
        if( (determined[v1] ^ determined[v2]) != nowval) {
            doConflict();
        }
    }
}

int tmp_pre[20], tmp_val[20];

int findVal(int sum, int cnt) {
    if(cnt == 0) {
        return sum;
    }

    for(int i = 1; i <= num[0]; i++) {
        if(used[i]) continue;

        for(int j = i+1; j <= num[0]; j++) {
            if(used[j]) continue;

            if(tmp_pre[i] == tmp_pre[j]) {
                used[i] = used[j] = 1;
                return findVal(sum ^ tmp_val[i] ^ tmp_val[j], cnt - 2);
            }
        }
    }
    return -1;
}

int main() {
    int Q;
    int i, j;
    int cases = 1;
    
    while( scanf("%d %d", &n, &Q) != EOF ) {
        if( !n && !Q ) break;

        init();
        
        printf("Case %d:\n", cases++);
        while(Q--) {
            scanf("%s", kind);
            getchar();

            
                
                if(kind[0] == 'I') {
                    gets(str);
                    factCnt ++;

                    num[0] = sscanf(str, "%d%d%d", &num[1], &num[2], &num[3]);
                    if(conflict) continue;
                    if(num[0] == 2) {
                        // 一个数的情况 p[ num[1] ] = num[2];
                        // 如果不和之前的情况冲突，那么对所有和它有边相连的点进行扩展                                                                                                                                                                         
                        if( isOneValConflict(num[1], num[2]) ) {
                            doConflict();
                            continue;
                        }
                        doBFS(num[1], num[2]);
                    }else {
                        joinTwoValue(num[1], num[2], num[3]);
                    }
                }else if(kind[0] == 'Q') {
                    
                    scanf("%d", &num[0]);
                    for(i = 1; i <= num[0]; i++) {
                        scanf("%d", &num[i]);
                    }
                    if(conflict) continue;
                    int sum = 0;
                    int cnt = num[0];
                    memset(used, 0, sizeof(used));

                    for(i = 1; i <= num[0]; i++) {
                        int v = num[i];
                        if(determined[v] != -1) {
                            sum ^= determined[v];
                            cnt --;
                            used[i] = 1;
                        }
                        tmp_pre[i] = unionset_find(v);
                        tmp_val[i] = getRealToRootVal(v);
                    }

                    int lastVal = findVal(sum, cnt);
                    if(lastVal == -1) {
                        printf("I don't know.\n");
                    }else {
                        printf("%d\n", lastVal);
                    }
                }
            
        }

        puts("");

    }
    return 0;
}
