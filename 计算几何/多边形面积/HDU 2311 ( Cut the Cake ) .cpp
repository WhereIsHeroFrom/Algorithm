#include <iostream>
#include <algorithm>
using namespace std;
int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
struct point     //横轴x，纵轴y
{
    int x;
    int y;
};

struct cake
{
    point upleft;
    point downright;
    int Time;
    int area;
}p[200000], buf[200000];

int hen, gao;
int n, w, d;
int i, j;
int zong;
int num, step;
int x, y;
int ty;
int stack[200000], top;
int cmp(const void*a, const void *b)
{
    cake *c = (cake *)a;
    cake *d = (cake *)b;
    if(c->Time != d->Time)
         return c->Time - d->Time;
    else
        return c->area - d->area;
}

int main()
{
    while(scanf("%d %d %d", &n, &w, &d) != EOF)
    {
        if(!n && !w && !d)
            break;
        zong = 1;

        p[1].upleft.x = 1;
        p[1].upleft.y = 1;
        p[1].downright.x = w+1;
        p[1].downright.y = d+1;
        p[1].Time = 0;
        p[1].area = w * d;

        for(ty = 1; ty <= n; ty++)
        {
            scanf("%d %d", &num, &step);
            x = p[num].upleft.x;
            y = p[num].upleft.y;
            zong = 1;

            for(j = 1; j <= ty; j++)
            {
                if(j != num)
                   buf[zong++] = p[j];
                //printf("%d %d %d %d %d\n", p[j].upleft.x, p[j].upleft.y, p[j].downright.x, p[j].downright.y, p[j].Time);

            }

            while(1)
            {
                for(i = 0; i < 4; i++)
                {
                    if(i == 0)
                    {
                        if(p[num].downright.x - x < step)
                        {    
                            step -= (p[num].downright.x - x);
                            x = p[num].downright.x;
                        }else 
                        {
                            x += step;
                            break;
                        }
                    }
                    if(i == 2)
                    {
                        if( x - p[num].upleft.x < step)
                        {
                            
                            step -= (x - p[num].upleft.x);
                            x = p[num].upleft.x;
                        }else 
                        {
                            x -= step;
                            break;
                        }
                    }

                    if(i == 1)
                    {
                        if(p[num].downright.y - y < step)
                        {
                            
                            step -= (p[num].downright.y - y);
                            y = p[num].downright.y;
                        }else 
                        {
                            y += step;
                            break;
                        }
                    }

                    if(i == 3)
                    {
                        if( y - p[num].upleft.y < step)
                        {
                            
                            step -= (y - p[num].upleft.y);
                            y = p[num].upleft.y;
                        }else 
                        {
                            y -= step;
                            break;
                        }
                    }
                }    
                if(i < 4)
                    break;
            }//printf("%d %d %d\n", x, y, step);    
            
            
            //printf("%d %d (%d, %d)(%d, %d)\n", x, y, p[num].upleft.x, p[num].upleft.y, p[num].downright.x, p[num].downright.y);

            buf[zong].Time = ty;
            buf[zong+1].Time = ty;

            if(x == p[num].upleft.x)
            {
                buf[zong].upleft = p[num].upleft;
                buf[zong].downright.x = p[num].downright.x;
                buf[zong].downright.y = y;

                //printf("%d %d %d %d\n", buf[zong].upleft.x, buf[zong].upleft.y, buf[zong].downright.x, buf[zong].downright.y);

                zong++;
                buf[zong].upleft.x = x;
                buf[zong].upleft.y = y;
                buf[zong].downright = p[num].downright;
                //printf("%d %d %d %d\n", buf[zong].upleft.x, buf[zong].upleft.y, buf[zong].downright.x, buf[zong].downright.y);

                zong++;
            }

            if(y == p[num].upleft.y)
            {
                buf[zong].upleft = p[num].upleft;
                buf[zong].downright.x = x;
                buf[zong].downright.y = p[num].downright.y;

                zong ++;

                buf[zong].upleft.x = x;
                buf[zong].upleft.y = p[num].upleft.y;
                buf[zong].downright = p[num].downright;

                zong++;
            }

            if(x == p[num].downright.x)
            {
                buf[zong].upleft = p[num].upleft;
                buf[zong].downright.x = x;
                buf[zong].downright.y = y;

                zong++;

                buf[zong].upleft.x = p[num].upleft.x;
                buf[zong].upleft.y = y;
                buf[zong].downright = p[num].downright;

                zong++;
            }

            if(y == p[num].downright.y)
            {
                buf[zong].upleft = p[num].upleft;
                buf[zong].downright.x = x;
                buf[zong].downright.y = y;

                zong++;

                buf[zong].upleft.x = x;
                buf[zong].upleft.y = p[num].upleft.y;
                buf[zong].downright = p[num].downright;

                zong++;
            }

            buf[zong-1].area = (buf[zong-1].downright.y - buf[zong-1].upleft.y)*(buf[zong-1].downright.x - buf[zong-1].upleft.x);
            buf[zong-2].area  = (buf[zong-2].downright.y - buf[zong-2].upleft.y)*(buf[zong-2].downright.x - buf[zong-2].upleft.x);
            qsort(&buf[1], zong-1, sizeof(cake), cmp);
            for(j = 1; j < zong; j++)
            {
                 p[j] = buf[j];
            }
        }

        top = 0;

        for(i = 1; i <= n+1; i++)
        {
            stack[top++] = p[i].area;
        }

        sort(stack, stack+top);
        printf("%d", stack[0]);
        for(i = 1; i < top; i++)
            printf(" %d", stack[i]);
        puts("");







    }
}
