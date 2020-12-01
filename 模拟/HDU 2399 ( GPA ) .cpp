/*#include <iostream>
#include <cmath>
using namespace std;

double a, b, c;

int main()
{
    while(scanf("%lf %lf %lf", &a, &b, &c) != EOF){
        double buf = c / a;
        buf = log(buf) / log(1 + b / 100);
        printf("%d\n", int(buf) == buf ? (int)buf : (int)buf + 1);
    }
    return 0;
}*/
/*
#include <iostream>

using namespace std;

int a, b;
int main()
{
    while(scanf("%d %d", &a, &b) != EOF)
    {
        if(!a && !b)
            break;
        printf("%d\n", a +b);
    }
}*/

#include <iostream>

using namespace std;

char str[1000];
int hash[10000];

int main()
{
    int sum, coun;

    while(gets(str)){
        sum = coun = 0;

        int flag = 0;

        for(int i = 0; str[i]; i++){
            if(str[i] == ' ')
                continue;

            coun ++;
            if(str[i] == 'A' )
                sum += 4;
            else if(str[i] == 'B' )
                sum += 3;
            else if(str[i] == 'C' )
                sum += 2;
            else if(str[i] == 'D' )
                sum += 1;
            else if(str[i] == 'F')
                sum += 0;
            else
            {
                flag = 1;
            }
        }

        if(flag)
            puts("Unknown letter grade in input");
        else
        {
            printf("%.2lf\n", sum / 1.0 / coun);
        }

    }
}

