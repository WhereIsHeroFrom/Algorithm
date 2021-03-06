#include <iostream>
using namespace std;

struct PC
{
    int start;
    int end;
    int index;
};

struct Stu
{
    PC stack[101];
    int top;
}p[10001];

int N, M;
int hash[10001];

int main()
{
    int r, q, t, n, m, s, i, j, k;
    int ts, te;
    while(scanf("%d %d", &N, &M) != EOF)
    {
        if(!N && !M) break;

        scanf("%d", &r);

        for(i = 1; i <= M; i++)
            p[i].top = 0;

        for(i = 0; i < r; i ++)
        {
            scanf("%d %d %d %d", &t, &n, &m ,&s);

            if(s == 1)
            {
                p[m].stack[ p[m].top ].start = t;
                p[m].stack[ p[m].top ++].index = n;

            }else
            {
                for(j = p[m].top - 1; j >= 0; j--)
                {
                    if(n == p[m].stack[j].index)
                        break;
                }
                p[m].stack[j].end = t;

            }

        }

        scanf("%d", &q);
        
        for(i = 0; i < q; i++)
        {
            scanf("%d %d %d", &ts, &te, &m);

            memset(hash, 0, sizeof(hash));

            int coun = 0;
            for(j = 0; j < p[m].top; j++)
            {
                int s = p[m].stack[j].start;
                int e = p[m].stack[j].end;
                
                if(ts >= s && te <= e)
                {
                    coun += te - ts;
                    break;
                }

                if(te >= s && te <= e)
                {
                    ts = s;
                    coun += te - ts;
                    break;
                }

                if(ts >= s && ts <= e)
                {
                    coun += e - ts;
                    ts = e;
                }

                if(ts <= s && te >= e)
                {
                    coun += e - s;
                    ts = e;
                }
            }

            printf("%d\n", coun);
        }
    }

    return 0;
}

