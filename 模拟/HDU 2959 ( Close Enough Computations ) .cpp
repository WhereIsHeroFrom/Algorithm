#include <iostream>

using namespace std;

int round(int key)
{
    if(key % 10 > 4)
        return key / 10 + 1;
    return key / 10;
}
int main()
{
    int a, b, c, d, i, j, k, ii, jj, kk;

    while(scanf("%d %d %d %d", &a, &b, &c, &d) != EOF)
    {
        if(!a && !b && !c && !d)
            break;

        i = b * 10 - 5;
        if(i < 0)
            i = 0;


        j = c * 10 - 5;
        if(j < 0)
            j = 0;

        
        k = d * 10 - 5;
        if(k < 0)
            k = 0;


        ii = b * 10 + 5;
        jj = c * 10 + 5;
        kk = d * 10 + 5;

        int Min = i * 9 + j * 4 + k * 4;
        int Max = ii * 9 + jj * 4 + kk * 4;

        if(Min % 10 > 4)
            Min = ((Min / 10) + 1 );
        else
            Min = (Min / 10);

        if(Max % 10 > 4)
            Max = ((Max / 10) + 1);
        else
            Max = (Max / 10);

        printf("%s\n", Min <= a && a < Max ? "yes" : "no" );
    }
}

/*
250 12 31 5
250 13 31 5
122 10 10 0
0 0 0 0
*/
