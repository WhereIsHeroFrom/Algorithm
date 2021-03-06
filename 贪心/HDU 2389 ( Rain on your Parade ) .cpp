#include <iostream>

using namespace std;

struct point
{
    int day;
    int start;
    int end;
}p[50001];

int cmp(const void *a, const void *b)
{
    point *c = (point *)a;
    point *d = (point *)b;
    if(c->day == d->day)
    {
        if(c->end != d->start)
            return c->end - d->end;
        else
            return c->start - d->start;
    }else
        return c->day - d->day;
}

point stack[50001];
int top;
int m, i, j;
int t, sum, end;
int main()
{

    int c = 1;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &m);
        for(i = 0; i < m; i++)
            scanf("%d %d %d", &p[i].day, &p[i].start, &p[i].end);
        qsort(p, m, sizeof(point), cmp);

        top = 0;
        stack[top].start = 0;
        for(i = 1; i < m; i++)
        {
            if(p[i].day != p[i-1].day)
            {
                stack[top].end = i - 1;
                top++;
                stack[top].start = i;
            }
        }
        stack[top].end = i - 1;
        top++; 
        sum = 0;
        for(i = 0; i < top; i++)
        {
            sum ++;
            end = p[ stack[i].start ].end;
            for(j = stack[i].start + 1; j <= stack[i].end; j++)
            {
                if(end <= p[j].start)
                {
                    sum ++;
                    end = p[j].end;
                }
            }
        }

        printf("Scenario #%d:\n%d\n\n", c++, sum);
    }

}
