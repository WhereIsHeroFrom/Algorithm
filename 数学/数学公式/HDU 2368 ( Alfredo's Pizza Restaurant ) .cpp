#include <iostream>
#include <cmath>
using namespace std;

int c = 1;
int r, w, l;
int main()
{
    while(scanf("%d%d%d", &r, &w, &l) != EOF)
    {
        if(!r)
            break;
        double t = sqrt(1.0*w*w + 1.0*l*l)/2.0;
        if(t <= r)
        {
            printf("Pizza %d fits on the table.\n", c++);
        }else
            printf("Pizza %d does not fit on the table.\n", c++);
    }
    return 0;
}








