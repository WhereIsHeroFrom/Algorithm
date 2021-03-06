#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define MAXC 26
#define MAXM 300000
#define MAXN 1000010

class Node {
public:
    Node *fail;
    Node *next[MAXC];
    int cnt;
    
    void reset() {
        fail = NULL;
        cnt = 0;
        for(int i = 0; i < MAXC; i++) next[i] = NULL;
    }
};
int tot;
vector<Node*> buffNode;
Node *q[MAXM];
int front, rear;
Node *root;

void init() {
    tot = 0;
}

Node *getNode() {
    Node *p = NULL;
    if(tot >= buffNode.size()) {
        buffNode.push_back( new Node() ); 
    }
    p = buffNode[ tot++ ];
    p->reset();
    return p;
}

// 字典树 插入
void insert(Node *root, char *str) {
    int i = 0, index;
    Node *p = root;
    while(str[i]) {
        index = str[i] - 'a';
        if (p->next[ index ] == NULL) {
            p->next[ index ] = getNode();
        }
        p = p->next[ index ];
        i++;
    }
    p->cnt ++;
}

// 失败指针构造 
void bfs_acautomation(Node *root) {
    int i;
    Node *now, *son, *p;
    // 根结点失败指针指向NULL 
    root->fail = NULL;
    front = rear = 0;
    // 从根结点开始扩展 
    q[ rear++ ] = root;
    
    while( front < rear ) {
        now = q[ front++ ];
        for(i = 0; i < MAXC; i++) {
            son = now->next[i]; 
            if(son != NULL) {
                if(now == root) {
                    son->fail = root;
                }else {
                    // 循着父结点的失败指针一直找
                    p = now->fail;
                    while(p != NULL) {
                        if(p->next[i] != NULL) {
                            son->fail = p->next[i];
                            break; 
                        }
                        p = p->fail;
                    }
                    if(p == NULL) {
                        son->fail = root;
                    }
                }
                q[ rear++ ] = now->next[i];
            }
        }
    }
}

int query(Node *root, char *str) {
    int i = 0;
    int cnt = 0;
    Node *p = root, *tmp = NULL;
    
    while( str[i] ) {
        int index = (str[i] - 'a');
        // 找到一个能够和 p->next[index] 匹配的串 
        while( p != root && p->next[index] == NULL ) p = p->fail;
        // 匹配到子结点 
        p = p->next[index];
        // 如果没有匹配，返回根结点 
        if(p == NULL) p = root;
        
        // 可能有多个串与之匹配 
        tmp = p;
        while (tmp != root && tmp->cnt != -1) {
            cnt += tmp->cnt;
            tmp->cnt = -1;
            tmp = tmp->fail;
        } 
        i++;
    }
    return cnt;
}

char str[MAXN];

int main() {
    int t, n;
    int i;
    
    scanf("%d", &t);
    while( t-- ) {
        init();
        root = getNode();
        scanf("%d", &n);
        for(i = 0; i < n; i++) {
            scanf("%s", str);
            insert(root, str);
        }
        bfs_acautomation(root);
        scanf("%s", str);
        printf("%d\n", query(root, str) );
        
    }
    return 0;
}
/*
7
she
she
sh
he
say
shr
her
yasherhs
*/

