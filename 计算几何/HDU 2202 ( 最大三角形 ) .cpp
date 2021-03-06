//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                     ???? ??????????(??????????)                                            ////
////        ???? : ???????????(???????????????????),?????????,??????,??????????????.             ////
////        ??? : ?????n???,??????????2??,???????????????�?????sta[]??,????????????????point[]???????    ////
////        ??????? : 2007-4-21     by xhd                                                                       ////
////                                                                                                      by  xhd ////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#define pi acos(-1.0)
using namespace std;

typedef double pointper;       //????????????

#define POINTNUM 50005       //???????????
#define PREX    1e-11       //?????????????????
  
struct node
{
    pointper x,y;
}P[100001];

class Polygon
{
public:
    int sta[POINTNUM];      //???????????�?
    node point[POINTNUM];
    bool flag[POINTNUM];
    int top,n,stab;            //n?????????????,top-1????????????,0 -- top-2??????????????,top-1??0?????????????.
    pointper x1,y1,x2,y2;
    Polygon(){top = n = 0;}
    static bool cmp(const node & A,const node & B){ return A.x < B.x || A.x == B.x && A.y < B.y;}
    bool X(int x1,int y1,int x2,int y2,bool f)                       //f?true????????????????
    { 
        if(f)
            return x1 * y2 - x2 * y1 >= 0;
        return x1 * y2 - x2 * y1 > 0;
    }
    bool X(double x1,double y1,double x2,double y2,bool f)           //f?true????????????????
    { 
        if(f)
            return x1 * y2 - x2 * y1 > 0.0 || fabs(x1 * y2 - x2 * y1) < PREX;
        return x1 * y2 - x2 * y1 > 0.0;
    }
    void pointselect(bool f);           //?????????,f?true????????????????*
    void getpoint(int i,bool f);
    void XY(int i);
    double length();                    //*
    double Area();                        //*
    bool IsInPoly(int x,int y,bool f);        //f?true??????????????*
    bool IsInPoly(double x,double y,bool f);  //f?true??????????????*
};

Polygon Tubao;

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

double dis(node a, node b) {
    return sqrt( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );
}

double Area(node a, node b, node c)
{
    double ab = dis(a, b);
    double ac = dis(a, c);
    double bc = dis(b, c);
    double p = (ab+bc+ac)/2;
    double S = p*(p-ab)*(p-ac)*(p-bc);
    return S;
}

int main()
{

    int n, i, j;
    int low, high, lm, rm;


    while( scanf("%d", &n) != EOF  && n != -1 ){
        double Max = 0;
        for(i = 0; i < n; i++){
            scanf("%lf %lf", &Tubao.point[i].x, &Tubao.point[i].y);
        }
        Tubao.n = n;
        Tubao.pointselect(false);
        
        //???????????????????P??????
        int top = 0;
        for(i = 0; i < Tubao.top - 1; i++) {
            P[top++] = Tubao.point[ Tubao.sta[i] ];
        }
        for(i = 0; i < top; i++) {
            //printf("%.2lf %.2lf\n", P[i].x,    P[i].y);
            P[top + i] = P[i];
        }

        //???????�??
        for(i = 0; i < top; i++) {
            for(j = i + 1; j < top; j++) {
                // ????i+1 ?? j-1??????????????????
                low = i+1;
                high = j-1;

                while(low <= high) {
                    lm = ( 2 * low + high ) / 3;
                    rm = ( low + 2 * high ) / 3;
                    double A = Area(P[i], P[j], P[lm]);
                    double B = Area(P[i], P[j], P[rm]);
                    
                    if(A > Max)
                        Max = A;
                    if(B > Max)
                        Max = B;

                    if(A < B)
                        low = lm + 1;
                    else
                        high = rm - 1;
                }
                // ????j+1 ?? i-1+top?????????????????
                /*low = j+1;
                high = i-1+top;

                while(low <= high) {
                    lm = ( 2 * low + high ) / 3;
                    rm = ( low + 2 * high ) / 3;
                    double A = Area(P[i], P[j], P[lm]);
                    double B = Area(P[i], P[j], P[rm]);
                    
                    if(A > Max)
                        Max = A;
                    if(B > Max)
                        Max = B;

                    if(A < B)
                        low = lm + 1;
                    else
                        high = rm - 1;
                }*/
            }
        }

        printf("%.2lf\n", sqrt(Max) );
    }
    return 0;
}

/*
4
1 0
1 1
0 1
0 0
*/
