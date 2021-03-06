#include <iostream>

using namespace std;

char str1[100], str2[100];
__int64 sum;
int len;


__int64 power(__int64 x, int y)
{
    int i;
    __int64 su = 1;
    for(i = 0; i < y; i++)
        su *= x;
    return su;
}

void dfs(int index)
{
    int i;
    if(str1[index] == '?')
    {
        int coun = 0;
        for(i = index + 1; i < len; i++)
        {
            if(str1[i] == '?')
                coun ++;
        }
        sum += (9 - str2[index] + '0') * power(10, coun);
        if(index < len - 1)
            dfs(index+1);
    }else 
    {
        if(str1[index] > str2[index])
        {
            int coun = 0;
            for(i = index + 1; i < len; i++)
            {
                if(str1[i] == '?')
                    coun ++;
            }
            sum += power(10, coun);
        }else if(str1[index] == str2[index])
        {
            if(index < len - 1)
               dfs(index+1);
        }
    }

}
int main()
{
    while(scanf("%s", str1) != EOF)
    {
        sum = 0;
        len = strlen(str1);
        if(strcmp(str1, "#") == 0)
            break;
        scanf("%s", str2);

        dfs(0);
        printf("%I64d\n", sum );
    }
}
