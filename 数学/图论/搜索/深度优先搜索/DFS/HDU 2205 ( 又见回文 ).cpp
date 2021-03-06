#include <iostream>
using namespace std;
int Max;

void dfs(char *str ,char *ch, int lens, int lenc,  int s1, int e1, int s2, int e2)
{
    if(e1 - s1 + e2 - s2 + 2 > Max)
        Max = e1 - s1 + e2 - s2 + 2;
    if(s1 >= 1 && e1+1 < lens && str[s1-1] == str[e1+1])
        dfs(str, ch, lens, lenc, s1-1, e1+1, s2, e2);
    
    if(s1 >= 1 && e2+1 < lenc && str[s1-1] == ch[e2+1])
        dfs(str, ch, lens, lenc, s1-1, e1, s2, e2+1);

    if(s2 >= 1 && e2+1 < lenc && ch[s2-1] == ch[e2+1])
        dfs(str, ch, lens, lenc, s1, e1, s2-1, e2+1);

    if(s2 >= 1 && e1+1 < lens &&  ch[s2-1] == str[e1+1])
        dfs(str, ch, lens, lenc, s1, e1+1, s2-1, e2);
}

char ch1[100], ch2[100];
int main()
{
    int i, j;
    while(gets(ch1))
    {
        gets(ch2);
        int len1 = strlen(ch1);
        int len2 = strlen(ch2);
        Max = 0;
        for(i = 0; i < len1; i++)
        {
            for(j = 0;j < len2; j++)
            {
                   dfs(ch1, ch2, len1, len2, i, i, j, j-1);
                   dfs(ch2, ch1, len2, len1, j, j, i, i-1);
                   
                   if(ch1[i] == ch1[i+1])
                       dfs(ch1, ch2, len1, len2, i, i+1, j, j-1);
                   
                   if(ch2[j] == ch2[j+1])
                       dfs(ch2, ch1, len2, len1, j, j+1, i, i-1);

                   if(ch1[i] == ch2[j])
                       dfs(ch1, ch2, len1, len2, i, i, j, j);
            }
        }
        if(len2 == 0)
        {
          for(i = 0; i < len1; i++)
             dfs(ch1, ch2, len1, len2, i, i, 88, 87);
          for(i = 0; i < len1; i++)
             if(ch1[i] == ch1[i+1])
                    dfs(ch1, ch2, len1, len2, i, i+1, 88, 87);
        }
        if(len1 == 0)
        {
           for(i = 0; i < len2; i++)
              dfs(ch2, ch1, len2, len1, i, i, 88, 87);
           for(i = 0; i < len2; i++)
              if(ch2[i] == ch2[i+1])
                    dfs(ch2, ch1, len2, len1, i, i+1, 88, 87);
        }
        printf("%d\n", Max);
        memset(ch1, '\0', sizeof(ch1));
        memset(ch2, '\0', sizeof(ch2));
    }

}
