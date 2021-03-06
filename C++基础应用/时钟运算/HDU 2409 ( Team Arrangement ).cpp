#include <iostream>

using namespace std;

struct point
{
    char name[30];
    int NumOfOrder;
    char Charecter;
    int NumOfYear;
}p[1000], buf[4][100];
int top[4];

char ch[] = {'G', 'D', 'M', 'S'};
int i, j, start, end, ty;
int x, y;
char df[1000];
int hash[100][100];
int cmp(const void *a, const void *b)
{
    point *c = (point *)a;
    point *d = (point *)b;
    return c->NumOfOrder - d->NumOfOrder;
}

int main()
{
    while(scanf("%d", &p[0].NumOfOrder) != EOF)
    {
        if(!p[0].NumOfOrder) break;

        memset(hash, 0, sizeof(hash));
        for(i = 0; i < 22; i++)
        {
            if(i)
            {
                scanf("%d", &p[i].NumOfOrder);
            }
            scanf("%s %s", p[i].name, df);
            p[i].Charecter = df[0];

            getchar();

            gets(df);
            int len = strlen(df);
            
            p[i].NumOfYear = 0;
            for(j = 0; j < len; j++)
            {
                if(df[j] >= '0' && df[j] <= '9')
                {
                    sscanf(&df[j], "%d-%d", &start, &end);
                    while(df[j] >= '0' && df[j] <= '9' || df[j] == '-')
                        j ++;
                    p[i].NumOfYear += end - start + 1;
                }
            }
        }
        scanf("%s", df);
        int g, d, m, s;
        sscanf(df, "%d-%d-%d", &d, &m, &s);

        int dor[4];

        dor[0] = 1;
        dor[1] = d;
        dor[2] = m;
        dor[3] = s;


        for(ty = 0; ty < 4; ty++)
        {
                top[ty] = 0;

                for(i = 0; i < 22; i++)
                {
                    if(p[i].Charecter == ch[ty])
                    {
                        buf[ty][top[ty] ++] = p[i];
                    }
                }
                if(top[ty] < dor[ty]) break;
                qsort(buf[ty], top[ty], sizeof(point), cmp);
        }

        if(ty == 4)
        {       
            int Max = -1;
            for(ty = 0; ty < 4; ty++)
            {
                for(i = 0; i < dor[ty]; i++)
                {
                    if(buf[ty][i].NumOfYear > Max ||
                        buf[ty][i].NumOfYear == Max && buf[ty][i].NumOfOrder > buf[x][y].NumOfOrder)
                    {
                        Max = buf[ty][i].NumOfYear;
                        x = ty;
                        y = i;
                        
                    }
                      //printf("%d %s %c\n", buf[ty][i].NumOfOrder, buf[ty][i].name, buf[ty][i].Charecter);
                }
            }
            hash[x][y] = 1;
            printf("%d %s %c\n", buf[x][y].NumOfOrder, buf[x][y].name, buf[x][y].Charecter);

            for(ty = 0; ty < 4; ty++)
            {
                for(i = 0; i < dor[ty]; i++)
                {
                    if(!hash[ty][i])
                      printf("%d %s %c\n", buf[ty][i].NumOfOrder, buf[ty][i].name, buf[ty][i].Charecter);
                }
            }
        }else
        {
            printf("IMPOSSIBLE TO ARRANGE\n");
        }

        puts("");




    }
}
