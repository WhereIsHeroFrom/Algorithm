#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

#define MAXC 2
#define MAXM 200000
#define MAXN 20
#define INF 100000000

class Node {
public:
    Node *fail;         // fail指针，指向和当前单词后缀匹配的最长前缀的位置 
    Node *next[MAXC];   // 子结点指针 
    int id;             // 结点编号(每个结点都有一个唯一编号)
    int end;            // 单词结尾的权值
    int val;            // 它本身和它所有fail指针指向的点的权值的或
    
    void reset(int _id) {
        id = _id;
        val = 0;
        end = 0;
        fail = NULL;
        memset(next, 0, sizeof(next));
    }
    
};

// 自动机指针结构 
vector <Node*> buffNode;     // 结点缓存，避免内存重复申请和释放，节约时间 
int totNode;                 // 结点总数 
Node *root;                  // 根结点指针 

// 结点字母的简单HASH，使得结点编号在数组中连续
int ID[128], sz;

// 构造fail指针的队列结构 
Node *Q[MAXM];
int front, rear;

// 获取缓存结点
Node *getNode() {
    if( totNode >= buffNode.size() ) {
        buffNode.push_back( new Node() );
    }
    Node *p = buffNode[ totNode ];
    p->reset( totNode );
    totNode ++;
    return p;
}

// 字母到编号的映射 
int getID(char c, int needcreate) {
    if(!needcreate) {
        return ID[c];
    }
    if(ID[c] == -1) {
        ID[c] = sz++;
    }
    return ID[c];
}

// 每组数据必须调用的初始化
void init() {
    totNode = 0;
    sz = 0;
    root = getNode();
    memset(ID, -1, sizeof(ID));
}

// 构建字典树(Trie) 
// val 为结束标记，不能为0 
void insert(char *str, int val) {
    Node *p = root;
    int id;
    
    for(int i = 0; str[i]; i++) {
        // 获取hash后的id 
        id = getID(str[i], true);
        // 检查子结点是否存在，如果不存在需要创建新的子结点 
        if(p->next[id] == NULL) {
            p->next[id] = getNode();
        }
        // 指针指向子结点 
        p = p->next[id];
    }
    // 可以理解为str这个字符串的结尾标记 
    p->val = val;
    p->end = val;
}

// 构建fail指针 
void bfs_acautomation() {
    Node *now, *son, *p;
    int i;
    
    // 初始化队列为空 
    front = rear = 0;
    // 根结点的fail指针为空 
    root->fail = NULL;
    // 根结点入队 
    Q[ rear++ ] = root;
    
    while( front < rear ) {
        // 取出一个待处理结点 
        now = Q[ front++ ];
        
        // 枚举它所有的子结点 
        for(i = 0; i < sz; i++) {
            son = now->next[i];
            if(son != NULL) {
                // 如果子结点非空，则为每个子结点 
                if(now == root) {
                    // 待处理结点为根结点，那么子结点的fail指针指向根结点 
                    son->fail = root;
                }else {
                    // 待处理结点非根结点
                    // 沿着待处理结点的fail指针找
                    // 直到找到一个结点p，它的对应字母子结点非空
                    // 标记子结点的fail指针 指向 p的对应字母子结点 
                    p = now->fail;
                    while(p != NULL) {
                        if(p->next[i] != NULL) {
                             son->fail = p->next[i];
                             break;
                        }
                        p = p->fail;
                    }
                    
                    // 如果没有找到匹配的，将子结点的fail指针指向根结点 
                    if(p == NULL) son->fail = root;
                }
                
                // 将子结点入队，继续处理以该子结点为根的子树的fail指针 
                Q[ rear++ ] = son;
            }
        }
    }
}

// 询问 str 中包含哪些模式串 
void query(char *str) {
    Node *p = root, *tmp = NULL;
    int id, i;
    
    
    for(int i = 0; str[i]; i++) {
        // 和str后缀匹配的最长字符 
        id = getID(str[i], false);
        if(id == -1) {
            p = root;
        }else {
            // 沿着失败指针一直找到能够和当前字符串str[0...i]后缀匹配的最长前缀的位置 
            while(p != root) {
                if(p->next[id] != NULL) break;
                p = p->fail;        
            }
            p = p->next[id];
            // 如果一直没有找到，说明没有匹配，直接指向根结点 
            if(p == NULL) p = root;
        }
        
        tmp = p;    
        while(tmp != root) {
            if(tmp->val) {
                // 找到一个子串以tmp结点结尾
                // 这里一般需要做题目要求的操作，不同题目不同
                // 有的是统计子串数目、有的则是输出子串位置 
            }
            tmp = tmp->fail;
        }
    }
}

int n, m;

bool isVirus(int val) {
    return val & (1<<n);
}

