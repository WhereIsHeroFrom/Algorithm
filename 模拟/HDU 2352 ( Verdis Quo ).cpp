#include <iostream>

using namespace std;
char *buf[100001];
/*char *NumToRoman()
{
}*/

int RomanToNum(char *Ro)
{
    int len = strlen(Ro);
    int i;
    int sum = 0;
    for(i = 0; i < len; i++)
    {
        if(Ro[i] == 'V') sum += 5;
        else if(Ro[i] == 'L') sum += 50;
        else if(Ro[i] == 'D') sum += 500;
        else if(Ro[i] == 'M') sum += 1000;
        
        if(Ro[i] == 'I')
        {
            if(Ro[i+1] == 'V') sum += 4, i++;
            else if(Ro[i+1] == 'X') sum += 9, i++;
            else sum += 1;
        }else if(Ro[i] == 'X')
        {
            if(Ro[i+1] == 'L') sum += 40, i++;
            else if(Ro[i+1] == 'C') sum += 90, i++;
            else sum += 10;
        }else if(Ro[i] == 'C')
        {
            if(Ro[i+1] == 'D') sum += 400, i++;
            else if(Ro[i+1] == 'M') sum += 900, i++;
            else sum += 100;
        }
    }
    return sum;
}
char ch[100000];
int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%s", ch);
        printf("%d\n", RomanToNum(ch));
    }

}
