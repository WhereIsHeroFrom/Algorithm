#include <iostream>

using namespace std;

char ch[1000001];
int hash[300];
int coun;
int start, end;
int main()
{
    int n, i;
    while(scanf("%d", &n) != EOF && n)
    {
        getchar();
        gets(ch);
        int Max = 0;
        int  len = strlen(ch);
        memset(hash, 0, sizeof(hash));
        start = 0;
        end = 0;
        coun = 0;
        for(i = 0; i < len; i++)
        {
            end = i;
            if(!hash[ ch[end] ])
                coun++;    
            hash[ ch[end] ] ++;
            if(coun > n)
            {
                while(coun > n)
                {
                    hash[ ch[start] ] --;
                    start ++;
                    if(hash[ ch[start-1] ] == 0)
                        coun --;
                }
            }


            if(end - start + 1> Max)
                Max = end - start + 1;
        }
        printf("%d\n", Max);
    }
}
