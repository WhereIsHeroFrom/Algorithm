/*
AC自动机 模板 
该模板在具体实现的时候主要修改以下几个地方：
     1、MAXC 的大小，每个题目的字符集总数不一样
     2、MAXQ 的大小，每个题目的结点总数不一样 (字符串数目*字符串长度)
     3、bool isReceiving()接收态的实现。
     4、ACNode结点的cnt和val两个域一般只需要用到其中一个，另外一个可以注释，节省空间。 
     5、构造fail指针时，将fail指针的val状态传递给当前结点的时候，有时候是+，有时候是|，视情况而定。 
*/ 
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define MAXC 26
#define MAXQ 50010

// 结点结构
struct ACNode {
public:
    ACNode *fail;        // fail指针，指向和当前结点的某个后缀匹配的最长前缀的位置
    ACNode *next[MAXC];  // 子结点指针

    // 以下这些数据需要针对不同题目，进行适当的注释，因为可能内存会吃不消

    int id;              // 结点编号(每个结点有一个唯一编号)
    int val;             // 当前结点和它的fail指针指向结点的结尾单词信息的集合
    int cnt;               // 有些题中模式串有可能会有多个单词是相同的，但是计数的时候算多个

    void reset(int _id) {
        id = _id;
        val = 0;
        cnt = 0;
        fail = NULL;
        memset(next, 0, sizeof(next));
    }

    // 状态机中的 接收态 的概念
    // 模式串为不能出现(即病毒串)的时候才有接收态
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
    ACNode* nodes[MAXQ];          // 结点缓存，避免内存重复申请和释放，节省时间
    int nodesMax;                 // 缓冲区大小，永远是递增的 
    ACNode *root;                 // 根结点指针
    int nodeCount;                // 结点总数

    /*数据相关结构*/
    int ID[256], IDSize;          // 结点上字母的简单HASH，使得结点编号在数组中连续
                                  // 例如： ID['a']=0   ID['b']=1 依此类推

    /*队列相关结构*/
    ACNodeQueue Q;

public:
    ACAutoman() {
        nodesMax = 0;
    }
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
        if(nodeCount >= nodesMax) {
            nodes[nodesMax++] = new ACNode();
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
    void insert(char *str, int val) {
        ACNode *p = root;
        int id;
        for(int i = 0; str[i]; i++) {
            // 获取字母对应的哈希ID
            id = getCharID(str[i], true);
            // 检查子结点是否存在，不存在则创建新的子结点
            if(p->next[id] == NULL) p->next[id] = getNode();
            p = p->next[id];
        }
        // 在这个单词的结尾打上一个标记
        p->val |= val;     // 注意有可能有相同的串
        p->cnt ++;
    }

    // 构造失败指针、trie图 
    void construct_trie() {
        ACNode *now, *son, *tmp;
        
        root->fail = NULL;
        Q.clear();
        Q.push(root);
        
        // 逐层计算每一层的结点的fail指针
        // 当每个结点计算完毕，保证它所有后继都已经计算出来 
        while( !Q.empty() ) {
            now = Q.pop();
            
            if(now->fail) {
                // 这里需要视情况而定
                // 目的是将fail指针的状态信息传递给当前结点
                // now->val += now->fail->val;
                //now->val |= now->fail->val;

                // 如果当前结点是个接收态，那么它的所有后继都是回到本身
                if(now->isReceiving()) {
                    for(int i = 0; i < IDSize; i++) {
                        now->next[i] = now;
                    }
                    continue;
                }
            }
            // 首先，我们把当前结点now的i号后继记为son[i]
            //   i) 如果son[i]不存在，将它指向 当前结点now的fail指针指向结点的i号后继(保证一定已经计算出来)。
            //   2) 如果son[i]存在，将它的fail指针指向 当前结点now的fail指针指向结点的i号后继(保证一定已经计算出来)。
            for(int i = 0; i < IDSize; i++) {
                son = now->next[i];
                tmp = (now == root) ? root : now->fail->next[i];
                if(son == NULL) {
                    now->next[i] = tmp;
                }else {
                    son->fail = tmp;
                    Q.push(son);
                }
            }
        }
    }

    // 询问str中有哪些模式串
    int query_str(char *str, int *ans) {
        ACNode *p = root, *tmp = NULL;
        int id;
        int cnt = 0;
        
        for(int i = 0; str[i]; i++) {
            id = getCharID(str[i], false);
            if(id == -1) {
                // 当前单词从来没有出现过，直接回到匹配之初
                p = root;
                continue;
            }
            p = p->next[id];
            tmp = p;
            while(tmp != root && tmp->cnt != -1) {
                if(tmp->cnt) {
                    ans[ tmp->val ] += tmp->cnt; 
                }
                tmp = tmp->fail;
            }
        }
        return cnt;
    }
}AC;

int N;
char str[2000010];
char mot[1010][55];
int ans[1010];

int main() {
    int i;
    while(scanf("%d", &N) != EOF) {
        getchar();
        AC.init();
        for(i = 1; i <= N; i++) {
            gets(mot[i]);
            AC.insert(mot[i], i);
        }
        AC.construct_trie();
        gets(str);
        memset(ans, 0, sizeof(ans));
        AC.query_str(str, ans);
        for(i = 1; i <= N; i++) {
            if(ans[i]) {
                printf("%s: %d\n", mot[i], ans[i]);
            }
        }
    }
    return 0;
}

/*
5
ab gf
.,;;
/.;
...
o0p
1
...,;;ab gf

*/
