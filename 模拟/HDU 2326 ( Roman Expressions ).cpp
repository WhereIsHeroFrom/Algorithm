#include <iostream>

using namespace std;
char buf[100001];
int top = 0;
void NumToRoman(int num)
{
    int i, coun;
    top = 0;
    if(num == 0)
    {
        buf[0] = 'O';
        buf[1] = '\0';
        return;
    }
    if(num >= 1000)
    {
        coun = num / 1000;
        for(i = 0; i < coun; i++)
            buf[ top++ ] = 'M';
        num %= 1000;
    }

    if(num >= 900)
    {
        buf[top++] = 'C';
        buf[top++] = 'M';
        num -= 900;
    }

    if(num >= 500)
    {
        buf[top++] = 'D';
        num -= 500;
    }

    if(num >= 400)
    {
        buf[top++] = 'C';
        buf[top++] = 'D';
        num -= 400;
    }

    if(num >= 100)
    {
        coun = num / 100;
        for(i = 0; i < coun; i++)
            buf[ top++ ] = 'C';
        num %= 100;
    }

    if(num >= 90)
    {
        buf[top++] = 'X';
        buf[top++] = 'C';
        num -= 90;
    }

    if(num >= 50)
    {
        buf[top++] = 'L';
        num -= 50;
    }

    if(num >= 40)
    {
        buf[top++] = 'X';
        buf[top++] = 'L';
        num-= 40;
    }

    if(num >= 10)
    {
        coun = num / 10;
        for(i = 0; i < coun; i++)
            buf[top++] = 'X';
        num %= 10;
    }

    if(num >= 9)
    {
        buf[top++] = 'I';
        buf[top++] = 'X';
        num -= 9;
    }

    if(num  >= 5)
    {
        buf[top++] = 'V';
        num -= 5;
    }

    if(num >= 4)
    {
        buf[top++] = 'I';
        buf[top++] = 'V';
        num -= 4;
    }

    for(i = 0; i < num; i++)
        buf[top++] = 'I';
    buf[top] = '\0';
}

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
char ch[100001];
char bu[100001];
int hash[11];
int main()
{
    int i, j;
    for(i = 0; i < 10; i++)
        hash[i] = INT_MAX;
    while(scanf("%s", ch) != EOF)
    {
        if(strcmp(ch, "RESET") == 0)
        {
            printf("Ready\n");
            for(i = 0; i < 10; i++)
                hash[i] = INT_MAX;
        }else if(strcmp(ch, "QUIT") == 0)
        {
            printf("Bye\n");
            break;
        }else
        {
            int zong = 0;
            int len = strlen(ch);
            int start = 2;
            int sign = 1;
            int top;
            int error = 0;
            for(i = 2; i <= len; i++)
            {
                if(ch[i] == '+' || ch[i] == '-' || ch[i] == '\0')
                {
                    top = 0;
                    for(j = start; j < i; j++)
                    {
                        bu[top++] = ch[j];
                    }
                    bu[top] = '\0';
                    start = i + 1;

                    if(bu[0] >= '0' && bu[0] <= '9')
                    {
                        if( hash[ bu[0] - '0'] == INT_MAX)
                        {
                            error = 1;
                            break;
                        }else
                        {
                            zong +=  sign*hash[ bu[0] - '0'];
                        }
                    }else
                    {
                        zong += sign*RomanToNum(bu);
                    }

                    if(ch[i] == '+')
                        sign = 1;
                    else
                        sign = -1;
                }
            }
            if(zong > 10000 || zong < 0)
                    error = 1;
            if(error)
                printf("Error\n");
            else
            {
                NumToRoman(zong);
                hash[ch[0] - '0'] = zong;
                printf("%c=%s\n", ch[0], buf);
            }
        }
    }
    return 0;

}
