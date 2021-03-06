#include <iostream>
#include <algorithm>
using namespace std;

int t;
char str[1001];

struct point
{
    char dir[101];
    char cop[101];
    int len;
    int ty;
}p[10001];

struct intv
{
    int start;
    int end;
    int len;
}rt[10001];
int zong;


int apr = 0, n;
int stack[10001], top;
int bol[10001];           // 0 impossible     1 ambigus      2 unique
int ty[10001], orz;
int len, flag;


int dfs(int start)
{
    int i, j, k;
    char buf[111];

    if(start == len)
    {
        if(apr)
        {
            return 1;
        }else
            apr ++;

        orz = 0;
        for(i = 0; i < top; i++)
            ty[orz ++] = stack[i];

        return 2;
    }

    int coun = 0;
    for(i = 0; i <= zong; i++)
    {
        if(rt[i].len > len - start)
            break;

        for(j = start; j < start + rt[i].len; j++)
            buf[j-start] = str[j];
        buf[j-start] = '\0';
        
        sort(buf, buf+rt[i].len);

        for(j = rt[i].start; j <= rt[i].end; j++)
        {
            int s = strcmp( buf, p[j].cop );

            if( s < 0)
                break;

            if( s == 0 && str[start] == p[j].dir[0] && str[start+rt[i].len-1] == p[j].dir[rt[i].len-1] )
            {

                stack[ top ++ ] = j;

                if( bol[ start + rt[i].len ] == -1) 
                    bol[ start + rt[i].len ] = dfs(start + rt[i].len);

                if(bol[ start + rt[i].len ] == 1)
                    return 1;

                if(bol[ start + rt[i].len ] == 2)
                    coun ++;

                top --;
            }
        }
    }

    if(coun == 1)
        return 2;
    if(coun > 1)
        return 1;

    return 0;
}

int cmp(const void *a, const void *b)
{
    point *c = (point *)a;
    point *d = (point *)b;

    if(c->len == d->len)
        return strcmp(c->cop, d->cop);
    return c->len - d->len;
}
int main()
{

    int t, i;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%s", str);
        len = strlen(str);

        scanf("%d", &n);
        apr = 0;

        memset(bol, -1, sizeof(bol));

        for(i = 0; i < n; i++)
        {
            scanf("%s", p[i].dir);
            p[i].len = strlen(p[i].dir);
            strcpy(p[i].cop, p[i].dir);
            sort(p[i].cop, p[i].cop+p[i].len);
        }

        qsort(p, n, sizeof(point), cmp);

        flag = 0;

        zong = 0;

        rt[zong].len = p[0].len;
        rt[zong].start = 0;
        rt[zong].end = 0;
        
        for(i = 1; i < n; i++)
        {
            if(p[i].len == rt[zong].len)
            {
                rt[zong].end = i;
            }else
            {
                zong ++;
                rt[zong].len = p[i].len;
                rt[zong].start = i;
                rt[zong].end = i;
            }
        }

    //    for(i = 0; i <= zong; i++)
    //        printf("%d %d %d\n", rt[i].start, rt[i].end, rt[i].len);


    //    for(i = 0; i < n; i++) printf("%s(%s)\n", p[i].dir, p[i].cop);

        top = 0;

        bol[0] = dfs(0);

        /*for(i = 0; i <= len; i++)
            printf("%d ", bol[i]);
        puts("");*/

        if(bol[0] == 1)
            printf("ambiguous\n");
        else if(bol[0] == 0)
            printf("impossible\n");
        else
        {
            for(i = 0; i < orz; i++)
            {
                if(i) printf(" ");
                printf("%s", p[ ty[i] ].dir);
            }
            puts("");
        }
    }
}

/*
2
ab
2
a
b
*/
