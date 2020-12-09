#include <iostream>

using namespace std;
int n, a[1000];
int hash[10000];
int H[1000];
int stack[1000], top;
int main()
{
    int t;
    scanf("%d", &t);
    int i, j;
    while(t--)
    {
        top = 0;
        scanf("%d", &n);
        for(i = 0; i < n-2; i++)
        {
            scanf("%d", &a[i]);
        }
        memset(H, 0, sizeof(H));
        for(i = 0; i < n-2; i++)
        {
            memset(hash, 0, sizeof(hash));
            for(j = i; j < n-2; j ++)
            {
                hash[ a[j] ] = 1;
            }
            for(j = 1; ; j++)
            {
                if(!hash[j] && !H[j])
                    break;
            }
            stack[top++] = j;
            H[j] = 1;
        }
        printf("%d", stack[0]);
        for(i = 1; i < top; i++)
            printf(" %d", stack[i]);
        puts("");
    }
}
