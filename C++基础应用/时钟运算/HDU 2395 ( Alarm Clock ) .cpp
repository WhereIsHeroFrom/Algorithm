#include <iostream>

using namespace std;


struct point
{
    int hour;
    int onem;
    int tenm;
    char rt[20];
    int buf;
    int ap;
}p[20];

int t, i;
char buf[10];
int temp;

int Min(int a, int b){
    return a < b ? a : b;
}
int sum;

int main()
{
    scanf("%d", &t);

    while(t--)
    {
        sum = 0;
        for(i = 0; i < 2; i++)
        {
            scanf("%s", p[i].rt);
            sscanf(p[i].rt, "%d:%d%s", &p[i].hour, &p[i].buf, buf);
            p[i].onem = p[i].buf % 10;
            p[i].tenm = p[i].buf / 10;
            p[i].hour = p[i].hour;

            if(strcmp( buf, "pm" ) == 0)
                p[i].ap = 1;
            else
                p[i].ap = 0;
        }

        if(p[0].hour > p[1].hour)
        {
            temp = p[0].hour;
            p[0].hour = p[1].hour;
            p[1].hour = temp;
        }

        if(p[0].onem > p[1].onem)
        {
            temp = p[0].onem;
            p[0].onem = p[1].onem;
            p[1].onem = temp;
        }

        if(p[0].tenm > p[1].tenm)
        {
            temp = p[0].tenm;
            p[0].tenm = p[1].tenm;
            p[1].tenm = temp;
        }

        sum += Min(p[1].hour - p[0].hour, 12 + p[0].hour - p[1].hour);
        sum += Min(p[1].onem - p[0].onem, 10 + p[0].onem - p[1].onem);
        sum += Min(p[1].tenm - p[0].tenm, 6 + p[0].tenm - p[1].tenm);
        sum += (p[0].ap ^ p[1].ap);

        if(sum == 1)
            printf("Going from %s to %s requires 1 push.\n", p[0].rt, p[1].rt );
        else
        {
            printf("Going from %s to %s requires %d pushes.\n", p[0].rt, p[1].rt, sum);
        }


    }
}

