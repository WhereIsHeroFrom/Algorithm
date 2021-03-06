#include <iostream>
#include <cmath>
using namespace std;

struct point
{
    int basket[3];
    int step;
    int fro;
}temp, tt;
point q[1000001];
point stack[10000];
int top;

int front, end;
bool hash[61][61][61];

void hash_it(point t)
{
    hash[t.basket[0]][t.basket[1]][t.basket[2]] = 1;
    hash[t.basket[0]][t.basket[2]][t.basket[1]] = 1;
    
    hash[t.basket[1]][t.basket[0]][t.basket[2]] = 1;
    hash[t.basket[1]][t.basket[2]][t.basket[0]] = 1;
    
    hash[t.basket[2]][t.basket[0]][t.basket[1]] = 1;
    hash[t.basket[2]][t.basket[1]][t.basket[0]] = 1;
}

int main()
{
    int i, j;
    while(scanf("%d %d %d", &temp.basket[0], &temp.basket[1], &temp.basket[2]) != EOF)
    {
        memset(hash, 0, sizeof(hash));

        hash_it(temp);
        front = end = 0;
        temp.step = 0;
        temp.fro = -1;
        q[end++] = temp;
        point buf = temp;
        while(front < end)
        {
            temp = q[front++];
            
            if(temp.basket[0] == temp.basket[1] && temp.basket[1] == temp.basket[2])
            {
                buf = temp;
                break;
            }

            for(i = 0; i < 3; i++)
            {
                for(j = 0; j < 3; j++)
                {
                    if(i == j) continue;

                    tt = temp;    
                    tt.fro = front - 1;
                    tt.step ++;

                    if(temp.basket[i] >= temp.basket[j])
                    {
                        
                        int cha = temp.basket[j];
                        tt.basket[i] -= cha;
                        tt.basket[j] += cha;
                        if(!hash[tt.basket[0]][tt.basket[1]][tt.basket[2]])
                        {
                            hash_it(tt);
                            q[end++] = tt;
                        }
                    }
                }
            }
        }

        top = 0;
        temp = buf;
        while(temp.fro != -1)
        {
            stack[top++] = temp;
            temp = q[temp.fro];
        }
        stack[top++] = temp;

    
        for(i = top - 1; i >= 0; i--)
        {
            printf("%4d%4d%4d\n", stack[i].basket[0], stack[i].basket[1], stack[i].basket[2]);
        }
        for(i = 0; i < 12; i++)
            printf("=");
        puts("");
    }
}
