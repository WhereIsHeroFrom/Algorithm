#include <iostream>
using namespace std;
struct point
{
    int w;
    int v;
}p[10000];
int i, j, a[10000];
int k, t, n, m;

int cmp(const void *a, const void *b)
{
    point *c = (point *)a;
    point *d = (point *)b;
    return c->v - d->v;
}
double sum = 0;
int main()
{
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d",&n, &m);
        for(i = 0; i < m ;i++)
        {
            scanf("%d%d", &p[i].v, &p[i].w);
        }
        qsort(p, m, sizeof(point), cmp);

        sum = 0;
        for(i = 0; i < m; i++)
        {
            if(n > p[i].v * p[i].w)
            {
                n -= p[i].v * p[i].w;
                sum += p[i].w;
            }else
            {
                sum += n*1.0/p[i].v; 
                break;
            }
        }
        printf("%.2lf\n", sum);

    }

    return 0;
}

