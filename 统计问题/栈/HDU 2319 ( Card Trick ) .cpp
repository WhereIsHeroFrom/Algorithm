#include <iostream>
using namespace std;

int t;
int n, i, j;
int stack[100000];
int sor[100], top;
int fro, end;

int main()
{
    scanf("%d", &t);

    while(t--)
    {
        scanf("%d", &n);
        top = 0;
        for(i = 1; i <= n; i++)
            stack[i] = i;

        fro = 1;
        end = n + 1;

        for(i = 1; i <= n; i++)
        {
            for(j = 1; j <= i; j++)
            {
                stack[end ++] = stack[fro++];
            }

            sor[stack[fro ++] - 1] = i;
        }

        for(i = 0; i < n; i++)
        {
            if(i) printf(" ");
            printf("%d", sor[i]);
        }
        puts("");
    }
}

