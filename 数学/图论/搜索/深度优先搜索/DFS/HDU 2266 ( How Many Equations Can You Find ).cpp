#include <iostream>

using namespace std;

__int64 stack[100], top;

// i = 0; ' '
// i = 1; '+'
// i = 2; '-'

__int64 cal(__int64 a, char c, __int64 b){
    if(c == '+')
        return a + b;
    if(c == '-')
        return a - b;
}

struct Stack {
    __int64 a[16];
    int index[16];
    int top;
}Num, Ope, Buf;

__int64 a;
char str[100];
int coun = 0;
int len;
int hash[14];

void dfs(int depth){

    int i, j;

    if(depth == len - 1) {

        Num.top = Ope.top = 0;
        memset(hash, 0, sizeof(hash));

        for(i = 0; i < top ;i++) {
            if(stack[ i ] == 0){
                Ope.a[ Ope.top++ ] = '+';
                if(!hash[i])
                    Num.a[ Num.top++ ] = (__int64)(str[i] - '0');
                if(i == top - 1)
                    Num.a[ Num.top++ ] = (__int64)(str[i+1] - '0');
            }else if(stack[ i ] == 1){
                Ope.a[ Ope.top++ ] = '-';
                if(!hash[i])
                    Num.a[ Num.top++ ] = (__int64)(str[i] - '0');
                
                if(i == top - 1)
                    Num.a[ Num.top++ ] = (__int64)(str[i+1] - '0');
            }else {
                int start = i;

                while(i < top && stack[i] == 2)
                    i++;
                Num.a[ Num.top ] = 0;
                Num.index[ Num.top ] = start;
                for(j = start; j <= i; j++) {
                    Num.a[ Num.top ] = Num.a[ Num.top ] * 10 + (__int64)(str[j] - '0');
                    hash[j] = 1;
                }
                Num.top++;
                i--;
            }
        }

        /*printf("%I64d ", Num.a[ 0 ]);
        for(i = 1; i < Num.top; i++) {
            printf("%c %I64d ", (char)Ope.a[i-1], Num.a[i]);
        }
        puts("");
        */
        Buf = Num;

        for(i = 0; i < Ope.top; i++) {
            Num.a[i+1] = cal(Num.a[i], (char)Ope.a[i], Num.a[i+1]);
        }

        //printf("%I64d\n", Num.a[ Ope.top ]);
        if(Num.a[ Ope.top ] == a) {
            /*printf("%I64d ", Buf.a[ 0 ]);
            for(i = 1; i < Buf.top; i++) {
                    printf("%c %I64d ", (char)Ope.a[i-1], Buf.a[i]);
            }
            puts("");*/
            coun ++;
        }
        return;
    }            

    for(i = 0; i < 3; i ++) {
        stack[ top ++ ] = i;
        dfs(depth+1);
        top --;
    }
}
int main()
{
    while(scanf("%s %I64d", str, &a) != EOF){
        coun = 0;
        top = 0;
        len = strlen( str );
        dfs(0);
        printf("%d\n", coun);
    }
    return 0;
}
/*
123456789 3
21 1
*/
