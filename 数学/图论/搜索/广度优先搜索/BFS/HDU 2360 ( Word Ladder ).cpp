#include <iostream>
#include <map>
#include <vector>
using namespace std;

map < char *, int > Map;

struct ele
{
    int step;
    int now;
    int fro;
}temp, tt;

int front, end;
ele q[1500001];

struct point
{
    char ch[31];
}p[110];
int n, len;
int cmp(const void *a, const void *b)
{
    point *c = (point *)a;
    point *d = (point *)b;
    return strcmp(c->ch, d->ch);
}
char buf[110][31];
char M_hash[110][31];
int T = 1;
vector < int > vec[110];


int Min[1000], Top;         //保存最优解
int stack[1000], top;

int check(char *a, char *b)
{
    int i, j;
    int hash[31];
    for(i = 0; i < 23; i++)
        hash[i] = 0;
    int coun = 0;

    for(i = 0; i < len; i++)
    {
        for(j = 0; j < len; j++)
        {
            if(!hash[j])
            {
                if(a[i] == b[j])
                {
                    hash[j] = 1;
                    coun++;
                    break;
                }
            }
        }
    }
    if(coun == len - 1)
        return 1;
    return 0;
}

int orz(char *a, char *b)
{
    int i, j;
    for(i = 0; i < len; i++)
    {
        for(j = 0; j < len; j++)
            if(a[i] == b[j])
                break;
        if(j != len)
            return 0;
    }
    return 1;
}

int main()
{
    int t, i, j;
    scanf("%d", &t);
    while(t--)
    {
        T = 1;
        Map.clear();
        for(i = 1; i <= 100; i++)
            vec[i].clear();

        scanf("%d%d", &n, &len);
        for(i = 0; i < n; i++)
            scanf("%s", p[i].ch);
        qsort(p, n, sizeof(point), cmp);
        //for(i = 0; i < n; i++)
        //    printf("%s\n", p[i].ch);

        int u, v;
        for(i = 0; i < n; i++)
        {
            if(Map[p[i].ch] == 0)
            {
                Map[p[i].ch] = T++;
                strcpy(M_hash[T-1], p[i].ch);
            }
        }

        T--;

        for(i = 1; i <= T; i++)
        {
            for(j = 1; j <= T; j++)
            {
                if(i == j)
                    continue;
                if(check(M_hash[i], M_hash[j]))
                {
                    //printf("%d %d\n", i, j);
                    vec[i].push_back(j);
                    vec[j].push_back(i);
                }
            }
        }

        int hash[110];
        Top = -1;

        for(i = 1; i <= T; i++)   //枚举每个点为起点
        {
            memset(hash, 0, sizeof(hash));
            front = end = 0;
            temp.fro = -1;
            temp.step = 0;
            temp.now = i;
            hash[i] = 1;
            q[end++] = temp;

            while(front < end)
            {
                temp = q[front++];

                if ( orz(M_hash[i], M_hash[temp.now]) )
                {
                    top = 0;
                    while(temp.fro != -1)
                    {
                        stack[ top ++ ] = temp.now;
                        temp = q[temp.fro];
                    }
                    stack[top++] = i;
                    if(Top == -1 || top < Top)
                    {
                        Top = top;
                        for(j = 0; j < Top; j++)
                        {
                            Min[j] = stack[j];
                        }
                    }

                    if(Top == len + 1)
                        break;
                }
                tt.fro = front - 1;
                tt.step = temp.step + 1;
                int zong = vec[temp.now].size();

                for(j = 0; j < zong; j++)
                {
                    int v = vec[temp.now][j];
                    tt.now = v;
                    if(!hash[ v ] )
                    {
                        hash[ v ] = 1;
                        q[end++] = tt;
                    }
                }
            }
        }

        printf("%s", M_hash[ Min[Top-1] ]);
        for(i = Top - 2; i >= 0; i--)
        {
            printf(" %s", M_hash[ Min[i] ]);
        }
        puts("");
    }
}
