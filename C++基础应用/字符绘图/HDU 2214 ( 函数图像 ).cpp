#include <iostream>
#include <cmath>
using namespace std;

int n, c = 1, i, j, dp, sum, s, hp;
char map[1000][1000], ch[1000];
int main()
{
    //printf("%d\n", strlen("-----------------------------.+------------------------------>"));
    while(scanf("%d", &n) != EOF)
    {
        memset(map, '\0', sizeof(map));
        for(i = 0; i <= 656; i++)
            for(j = 0; j <= 566; j++)
                map[i][j] = ' ';

        printf("Case:%d\n", c++);

        
        for(i = 0; i <= 60; i++)
            map[30][i] = '-';
        for(i = 0; i <= 60; i++)
            map[i][30] = '|';

        map[30][61] = '>';
        map[31][61] = 'x';

        map[30][30] = '+';


        for(i = 0; i < n; i++)
        {
            scanf("%s", ch);
            for(s = -30 ; s <= 30; s++)
            {
                sum = 0;
                for(j = 0; j < strlen(ch); j++)
                {
                    if(ch[j] == 'x')
                    {
         //?????°??μ??μêy
                        if(j == 2)
                            dp = 1;
                        else if(j == 3)
                        {
                            if(ch[j-1] >= '0' && ch[j-1] <= '9')
                                dp = ch[j-1] - '0';
                            else if(ch[j-1] == '-')
                                dp = -1;
                            else
                                dp = 1;
                        }else if(j >= 4)
                        {
                            if(ch[j-1] >= '0' && ch[j-1] <= '9')
                                dp = ch[j-1] - '0';
                            else 
                                dp = 1;
                            if(ch[j-1] == '-')
                                dp = -1;
                            if(ch[j-2] == '-')
                                dp = -dp;
                        }


                        if(ch[j+1] == '^')
                        {
                             hp = ch[j+2] - '0';
                        }else
                             hp = 1;
                        
                        sum +=  pow(1.0*s, 1.0*hp)*dp;
                    }
                    if(ch[j] >= '0' && ch[j] <= '9' && ch[j+1] != 'x' && ch[j-1] != '^')
                    {
                        hp = 0;
                        dp = ch[j] - '0';
                        if(ch[j-1] == '-')
                            dp = -dp;
                        
                        sum +=  (int)pow(1.0*s, 1.0*hp)*dp;
                    }            
                }
            //    if(s == 2)
            //        printf("%d\n", sum);

                sum = 30 - sum;
                if(sum >= 0 && sum <= 60)
                {
                    int tp = s + 30;

                    if(map[sum][tp] == '|' || map[sum][tp] == '-' || map[sum][tp] == '+' || map[sum][tp] == '.')  
                        map[sum][tp] = '.';
                    else if(map[sum][tp] >= 'a' && map[sum][tp] <= 'z')
                        map[sum][tp] = '.';
                    else  
                        map[sum][tp] = 'a' + i;

                }
            }
        }
        for(i = 0; i < 29; i++)
            printf(" ");
        printf("y^");
        for(i = 0; i < 30; i++)
            printf(" ");
        puts("");
        for(i = 0; i <= 60; i++)
        {
            for(j = 0; j <= 61; j++)
            {
                if(i != 30 && i != 31 && j == 61)
                    break;
                printf("%c", map[i][j]);
            }
            printf("\n");
        }


    }
}
