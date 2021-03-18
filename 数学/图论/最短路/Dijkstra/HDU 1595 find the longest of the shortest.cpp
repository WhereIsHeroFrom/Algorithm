#include <iostream>
#define MAX 10000000
using namespace std;
int rt[1001];
int top;
int n;
int d[1001], s[1001], map[1001][1001];
int path[1001];

int Dijstra(int st)
{
    int i, flag;
    for (i = 1; i <= n; i++)
    {
        d[i] = map[st][i];
        s[i] = false;
        if (d[i] == MAX)
            path[i] = -1;
        else
            path[i] = st;
    }

    d[st] = 0;
    s[st] = true;

    while (1)
    {
        int Min = MAX;
        int u = -1;

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

        s[u] = 1;

        for (i = 1; i <= n; i++)
        {
            if (!s[i] && d[u] + map[u][i] < d[i])
            {
                d[i] = d[u] + map[u][i];
                path[i] = u;
            }
        }
    }

    if (d[n] == MAX)
        return 0;
    return d[n];
}

int main()
{
    int a, b, c, i, j, m, Max;
    while (scanf("%d %d", &n, &m) != EOF)
    {

        Max = 0;
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                map[i][j] = MAX;

        while (m--)
        {
            scanf("%d %d %d", &a, &b, &c);
            map[a][b] = map[b][a] = c;
        }

        int yu = Dijstra(1);

        int u = n;
        top = 0;
        while (path[u] != -1)
        {
            rt[top++] = u;
            u = path[u];
        }

        rt[top++] = 1;

        int temp;
        for (i = 0; i < top - 1; i++)
        {
            temp = map[rt[i]][rt[i + 1]];
            map[rt[i]][rt[i + 1]] = map[rt[i + 1]][rt[i]] = MAX;

            int yu = Dijstra(1);
            if (yu > Max)
                Max = yu;
            map[rt[i]][rt[i + 1]] = map[rt[i + 1]][rt[i]] = temp;
        }

        printf("%d\n", Max);
    }
    return 0;
}
