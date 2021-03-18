#include <iostream>
#include <cmath>
#define MAX 2100000000
using namespace std;
int s, e, n, m, k, target;
int p[301], speed[301];
double map[1001][1001], d[1001];
struct node
{
    double time;
    int dis;
    int num;
}people[301];

int cmp(const void *a, const void *b)
{
    node *c = (node *)a;
    node *d = (node *)b;
    if (c->time != d->time)
        return c->time - d->time > 0 ? 1 : -1;
    else if (c->dis != d->dis)
        return d->dis - c->dis > 0 ? 1 : -1;
    else
        return d->num - c->num > 0 ? 1 : -1;
}
void Dijkstra(int target)
{
    int i, u;
    bool s[1001];
    double Min = MAX;
    for (i = 1; i <= n; i++)
    {
        d[i] = map[target][i];
        s[i] = false;
    }
    s[target] = true;
    while (1)
    {
        Min = MAX;
        u = -1;
        for (i = 1; i <= n; i++)
        {
            if (!s[i] && d[i] < Min)
            {
                Min = d[i];
                u = i;
            }
        }
        if (u == -1)
            break;
        s[u] = true;
        for (i = 1; i <= n; i++)
        {
            if (!s[i] && d[i] > d[u] + map[u][i])
                d[i] = d[u] + map[u][i];
        }
    }
    d[target] = 0;
}
int main()
{
    int i, j, a, b, c;
    while (scanf("%d%d%d", &n, &m, &k) != EOF)
    {
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                map[i][j] = MAX;
        while (k--)
        {
            scanf("%d%d%d", &a, &b, &c);
            if (c < map[b][a])
                map[b][a] = c;
        }
        scanf("%d", &target);
        for (i = 1; i <= m; i++)
        {
            scanf("%d", &p[i]);
        }
        for (i = 1; i <= m; i++)
        {
            scanf("%d", &speed[i]);
        }
        Dijkstra(target);
        for (i = 1; i <= m; i++)
        {
            people[i].dis = d[p[i]];
            people[i].time = people[i].dis*1.0 / speed[i];
            people[i].num = i;
        }

        /*for(i = 1; i <= m; i++)
        {
        printf("dis = %d time = %lf num = %d\n", people[i].dis, people[i].time, people[i].num);
        }*/
        qsort(&people[1], m, sizeof(node), cmp);
        for (i = 1; i <= m; i++)
        {
            if (people[i].dis != MAX)
                break;
        }
        if (i == m + 1)
            printf("No one\n");
        else
            printf("%d\n", people[i].num);
    }
    return 0;
}