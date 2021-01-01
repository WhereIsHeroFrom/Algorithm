#include <stdio.h>
#include <math.h>
int a, b, temp, i;
int moto(int b)
{
    return (int)(b*(sqrt(5.0) - 1)/2);
}
int main()
{
    while(scanf("%d%d", &a, &b)!=EOF){
        if(!a && !b)break;
        if(a > b){
            temp = a; a = b; b = temp;
        }
        if(moto(b) == a){
            printf("0\n");
        }else{
            printf("1\n");
            for(i = 0;i < 1000000; i++)
                if(moto(b - i) == (a-i))
                    break;
            if(i != 1000000)
                printf("%d %d\n", a-i, b-i);
            printf("%d %d\n",moto(a), a);
       }
}
}
