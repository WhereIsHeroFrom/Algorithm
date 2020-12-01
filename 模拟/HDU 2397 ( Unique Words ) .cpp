#include <iostream>
using namespace std;

struct point
{
    char rt[100];
    int tp;
}p[80000];

int  top = 0;
char str[1000], buf[1000];

void Sleep()
{
    int i;
    int len = 0, u = 0;


    len = strlen( str );

    
    for(i = 0; i < len; i++){
        if( str[i] != 39 )
        {
            buf[u++] = str[i];
        }
    }


    buf[u] = '\0';

    strcpy(str, buf);


    for(i = 0; str[i] ; i++){
        if(str[i] >= 'a' && str[i] <= 'z')
            str[i] += (- 'a' + 'A');
    }

    len = strlen( str );
    
    int ty = 0;

    for(i = 0; i < len; i++)
    {
        if(str[i] >= 'A' && str[i] <= 'Z')
        {
            p[top].rt[ty++] = str[i];
        }else
        {

            if(ty == 0)
                continue;
            else
            {
                p[top].rt[ty] = '\0';
                ty = 0;
                top++;
            }
        }
    }    
    
    if(ty)
    {
        p[top].rt[ty] = '\0';
        ty = 0;
        top++;
    }
}

int cmp(const void *a, const void *b){
    point *c = (point *)a;
    point *d = (point *)b;

    return strcmp(c->rt, d->rt);
}

int t = 1;

void Process()
{
    printf("WORDS IN DOCUMENT #%d\n", t++);

    qsort(p, top, sizeof(point), cmp);

    puts( p[0].rt );

    for(int i = 1; i < top; i++)
    {
        if(strcmp( p[i].rt, p[i-1].rt) == 0)
            continue;
        puts( p[i].rt );
    }
}

char er[10000];

int main()
{
    top = 0;
    while( gets( er ) ){

        if( strcmp( er, "EOD" ) == 0 )
        {
            Process();
            top = 0;
        }else if( strcmp( er, "EOT" ) == 0 )
        {
            Process();
            break;
        }else
        {
            int i;
            int ty = 0;
            for( i = 0; er[i]; i++)
            {
                if(er[i] == ' ')
                {
                    str[ ty++ ] = '\0';
                    Sleep();
                    ty = 0;
                }else
                    str[ ty++ ] = er[i];
            }

            if(ty)
            {
                    str[ ty++ ] = '\0';
                    Sleep();
            }
                
        }
    }
    return 0;
}


