#include <stdio.h>
__int64 d[110][110], node[110], w[110][110], inf, daan[110][110];
__int64 t, l[5], c[5], n, m;
inline void dijistra(__int64 s)
{
    __int64 mark[110], mid;
    __int64 i, j, u;
    for (i = 1; i <= n; i++)
    {
        d[s][i] = w[s][i];
        mark[i] = 0;
    }
    mark[s] = 1;
    for (i = 2; i <= n; i++)
    {
        mid = inf;
        u = -1;
        for (j = 1; j <= n; j++)
        {
            if (!mark[j] && d[s][j] <= mid)
            {
                mid = d[s][j];
                u = j;
            }
        }
        if (u == -1)
            break;
        mark[u] = 1;
        for (j = 1; j <= n; j++)
        {
            if (!mark[j] && w[u][j] != inf &&d[s][j] > d[s][u] + w[u][j])
            {
                d[s][j] = d[s][u] + w[u][j];
            }
        }
    }
    return;
}

int main()
{
    __int64 temp;
    register __int64   i, j, y = 1, s, e;
    inf = 100000000;
    inf *= inf;
    scanf("%I64d", &t);
    while (t--)
    {
        for (i = 1; i <= 4; i++)
        {
            scanf("%I64d", &l[i]);
        }

        for (i = 1; i <= 4; i++)
        {
            scanf("%I64d", &c[i]);
        }

        scanf("%I64d%I64d", &n, &m);

        for (i = 1; i <= n; i++)
        {
            scanf("%I64d", &node[i]);
            w[i][i] = inf;
        }
        for (i = 1; i <= n; i++)
        {
            for (j = i + 1; j <= n; j++)
            {
                temp = node[i] - node[j] > 0 ? (node[i] - node[j]) : (node[j] - node[i]);
                if (0 < temp && temp <= l[1])
                    w[i][j] = w[j][i] = (__int64)c[1];
                else if (l[1] < temp && temp <= l[2])
                    w[i][j] = w[j][i] = (__int64)c[2];
                else if (l[2] < temp && temp <= l[3])
                    w[i][j] = w[j][i] = (__int64)c[3];
                else if (l[3] < temp && temp <= l[4])
                    w[i][j] = w[j][i] = (__int64)c[4];
                else if (temp > l[4])
                    w[i][j] = w[j][i] = inf;
            }
        }
        printf("Case %I64d:\n", y++);
        for (i = 1; i <= n; i++)
        {
            dijistra(i);
        }
        while (m--)
        {
            scanf("%I64d%I64d", &s, &e);
            temp = d[s][e];
            if (temp == inf)
                printf("Station %I64d and station %I64d are not attainable.\n", s, e);
            else
                printf("The minimum cost between station %I64d and station %I64d is %I64d.\n", s, e, temp);
        }


    }
}