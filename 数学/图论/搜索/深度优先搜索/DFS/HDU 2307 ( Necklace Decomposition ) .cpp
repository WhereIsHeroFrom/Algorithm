#include <iostream>

using namespace std;
char str[111];
int stack[111];
int top, len, flag;
char buf[111];
char ty[211];
int hash[111];
int test(char *buf, int len)
{
    int i, j;
    char Min[111] = {'\0'};
    char cpu[111] = {'\0'};
    strcpy(ty, buf);
    strcat(ty, buf);
    for(i = 0; i < len; i++)
    {
        for(j = 0; j < len; j++)
        {
            cpu[j] = ty[i+j];
        }
        if(Min[0] == '\0' || strcmp(cpu, Min) < 0)
        {
            strcpy(Min, cpu);
        }
    }
    if(strcmp(Min, buf) == 0)
        return 1;
    return 0;
    
}
void dfs(int start, int end)
{
    int l = 0, i;
    if(start > end)
    {
        flag = 1;
        printf("(");
        for(i = 0; i < len; i++)
        {
            printf("%c", str[i]);
            if(hash[i] == 1)
            {
                printf(")");
            if(i != len-1)
                printf("(");
            }
        }
        puts("");
    }
    if(flag)
        return;
    for(i = start; i <= end; i++)
    {
        buf[l++] = str[i];
    }
    buf[l] = '\0';

    int tp = test(buf, l);
    if(tp == 1)
    {
        hash[end] = 1; 
        dfs(end+1, len - 1);
        hash[end] = 0;
    }
    if(flag)
        return;
    for(i = end - 1; i >= start; i--)
    {
        dfs(start, i);
    }
}
int t;
int main()
{
    scanf("%d", &t);
    while(t--)
    {
        scanf("%s", str);
        len = strlen(str);
        flag = 0;
        memset(hash, 0, sizeof(hash));
        dfs(0, len - 1);
    }
}
