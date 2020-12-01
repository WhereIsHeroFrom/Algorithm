//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                     　　 　　凸包模版(无需求极角)                                              ////
////        功能 : 求出凸包上的点(支持求边上的和不是边上的点),求凸包面积,凸包周长,判断点是否在凸包内.              ////
////        注意 : 须先将n赋值,点数需大于2个,求出的凸包的点的下标放在sta[]中,而不是凸包的点放在point[]中！！！      ////
////        最后修改 : 2007-4-21                                                                                  ////
////                                                                                                      by  xhd ////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

typedef double pointper;       //点坐标的类型

#define POINTNUM 50005       //最多点的个数
#define PREX    1e-11       //当点坐标为实数型时用

struct node
{
    pointper x,y;
};

class Polygon
{
public:
    int sta[POINTNUM];      //在凸包上点的下标
    node point[POINTNUM];
    bool flag[POINTNUM];
    int top,n,stab;            //n为读入的点的个数,top-1为凸包上点的个数,0 -- top-2是凸包上点的坐标,top-1和0存的都是第一个点.
    pointper x1,y1,x2,y2;
    Polygon(){top = n = 0;}
    static bool cmp(const node & A,const node & B){ return A.x < B.x || A.x == B.x && A.y < B.y;}
    bool X(int x1,int y1,int x2,int y2,bool f)                       //f为true表示求的包括边上的点
    { 
        if(f)
            return x1 * y2 - x2 * y1 >= 0;
        return x1 * y2 - x2 * y1 > 0;
    }
    bool X(double x1,double y1,double x2,double y2,bool f)           //f为true表示求的包括边上的点
    { 
        if(f)
            return x1 * y2 - x2 * y1 > 0.0 || fabs(x1 * y2 - x2 * y1) < PREX;
        return x1 * y2 - x2 * y1 > 0.0;
    }
    void pointselect(bool f);           //求凸包上的点,f为true表示求的包括边上的点*
    void getpoint(int i,bool f);
    void XY(int i);
    double length();                    //*
    double Area();                        //*
    bool IsInPoly(int x,int y,bool f);    //f为true表示点可以在边上*
    bool IsInPoly(double x,double y,bool f);  //f为true表示点可以在边上*
};

void Polygon::XY(int i)
{
    x1 = point[i].x-point[sta[top-2]].x;
    y1 = point[i].y-point[sta[top-2]].y;
    x2 = point[sta[top-1]].x-point[sta[top-2]].x;
    y2 = point[sta[top-1]].y-point[sta[top-2]].y;
}

void Polygon::getpoint(int i,bool f)
{
    XY(i);
    if(top == stab || X(x1,y1,x2,y2,f))
    {
        sta[top++] = i;
        flag[i] = false;
    }
    else
    {
        top--;
        flag[sta[top]] = true;
        XY(i);
        while(top > stab && !X(x1,y1,x2,y2,f))
        {
            top--;
            flag[sta[top]] = true;
            XY(i);
        }
        sta[top++] = i;
        flag[i] = false;
    }
}

void Polygon::pointselect(bool f)
{
    int i;
    memset(flag,true,n+1);
    sort(point,point+n,cmp);
    sta[0] = 0;
    sta[1] = 1;
    top = 2;
    flag[1] = false;
    stab = 1;
    for(i = 2;i < n;i++) getpoint(i,f);
    stab = top;
    for(i = n-2;i >= 0;i--) if(flag[i]) getpoint(i,f);
}

double Polygon::length()
{
    double s = 0.0;
    int i;
    for(i = 1;i < top;i++)
        s += sqrt(1.0*(point[sta[i]].x-point[sta[i-1]].x)*(point[sta[i]].x-point[sta[i-1]].x)
             + (point[sta[i]].y-point[sta[i-1]].y)*(point[sta[i]].y-point[sta[i-1]].y));
    return s;
}

double Polygon::Area()
{
    double s = 0.0;
    int i;
    for(i = 1;i < top;i++)
        s += point[sta[i-1]].x*point[sta[i]].y - point[sta[i]].x*point[sta[i-1]].y;
    return fabs(s/2);
}

bool Polygon::IsInPoly(int x,int y,bool f)
{
    int i;
    for(i = 1;i < top;i++)
        if(!X(x-point[sta[i-1]].x,y-point[sta[i-1]].y,point[sta[i]].x-point[sta[i-1]].x,
            point[sta[i]].y-point[sta[i-1]].y,f))
            return false;
    return true;
}

bool Polygon::IsInPoly(double x,double y,bool f)
{
    int i;
    for(i = 1;i < top;i++)
        if(!X(x-point[sta[i-1]].x,y-point[sta[i-1]].y,(double)point[sta[i]].x-point[sta[i-1]].x,
            (double)point[sta[i]].y-point[sta[i-1]].y,f))
            return false;
    return true;
}

int three(double d)
{
    if(fabs(d)<1e-6)return 0;
    else if(d>0)return 1;
    else return -1; 
}
double cross(node a, node b, node c)
{
   return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}

int between(node a, node b, node c)
{
    return (a.x-b.x)*(a.x-c.x)+(a.y-b.y)*(a.y-c.y);
}

int segcross(node a, node b, node c, node d)
{
    int d1,d2,d3,d4;
    double s1,s2,s3,s4;
    d1=three(s1=cross(a,b,c));
    d2=three(s2=cross(a,b,d));
    d3=three(s3=cross(c,d,a));
    d4=three(s4=cross(c,d,b));

    if(d1*d2==-1&&d3*d4==-1)return 1;

    if(d1==0&&between(c,a,b)<=0||
        d2==0&&between(d,a,b)<=0||
        d3==0&&between(a,c,d)<=0||
        d4==0&&between(b,c,d)<=0
        )return 2;
    return 0;
}

struct SimplePolygon
{
    node pol[20000];
    int top;
}poly[2];

node xx, yy, temp;
Polygon t[2];
int n[2];

bool intersect(SimplePolygon st, SimplePolygon en)
{
    int i, j;

    for(i = 0; i < st.top - 1; i++)
    {
        for(j = 0; j < en.top - 1; j++)
        {
            if(segcross(st.pol[i], st.pol[i+1], en.pol[j], en.pol[j+1]))
            {
                return 1;
            }
        }
    }
    return 0;
}

int main()
{

    int i, j;
    int c = 1;
    int tt = 0;
    while(scanf("%d %d", &n[0], &n[1]) != EOF)
    {
        if(!n[0] && !n[1]) break;

        if(tt)
            puts("");
        tt++;



        for(i = 0; i < 2; i++)
        {
            t[i].n = 0;
            for(j = 0; j < n[i]; j++)
            {
                scanf("%lf %lf %lf %lf", &xx.x, &xx.y, &yy.x, &yy.y);
                t[i].point[ t[i].n++ ] = xx;
                t[i].point[ t[i].n++ ] = yy;

                temp.x = xx.x;    xx.x = yy.x;    yy.x = temp.x;
                t[i].point[ t[i].n++ ] = xx;
                t[i].point[ t[i].n++ ] = yy;
            }
            t[i].pointselect(false);
            int ty = 0;
            poly[i].top = 0;
            for(j = 0; j < t[i].top; j++)
            {
                poly[i].pol[ty++] = t[i].point[ t[i].sta[j] ];
            }
            poly[i].top = ty;
        }

        printf("Case %d: ", c++);

        if(intersect(poly[0], poly[1]))
            printf("It is not possible to separate the two groups of vendors.\n");
        else
            printf("It is possible to separate the two groups of vendors.\n");


    }

}
