#include <iostream>

using namespace std;

struct point {
    char str[210];
    int len;
}p[4001], buf[40001], pro[40001];

int buft, prot;

int cmp1(const void *a, const void *b) {
    point *c = (point *)a;
    point *d = (point *)b;
    return c->len - d->len;
}

int cmp2(const void *a, const void *b) {
    point *c = (point *)a;
    point *d = (point *)b;
    if(c->len == d->len)
        return strcmp( c->str, d->str );
    return - c->len + d->len;
}

void  Gernerate(char *str) {
    int i, j;
    buft = 0;
    int len = strlen( str );
    char rt[210];

    for(i = 0; i < len; i++) {
        for(j = i; j < len; j++) {
            rt[j-i] = str[j];
            rt[j-i+1] = '\0';
            strcpy(buf[ buft ].str, rt);
            buf[ buft ].len = j - i + 1;
            buft ++;
        }
    }
    qsort( buf, buft, sizeof(point), cmp2);
}

int MySubString(char *a, int lena, char *b, int lenb) {
    int i, j;
    for(i = 0; i < lenb; i++) {
        for(j = 0; j < lena; j++) {
            if(b[i+j] != a[j])
                break;
        }
        if(j == lena)
            return 1;
    }
    return 0;
}

int n;
int main() {

    int i, j;
    while(scanf("%d", &n) != EOF && n) {
        
        for(i = 0; i < n; i++) {
            scanf("%s", &p[i].str);
            p[i].len = strlen(p[i].str);
        }

        qsort(p, n, sizeof(point), cmp1);
        Gernerate(p[0].str);
        prot = 1;

        pro[0] = buf[0];
        for(i = 1; i < buft; i++) {
            if(strcmp( buf[i].str, buf[i-1].str ) == 0)
                continue;
            pro[ prot++ ] = buf[i];
        }

        for(i = 0; i < prot; i++) {
            for(j = 0; j < n; j++) {
                if( !MySubString(pro[i].str, pro[i].len, p[j].str, p[j].len) )
                    break;
            }
            if(j == n) {
                printf("%s\n", pro[i].str);
                break;
            }
        }

        if(i == prot)
            printf("IDENTITY LOST\n");
    }
}
