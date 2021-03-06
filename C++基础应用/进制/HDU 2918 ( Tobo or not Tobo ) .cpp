#include <iostream>

using namespace std;

char rt[10][10] =
{
    "1111110",
    "0101000",
    "1011101",
    "1111001",
    "0101011",
    "1110011",
    "1110111",
    "1101000",
    "1111111",
    "1101011"
};

int deci[10];
int hash[1011];
char str[10000];
int i, j;
char er[1000];
int stack[100], top;

int main()
{
    for(i = 0; i < 10; i++)
    {
        int s = 1;
        for(j = 0; j < 7; j++)
        {
            deci[i] += s * (rt[i][j] - '0');
            s *= 2;
        }
        hash[ deci[i] ] = i;
    }

    while(scanf("%s", str) != EOF )
    {
        if(strcmp( str, "BYE") == 0)
            break;

        int len = strlen( str );
        for(i = 0; i < len; i++)
            if(str[i] == '+') break;

        int plu = i, sum1 = 0, sum2 = 0;

        for(i = 0; i < plu; i += 3)
        {
            int ty = (str[i] - '0') * 100 
                + (str[i+1] - '0') * 10
                + (str[i+2] - '0') * 1;
            sum1 = sum1 * 10 + hash[ ty ];
        }

        for(i = plu+1; i < len - 1; i += 3)
        {
            int ty = (str[i] - '0') * 100 
                + (str[i+1] - '0') * 10
                + str[i+2] - '0';
            sum2 = sum2 * 10 + hash[ ty ];
        }

        sum1 += sum2;

        printf("%s", str);

        top = 0;


        while(sum1)
        {
            stack[ top++ ] = sum1 % 10;
            sum1 /= 10;
        }

        for(i = top - 1; i >= 0; i--)
        {
            if(deci[ stack[i] ] >= 10 && deci[ stack[i] ] <= 99)
                printf("0%d", deci[ stack[i] ]);
            else
                printf("%d", deci[ stack[i] ] );
        }

        puts("");


    }

}
