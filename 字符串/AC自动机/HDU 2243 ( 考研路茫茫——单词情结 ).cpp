#include <iostream>
#include <vector>
using namespace std;

#define MAXN 100
#define LL unsigned __int64

#define MAXC 26
#define MAXM 500000
#define MAXL 1010

class Node {
public:
    Node *fail;         // fail指针，指向和当前单词后缀匹配的最长前缀的位置 
    Node *next[MAXC];   // 子结点指针 
    int id;             // 结点编号(每个结点都有一个唯一编号)
    int val;            // 单词结尾的权值
    
    void reset(int _id) {
        id = _id;
        val = 0;
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


class Matrix {
public:
    int n, m;
    LL d[MAXN][MAXN];
    Matrix() {
        n = m = 0;
        int i, j;
        for(i = 0; i < MAXN; i++) {
            for(j = 0; j < MAXN; j++) {
                d[i][j] = 0;
            }
        }
    }
    Matrix operator *(const Matrix& other) {
        Matrix ret;
        ret.n = n;
        ret.m = other.m;
        int i, j, k;
        for(j = 0; j < ret.m; j++) {
            for(i = 0; i < ret.n; i++) {
                ret.d[i][j] = 0;
                for(k = 0; k < m; k++) {
                    ret.d[i][j] += d[i][k] * other.d[k][j];
                }
            }
        }
        return ret;
    }
    
    Matrix Identity(int _n) {
        Matrix I;
        I.n = I.m = _n;
        int i, j;
        for(i = 0; i < _n; i++) {
            for(j = 0; j < _n; j++) {
                I.d[i][j] = (i == j) ? 1 : 0;
            }
        }
        return I;
    }
    
    Matrix getPow(int e) {
        Matrix tmp = *this;
        Matrix ret = Identity(n);
        while(e) {
            if(e & 1) {
                ret = ret * tmp;
            }
            e >>= 1;
            tmp = tmp * tmp;
        }
        return ret;
    }

    // | A  A |
    // | O  I |
    // 扩展矩阵用于求A + A^2 + A^3 + ... + A^n
    Matrix getExtendMatrix() {
        Matrix ret;
        ret.n = ret.m = n * 2;
        ret.copyMatrix( *this, 0, 0);
        ret.copyMatrix( *this, 0, n);
        ret.copyMatrix( Identity(n), n, n);
        return ret;
    }

    // 将矩阵A拷贝到当期矩阵的(r, c)位置
    void copyMatrix(Matrix A, int r, int c) {
        for(int i = r; i < r + A.n; i++) {
            for(int j = c; j < c + A.n; j++) {
                d[i][j] = A.d[i-r][j-c];
            }
        }
    }
    
    void Print() {
        int i, j;
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                printf("%d ", d[i][j]);
            }
            puts("");
        }
    }
};

Matrix dfa_matrix_construct() {
    Node *now, *son, *p;
    
    Matrix M;
    M.n = M.m = totNode;
    
    front = rear = 0;
    Q[ rear++ ] = root;
    
    while( front < rear ) {
        now = Q[ front++ ]; 
        
        p = now;
        while(p != NULL) {
            if( p->val == 1 ) {
                now->val = 1;
                M.d[ now->id ][ now->id ] += MAXC;
                break;
            }
            p = p->fail;
        }
        if(p != NULL) continue;
        
        for(int i = 0; i < MAXC; i++) {
            son = now->next[i];
            if( son != NULL ) {
                M.d[ now->id ][ son->id ] ++;
                Q[ rear++ ] = son;
            }else {
                p = now->fail;
                while(p != NULL) {
                    if(p->next[i] != NULL) {
                        M.d[ now->id ][ p->next[i]->id ] ++;
                        break;
                    }
                    p = p->fail;
                }
                if(p == NULL) M.d[ now->id ][ root->id ] ++;
            }
        }
    }
    return M;
}


char str[20];
 
int main() {
    int i, j;
    int n, m;
    while ( scanf("%d %d", &m, &n) != EOF ) {
        init();
        for(i = 0; i < m; i++) {
            scanf("%s", str);
            insert(str, 1);
        }
        bfs_acautomation();
        Matrix M = dfa_matrix_construct();
        M = M.getExtendMatrix();
        //M.Print();
        M = M.getPow(n);
        //M.Print();
        LL ans = 0;
        for(i = M.m/2; i < M.m; i++) {
            if(buffNode[ i-M.m/2 ]->val) {
                ans += M.d[0][i];
            }
        }
        printf("%I64u\n", ans);
    }
    return 0;
}
/*

*/


