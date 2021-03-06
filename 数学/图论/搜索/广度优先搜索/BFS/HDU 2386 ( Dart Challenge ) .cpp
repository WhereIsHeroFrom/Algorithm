




#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
struct point
{
    int step;
    int x;
}temp, tt;

int hash[1000000];
int stac[10000], top;
int n, k, Max, a;
queue < point > q;
int main()
{
    int t, c = 1;
    int i, j, coun;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d %d", &n, &k);
        top = 0;
        Max = 0;
        memset(hash, 0, sizeof(hash));
        for(i = 0; i < n; i++)
        {
            scanf("%d", &a);
            if(a > Max)
                Max = a;
            hash[a] ++;
            hash[2*a]++;
            hash[3*a]++;
        }
        hash[3*Max] --;
        for(i = 1; i <= 300; i++)
            if(hash[i] > 0) stac[top++] = i;
        
        sort(stac, stac+top);
        Max = k * stac[top-1];
        memset(hash, 0, sizeof(hash));
        
        while(!q.empty())
            q.pop();
        temp.x = 0;
        temp.step = 0;
        q.push(temp);
        while(!q.empty())
        {
            temp = q.front();
            q.pop();
            tt.step = temp.step + 1;
            if(tt.step > k)
                continue;
            for(i = 0; i < top; i++)
            {
                int v = tt.x = stac[i] + temp.x;
                if(v > Max)
                    break;
                if(!hash[v])
                {
                    hash[v] = 1;
                    q.push(tt);
                }
            }
            
        }
        int coun = 0;
        for(i = 0; i <= Max; i++)
            if(hash[i]) coun ++;
        
        printf("Scenario #%d:\n", c++);
        printf("%d\n\n", coun + 1);
    }
}


