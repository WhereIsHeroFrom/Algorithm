#include <iostream>

using namespace std;

int n, i;
double sum;

int main()
{
    while(scanf("%d", &n) != EOF)
    {
        sum = 1;
        for(i = 1; i < n / 2; i++)
        {
            sum *= (n - 2*i) * 1.0 / (n - 2*i + 1);
        }
        printf("%.5f\n", sum);

    }
}
