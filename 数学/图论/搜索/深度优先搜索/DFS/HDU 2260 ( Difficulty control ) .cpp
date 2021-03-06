#include <iostream>
using namespace std;
struct point
{
    char c;
    int value;
}p[100];
int stack[100], top;
int buf[100], rt;
int zong[110];
int n, m;
int cha;
int cmp(const void *a, const void *b)
{
    point *c = (point *)a;
    point *d = (point *)b;
    return c->c - d->c;
}
void dfs(int sum, int index)
{
    int i;
    if(abs(sum - m) < cha)
    {
        cha = abs(sum - m);
        
        rt = top;
        for(i = 0; i < top; i++)
            buf[i] = stack[i];
    }
    if(sum - m >= cha)
        return ;
    
    for(i = index; i < n; i++)
    {
        if(m-(sum+zong[i]) >= cha)
            return;
         stack[top++] = i;
         dfs(sum + p[i].value, i+1);
         top--;
    }
}
int main()
{
    int i;
    int sum = 0;
    char ss[10];
    while(scanf("%d%d", &n, &m) != EOF)
    {
        sum = 0;
        for(i = 0; i < n ;i++)
        {
            scanf("%s %d", ss, &p[i].value);
            p[i].c = ss[0];
            sum += p[i].value;
        }
        
        qsort(p, n, sizeof(point), cmp);
        
        if(sum <= m)
        {
             printf("%d\n", n);
             for(i = 0; i < n; i++)
             {
                 if(i) printf(" ");
                 printf("%c", p[ i ].c);
             }
             puts("");   
             continue;
        }
        zong[n-1] = p[n-1].value;
        
        for(i = n-2; i >= 0; i--)
            zong[i] = zong[i+1] + p[i].value;
        
        
        top = 0;
        cha = INT_MAX;
        dfs(0, 0);
        
        printf("%d\n", rt);
        for(i = 0; i < rt; i++)
        {
            if(i) printf(" ");
            printf("%c", p[ buf[i] ].c);
        }
        puts("");
    }
}