void dfa_matrix_construct() {
    Node *now, *son, *p;
    
    front = rear = 0;
    Q[ rear++ ] = root;
    
    while( front < rear ) {
        now = Q[ front++ ]; 
        // 除了根结点，其它结点的fail指针都不为NULL 
        if(now->fail) {
            now->val |= now->fail->val;
            // 一旦当前状态包含一个病毒，那么接下来去的状态都只能到自己
            // 而且其它状态也不应该进来
            if( isVirus(now->val) )  {
                for(int i = 0; i < MAXC; i++) {
                    now->next[i] = now;
                }
                continue;
            }
        }

        for(int i = 0; i < MAXC; i++) {
            son = now->next[i];
            if( son != NULL ) {
                // 子结点不为空，处理子结点 
                Q[ rear++ ] = son;
            }else {
                // 子结点为空，找到一个最长后缀，将子结点指向它 
                p = now->fail;
                while(p != NULL) {
                    if(p->next[i] != NULL) {
                        now->next[i] = p->next[i]; 
                        break;
                    }
                    p = p->fail;
                }
                if(p == NULL) now->next[i] = root; 
            }
        }
    }
}

/*
n <= 10
srclen <= 1000
m <= 1000
viruslen <= 50000
*/

char src[1010];
char virus[50010];

int dist[MAXM];
int d[MAXN][MAXN];
int dp[MAXN][2048];
int pt[MAXN], pcnt;

// 从 根结点 或 resource 结尾点 到 其它点 的 最短路
void getMinDist(int startIdx) {
    memset(dist, -1, sizeof(dist));
    queue <int> QQ;
    QQ.push( pt[startIdx] );
    dist[ pt[startIdx] ] = 0;
    
    Node *nextNode = NULL;

    while( !QQ.empty() ) {
        int nowstate = QQ.front();
        QQ.pop();

        for(int i = 0; i < sz; i++) {
            nextNode = buffNode[nowstate]->next[i];
            // 病毒结点不敢走啊
            if( isVirus(nextNode->val) ) {
                continue;
            }
            // 已经被人捷足先登了
            if(dist[ nextNode->id ] != -1) {
                continue;
            }

            dist[nextNode->id] = dist[nowstate] + 1;
            QQ.push(nextNode->id);
        }
    }
    for(int i = 0; i < pcnt; i++) {
        d[startIdx][i] = dist[ pt[i] ] == -1 ? INF : dist[ pt[i] ];
        //printf("%d %d %d\n", startIdx, i, d[startIdx][i]);
    }
}

class routeInfo {
public:
    int u;
    int dist;
    int state;
    routeInfo() {}

    routeInfo(int _u, int _d, int _s) {
        u = _u;
        dist = _d;
        state = _s;
    }
};

int sovle() {
    int i;
    memset(dp, -1, sizeof(dp));
    int ans = INF;
    // 从 根结点出发，没有任何点的最短路为0
    dp[0][1<<0] = 0;
    queue <routeInfo> QQ;
    QQ.push( routeInfo(0, 0, 1<<0) );
    
    while( !QQ.empty() ) {
        routeInfo ri = QQ.front();
        QQ.pop();

        for(i = 0; i < pcnt; i++) {
            int mask = (1<<i) | ri.state;
            if( d[ri.u][i] == -1 ) {
                continue;
            }
            if(ri.dist + d[ri.u][i] < dp[i][mask] || dp[i][mask] == -1) {
                dp[i][mask] = ri.dist + d[ri.u][i];
                QQ.push( routeInfo(i, dp[i][mask], mask) );
            }
        }
    }
    for(i = 0; i < pcnt; i++) {
        if( dp[i][ (1<<pcnt) - 1 ] < ans && dp[i][ (1<<pcnt) - 1 ] != -1 ) ans = dp[i][ (1<<pcnt) - 1 ];
    }
    return ans;
}

int main() {
    int i;
    while( scanf("%d %d", &n, &m) != EOF ) {
        if(!n && !m) break;
        init();
        for(i = '0'; i <= '1'; i++) getID(i, true);

        for(i = 0; i < n; i++) {
            scanf("%s", src);
            insert(src, (1<<i));
        }
        for(i = 0; i < m; i++) {
            scanf("%s", virus);
            insert(virus, (1<<n));
        }
        bfs_acautomation();
        dfa_matrix_construct();

        pcnt = 0;
        pt[ pcnt++ ] = root->id;

        for(i = 0; i < totNode; i++) {
            // resource 结点
            if(buffNode[i]->end && !isVirus(buffNode[i]->val) ) {
                pt[ pcnt++ ] = i;
            }
        }

        // 任意两个resource结点间的最短路
        for(i = 0; i < pcnt; i++) {
            getMinDist(i);
        }
        printf( "%d\n", sovle() );
    }
}

/*
3 2
11
101
001
1001
1010

3 2
11
101
001
1001
1010

2 2
1110
0111
101
1001

3 4
11
101
001
1001
1010
1101
1011

1 0
111111111

*/


