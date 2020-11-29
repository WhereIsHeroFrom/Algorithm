#include <iostream>

#define MAXN 40010
#define MAXE 100010

class Edge {
public:
    int toVertex;
    Edge* next;

    Edge() {}
    void reset(int _to, Edge* _next) {
        toVertex = _to;
        next = _next;
    }
};
typedef Edge* EdgePtr;

class Graph {
    EdgePtr *head;
    Edge *edges;
    int edgeCount;
    int vertexCount;

    bool *visited;
    int *inDeg, *outDeg;

    void doPostOrderTraversal(int u);
    void doPreOrderTraversal(int u);
public:
    int *order, orderCount;
    int *sccID, sccCount;

    Graph() {
        // 链式前向星 存储
        // 邻接表首结点
        head = new EdgePtr[MAXN];
        // 边内存池
        edges = new Edge[MAXE];
        // 遍历时，记录顶点是否被访问
        visited = new bool[MAXN];
        // 后序遍历记录的访问顺序
        order = new int[MAXN];
        // 强连通编号映射
        sccID = new int[MAXN];
        // 入度 + 出度
        inDeg = new int[MAXN];
        outDeg = new int[MAXN];
    }

    ~Graph() {
        delete [] edges;
        delete [] head;
         delete [] visited;
        delete [] order;
        delete [] sccID;
    }

    void init(int vCount);
    void addEdge(int from, int to);
    Edge* getHead(int vertex);

    ////////后序遍历 - 记录时间戳//////////
    void postOrderTraversal();
    ////////前序遍历 - 记录强连通//////////
    void preOrderTraversal(int *order, int orderCount);
    //////// 缩图 //////////
    void doShrink(Graph* orgGraph);
    
    //////// 获取 max(入度=0的点个数,出度=0的点个数) //////////
    int getInDegOutDegMax();
};

void Graph::init(int vCount) {
    vertexCount = vCount;
    edgeCount = 0;
    orderCount = 0;
    sccCount = 0;
    for(int i = 0; i < vCount; i++) {
        head[i] = NULL;
        visited[i] = 0;
        inDeg[i] = outDeg[i] = 0;
    }
}

void Graph::addEdge(int from, int to) {
    edges[edgeCount].reset(to, head[from]);
    head[from] = &edges[edgeCount++];
    ++ inDeg[to];
    ++ outDeg[from];
}

Edge* Graph::getHead(int vertex) {
    return head[vertex];
}

void Graph::doPostOrderTraversal(int u) {
    if(visited[u]) {
        return;
    }
    visited[u] = 1;
    for(Edge *e = head[u]; e; e = e->next) {
        doPostOrderTraversal(e->toVertex);
    }
    order[orderCount++] = u;
}

void Graph::postOrderTraversal() {
    for(int i = 0; i < vertexCount; ++i) {
        doPostOrderTraversal(i);
    }
}

void Graph::doPreOrderTraversal(int u) {
    if(visited[u]) {
        return;
    }
    visited[u] = 1;
    sccID[u] = sccCount;
    for(Edge *e = head[u]; e; e = e->next) {
        doPreOrderTraversal(e->toVertex);
    }
}

void Graph::preOrderTraversal(int *order, int orderCount) {
    for(int i = orderCount-1; i >= 0; --i) {
        int u = order[i];
        if(visited[u]) {
            continue;
        }
        doPreOrderTraversal(u);
        ++ sccCount;
    }
}

void Graph::doShrink(Graph* orgGraph) {
    int vCount = orgGraph->sccCount;
    init(vCount);
    for(int i = 0; i < orgGraph->vertexCount; i++) {
        int from = orgGraph->sccID[i];
        for(Edge *e = orgGraph->getHead(i); e; e = e->next) {
            int to = orgGraph->sccID[e->toVertex]; 
            if(from != to)
                addEdge(from, to);
        }
    }
}

int Graph::getInDegOutDegMax() {
    int i;
    int inCount = 0, outCount = 0;
    for(i = 0; i < vertexCount; i++) {
        if(!inDeg[i]) {
            inCount++;
        }
        if(!outDeg[i]) {
            outCount++;
        }
    }
    return inCount>outCount?inCount:outCount;
} 

class GraphEx {
public:
    // 原图、反图
    Graph *orgGraph, *invGraph;
    // 缩点后的图
    Graph *shrinkGraph;
     
    GraphEx() {
        orgGraph = new Graph;
        invGraph = new Graph;
        shrinkGraph = new Graph;
    }
    ~GraphEx() {
        delete orgGraph;
        delete invGraph;
        delete shrinkGraph;
    }
    void init(int vCount);
    void addEdge(int from, int to);
    void Kosaraju();
    void ShrinkGraph();
    int getSCCCount();

    static GraphEx& Instance() {
        static GraphEx inst;
        return inst; 
    }
};
void GraphEx::init(int vCount) {
    orgGraph->init(vCount);
    invGraph->init(vCount);
}

void GraphEx::addEdge(int from, int to) {
    orgGraph->addEdge(from, to);
    invGraph->addEdge(to, from);
}

void GraphEx::Kosaraju() {
    // 对反图求一次后序遍历
    invGraph->postOrderTraversal();
    // 按照后序的逆序遍历原图
    orgGraph->preOrderTraversal(invGraph->order, invGraph->orderCount);
}

void GraphEx::ShrinkGraph() {
    // 按照原图进行缩图（缩边 + 缩点） 
    shrinkGraph->doShrink(orgGraph);
}

int GraphEx::getSCCCount() {
    return orgGraph->sccCount;
}

int main() {
    int n, m;
    while(scanf("%d %d", &n, &m) !=EOF) {
        GraphEx &g = GraphEx::Instance();
        g.init(n);
        while(m--) {
            int x, y;
            scanf("%d %d", &x, &y);
            x--;
            y--;
            g.addEdge(x, y);
        }
        g.Kosaraju();
        g.ShrinkGraph();
         int ans = g.shrinkGraph->getInDegOutDegMax();
         if(ans == 1) {
             ans = 0;
        }
        printf("%d\n", ans);
    }
    return 0;
}

/*
14 12
1 4
2 4
3 4
4 5
4 6
4 7
4 8
9 12
10 12
11 12
12 13
12 14
*/
