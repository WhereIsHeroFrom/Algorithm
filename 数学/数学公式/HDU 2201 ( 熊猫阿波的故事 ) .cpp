#include <iostream>
using namespace std;
double a, b;
int main()
{
    while(scanf("%lf%lf", &a, &b) != EOF)
    {
        printf("%.2lf\n", 1/a);
    }
}
