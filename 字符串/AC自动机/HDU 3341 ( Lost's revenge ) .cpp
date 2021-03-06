#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAXL 50
#define INF 100000000
#define MAXP 15000
#define MAXC 4
#define MAXQ 400000

// 结点结构
struct ACNode {
public:
    ACNode *fail;        // fail指针，指向和当前结点的某个后缀匹配的最长前缀的位置
    ACNode *next[MAXC];  // 子结点指针

    // 以下这些数据需要针对不同题目，进行适当的注释，因为可能内存会吃不消

    int id;              // 结点编号(每个结点有一个唯一编号)
    //int end;             // 模式串中以当前结点单词结尾的权值(0表示非结尾单词)
    int val;             // 当前结点和它的fail指针指向结点的结尾单词信息的集合
    //int cnt;             // 有些题中模式串有可能会有多个单词是相同的，但是计数的时候算多个

    void reset(int _id) {
        id = _id;
        val = 0;
        //end = 0;
        //cnt = 0;
        fail = NULL;
        memset(next, 0, sizeof(next));
    }

    // 状态机中的 接收态 的概念
    bool isReceiving() {
        return false;
    }
};

// 结点队列结构
// STL的效率不敢恭维，在某些OJ上效率极低，自己封装一套比较好
class ACNodeQueue {
public:
    ACNode *Data[MAXQ];
    int front, rear;

    bool empty() {
        return front == rear;
    }
    void clear() {
        front = rear = 0;
    }
    ACNode *pop() {
        ACNode *p = Data[front++];
        if(front == MAXQ) front = 0;
        return p;
    }
    void push(ACNode *node) {
        Data[rear++] = node;
        if(rear == MAXQ) rear = 0;
    }
};

// 艾斯奥特曼！！！北斗星司 <-> 南夕子
class ACAutoman {
public:
    /*结点相关结构*/
    vector <ACNode*> nodes;       // 结点缓存，避免内存重复申请和释放，节省时间
    ACNode *root;                 // 根结点指针
    int nodeCount;                // 结点总数

    /*数据相关结构*/
    int ID[256], IDSize;          // 结点上字母的简单HASH，使得结点编号在数组中连续
                                  // 例如： ID['a']=0   ID['b']=1 依此类推

    /*队列相关结构*/
    ACNodeQueue Q;

public:
    // 初始化！！！ 必须调用
    void init() {
        nodeCount = 0;
        IDSize = 0;
        root = getNode();
        memset(ID, -1, sizeof(ID));
    }


    // 获取结点
    ACNode *getNode() {
        // 内存池已满，需要申请新的结点
        if(nodeCount >= nodes.size()) {
            nodes.push_back( new ACNode() );
        }
        ACNode *p = nodes[nodeCount];
        p->reset(nodeCount++);
        return p;
    }

    // 获取字母对应的ID
    int getCharID(unsigned char c, int needcreate) {
        if(!needcreate) return ID[c];
        if(ID[c] == -1) ID[c] = IDSize++;
        return ID[c];
    }

    // 对每个模式串str进行insert操作，构造字典树
    // end 为结束标记
    void insert(char *str, int val) {
        ACNode *p = root;
        int id;
        for(int i = 0; str[i]; i++) {
            // 获取字母对应的哈希ID
            id = getCharID(str[i], true);
            // 检查子结点是否存在，不存在则创建新的子结点
            if(p->next[id] == NULL) {
                p->next[id] = getNode();
            }
            p = p->next[id];
        }
        // 在这个单词的结尾打上一个标记
        //p->end = val;
        p->val ++;     // 注意有可能有相同的串
        //p->cnt ++;
    }

    // 构造失败指针
    void construct_fail() {
        ACNode *now, *son, *tmp;
        
        root->fail = NULL;
        Q.clear();
        Q.push(root);
        
        while( !Q.empty() ) {
            now = Q.pop();
            for(int i = 0; i < IDSize; i++) {
                son = now->next[i];
                if(son != NULL) {
                    // 为了阐述方便，我们将now的i号子结点即为son[i]
                    // 如果son[i]非空，那么需要构造son[i]的fail指针
                    // 具体步骤如下：
                    // 利用now的fail指针，now的fail指针的fail指针... 一直找
                    // 直到找到一个结点，它的i子结点非空，那么将son[i]的fail指针指向它的i子结点
                    tmp = now->fail;                
                    while(tmp != NULL) {
                        if(tmp->next[i] != NULL) {
                            son->fail = tmp->next[i];
                            break;
                        }
                        tmp = tmp->fail;
                    }
                    // 找不到，则将i子结点的fail指针指向根结点
                    if(tmp == NULL) {
                        son->fail = root;
                    }
                    Q.push(son);
                }
            }
        }
    }

    // 构造trie图(DFA)
    // 多模式串匹配不需要构造状态机
    void construct_trie() {
        ACNode *now, *son, *tmp;

        Q.clear();
        Q.push(root);

        while( !Q.empty() ) {
            now = Q.pop();

            if(now->fail) {
                // 这里需要视情况而定
                // 目的是将fail指针的状态信息传递给当前结点
                // now->val += now->fail->val;
                now->val += now->fail->val;

                // 如果当前结点是个接收态，那么它的所有结点的去向都是回到本身
                if(now->isReceiving()) {
                    for(int i = 0; i < IDSize; i++) {
                        now->next[i] = now;
                    }
                    continue;
                }
            }

            for(int i = 0; i < IDSize; i++) {
                son = now->next[i];
                if(son == NULL) {
                    tmp = now->fail;
                    while(tmp != NULL) {
                        if(tmp->next[i]) {
                            now->next[i] = tmp->next[i];
                            break;
                        }
                        tmp = tmp->fail;
                    }
                    if(tmp == NULL) {
                        now->next[i] = root;
                    }
                }else {
                    Q.push(son);
                }
            }
        }

    }

    // 询问str中有哪些模式串
    int query_str(char *str) {
        ACNode *p = root, *tmp = NULL;
        int id;

        for(int i = 0; str[i]; i++) {
            id = getCharID(str[i], false);
            if(id == -1) {
                // 当前单词从来没有出现过，直接回到匹配之初
                p = root;
                continue;
            }
            // 沿着失败指针一直找到能够和当前字符串str[0...i]后缀匹配的最长前缀的位置 
            while(p != root) {
                if(p->next[id]) {
                    break;
                }
                p = p->fail;
            }
            p = p->next[id];

            // 这种情况，表示一直都没有匹配到，直接指向根结点 
            if(p == NULL) p = root;

            tmp = p;
            while(tmp != root) {
                //if(tmp->cnt > 0) {
                    // 找到一个子串以tmp结点结尾
                    // 这里一般需要做题目要求的操作，不同题目不同
                    // 有的是统计子串数目、有的则是输出子串位置             
                //}
                tmp = tmp->fail;
            }
        }
        return 0;
    }
}AC;

int cases = 1;
short dp[510][MAXP];
short has[510][MAXP];

char ACGT[] = "ACGT";
char str[MAXL];
int maxCount[10];
int Base[10];
int n;
int ans = 0;

unsigned int packState(int mat[]) {
    unsigned int s = 0;
    for(int i = 0; i < 4; i++) {
        s += mat[i] * Base[i];
    }
    return s;
}

int getStateVal(int state, int idx) {
    return state % Base[idx + 1] / Base[idx];
}


int mat[5];

int main() {
    int i, j, k;

    while( scanf("%d", &n) != EOF && n ) {
        AC.init();
        
        for(i = 0; ACGT[i]; i++) {
            maxCount[ AC.getCharID( ACGT[i], true) ] = 0;
        }
        
        for(i = 0; i < n; i++) {
            scanf("%s", str);
            /*for(j = 0; j < 10; j++) {
                str[j] = ACGT[rand()%4];
            }
            str[j] = 0;
            puts(str);*/
            AC.insert(str, 1);
        }
        scanf("%s", str);
        /*for(j = 0; j < 40; j++) str[j] = ACGT[rand()%4];
        str[j] = 0;
        puts(str);*/
        for(i = 0; str[i]; i++) {
            maxCount[ AC.getCharID(str[i], true) ] ++;
        }
        for(i = 0; i <= 4; i++) {
            if(i == 0) {
                Base[i] = 1;
            }else {
                Base[i] = Base[i-1] * (maxCount[i-1] + 1);
            }
        }

        ans = 0;
        AC.construct_fail();
        AC.construct_trie();
        //memset(dp, -1, sizeof(dp));
        int state = Base[4];
        dp[0][0] = 0;
        has[0][0] = cases;
        
        for(i = 0; i <= state; i++) {
            for(k = 0; k < 4; k++) {
                mat[k] = getStateVal(i, k);
                if(mat[k] > maxCount[k]) break;
            }
            if(k < 4) continue;            
            
            for(j = 0; j < AC.nodeCount; j++) {
                if(has[j][i] != cases) continue;
                
                if(dp[j][i] > ans) {
                    ans = dp[j][i];
                }
                
                ACNode *p = AC.nodes[j];
                for(k = 0; k < 4; k++) {
                    if(mat[k] == maxCount[k]) continue;
                    int nextstate = p->next[k]->id;
                    int nv = dp[j][i] + p->next[k]->val;
                    if(has[nextstate][i + Base[k]] != cases || nv > dp[nextstate][i + Base[k]]) {
                        has[nextstate][i + Base[k]] = cases;
                        dp[nextstate][i + Base[k]] = nv;
                    }
                }
            }
        }

        printf("Case %d: %d\n", cases++, ans);
    }
    return 0;
}
/*
3
AC
CG
GT
CGAT
1
AA
AAA

10
A
AA
AAA
AAAA
AAAAA
AAAAAA
AAAAAAA
AAAAAAAA
AAAAAAAAA
AAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

50
A A A A A A A A A A
A A A A A A A A A A
A A A A A A A A A A
A A A A A A A A A A
A A A A A A A A A A
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

3
ACG
CG
G
AAACCCGGGTTT
*/


