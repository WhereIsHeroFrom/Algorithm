#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

const int N = 501;
const int INF = 1 << 28;
int n, m, k;

class Graph
{

private:
   bool xckd[N], yckd[N];
   int edge[N][N], xmate[N], ymate[N];
   int lx[N], ly[N], slack[N], prev[N];
   queue<int> Q;
   bool bfs();
   void agument(int);

public:
   bool make();
   int KMMatch();
};

bool Graph::make() 
{
/*
   scanf("%d %d", &h, &w);
   if(w == 0) return false;
   scanf("\n"); n = 0;
   for(int i = 0; i < h; i++) {
      gets(line);
      for(int j = 0; line[j] != 0; j++) {
         if(line[j] == 'H') house[n++] = i * N + j;
         if(line[j] == 'm') child[cn++] = i * N + j;
      }
   }
   for(int i = 0; i < n; i++) {
      int cr = child[i] / N, cc = child[i] % N;
      for(int j = 0; j < n; j++) {
         int hr = house[j] / N, hc = house[j] % N;
         edge[i][j] = -abs(cr-hr) - abs(cc-hc);
      }
   }
   return true;
*/

   int a, b, c, i, j;

   if(n <= m)
   {
       for(i = 0; i < m; i++)
       {
           for(j = 0; j < m ;j++)
           {
               edge[i][j] = -10000000;
           }
       }
   }

   while(k--)
   {
       scanf("%d %d %d", &a, &b, &c);
       if(c < 0)
           edge[a][b] = -10000000;
       else
           edge[a][b] = c;
   }
   
   return true;
}
bool Graph::bfs() 
{
   while(!Q.empty()) 
   {
      int p = Q.front(), u = p>>1; Q.pop();
      if(p&1) 
      {
         if(ymate[u] == -1) 
         { 
             agument(u); 
             return true; 
         }
         else 
         { 
             xckd[ymate[u]] = true; 
             Q.push(ymate[u]<<1);
         }
      } else 
      {
         for(int i = 0; i < n; i++)
         {
            if(yckd[i]) continue;
            else if(lx[u]+ly[i] != edge[u][i])
            {
               int ex = lx[u]+ly[i]-edge[u][i];
               if(slack[i] > ex) { slack[i] = ex; prev[i] = u; }
            }
            else
            {
               yckd[i] = true; prev[i] = u;
               Q.push((i<<1)|1);
            }
         }
      }
   }
   return false;
}
void Graph::agument(int u) 
{
   while(u != -1) 
   {
      int pv = xmate[prev[u]];
      ymate[u] = prev[u];
      xmate[prev[u]] = u;
      u = pv;
   }
}
int Graph::KMMatch() 
{
    int i;

    if(n > m)
        return -1;
    int ty = n;
    n = m;


   memset(ly, 0, sizeof(ly));
   for(i = 0; i < n; i++) 
   {
      lx[i] = -INF;
      for(int j = 0; j < n; j++) 
          lx[i] = lx[i] > edge[i][j] ? lx[i] : edge[i][j];
   }
   memset(xmate, -1, sizeof(xmate)); 
   memset(ymate, -1, sizeof(ymate));

   bool agu = true;

   for(int mn = 0; mn < n; mn++) 
   {
      if(agu) 
      {
         memset(xckd, false, sizeof(xckd));
         memset(yckd, false, sizeof(yckd));
         for(int i = 0; i < n; i++) 
             slack[i] = INF;
         while(!Q.empty()) 
             Q.pop();

         xckd[mn] = true; 
         Q.push(mn<<1);
      }
      if(bfs()) 
      { 
          agu = true; 
          continue; 
      }
      int ex = INF; 
      mn--; 
      agu = false;

      for(i = 0; i < n; i++)
          if(!yckd[i]) ex = ex < slack[i] ? ex : slack[i];

      for(i = 0; i < n; i++) 
      {
         if(xckd[i]) lx[i] -= ex;
         if(yckd[i]) ly[i] += ex;
         slack[i] -= ex;
      }
      for(i = 0; i < n; i++)
         if(!yckd[i] && slack[i] == 0) { yckd[i] = true; Q.push((i<<1)|1); }

   }
   int cost = 0;

   for(i = 0; i < n; i++) cost += edge[i][xmate[i]];

   if(cost - (ty - m) * 10000000 < -9999999)
       return -1;

   return cost - (ty - m) * 10000000;
}

int main()
{
   Graph g;
   int c = 1;
   while(scanf("%d %d %d", &n, &m, &k) != EOF)
   {
       g.make();
       printf("Case %d: %d\n", c++, g.KMMatch());
   }
   return 0;
}


