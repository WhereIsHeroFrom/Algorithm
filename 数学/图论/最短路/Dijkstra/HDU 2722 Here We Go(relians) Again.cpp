#include <iostream>
#define M 999999999
using namespace std;
int map[1000][1000];
int i, j, k, a;
char buf[10000];
int d[10000];
bool s[10000];
int n, m, start;
int main()
{
    while (scanf("%d%d", &n, &m) != EOF)
    {
        if (n == 0 && m == 0)
            break;
        for (i = 1; i <= (n + 1)*(m + 1); i++)
            for (j = 1; j <= (n + 1)*(m + 1); j++)
                map[i][j] = M;
        for (i = 1; i <= 2 * n + 1; i++)
        {
            if (i & 1)
            {
                start = (i / 2)*(m + 1) + 1;
                for (j = start; j < start + m; j++)
                {
                    scanf("%d %s", &a, buf);

                    if (a == 0)
                    {
                        map[j + 1][j] = map[j][j + 1] = M;
                        continue;
                    }

                    a = 2520 / a;
                    if (buf[0] == '*')
                    {
                        map[j + 1][j] = map[j][j + 1] = a;
                    }
                    else if (buf[0] == '>')
                    {
                        map[j][j + 1] = a;
                    }
                    else if (buf[0] == '<')
                    {
                        map[j + 1][j] = a;
                    }
                }
            }
            else
            {
                start = ((i - 1) / 2)*(m + 1) + 1;
                for (j = start; j < start + m + 1; j++)
                {
                    scanf("%d%s", &a, buf);
                    if (a == 0)
                    {
                        map[j + m + 1][j] = map[j][j + m + 1] = M;
                        continue;
                    }
                    a = 2520 / a;
                    if (buf[0] == '*')
                    {
                        map[j + m + 1][j] = map[j][j + m + 1] = a;
                    }
                    else if (buf[0] == 'v')
                    {
                        map[j][j + m + 1] = a;
                    }
                    else if (buf[0] == '^')
                    {
                        map[j + m + 1][j] = a;
                    }
                }
            }
        }

        for (i = 2; i <= (n + 1)*(m + 1); i++)
        {
            d[i] = map[1][i];
            s[i] = false;
        }
        s[1] = true;
        while (1)
        {
            int Min = M;
            int u = -1;
            for (i = 1; i <= (n + 1)*(m + 1); i++)
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

            for (i = 1; i <= (n + 1)*(m + 1); i++)
            {
                if (!s[i] && map[u][i] != M && d[i] > map[u][i] + d[u])
                {
                    d[i] = map[u][i] + d[u];
                }
            }
        }
        if (d[(n + 1)*(m + 1)] == M)
            printf("Holiday\n");
        else
            printf("%d blips\n", d[(n + 1)*(m + 1)]);
    }
}