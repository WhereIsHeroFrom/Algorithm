#include <iostream>
using namespace std;

int n, w, d, sum, buf;
int i;

int main()
{
    while(scanf("%d %d %d %d", &n, &w, &d, &buf) != EOF)
    {
        sum = 0;
        for(i = 1; i < n; i++)
        {
            sum += i*w;
        }

        for(i = 1; i < n; i++)
        {
            if(sum - i*w + i*(w-d) == buf)
                break;
        }

        printf("%d\n", i);
    }
    return 0;
}

