#include <iostream>

using namespace std;

struct point {
    int hp;
    int str;
    int spd;
}f[2];

int t;
char str[2][100];

void rt(int u) {

    int len = strlen( str[u] );
    int tmp = 0;
    int i, j;
    f[u].hp = 300;

    for(i = 0; i < len; i++) {
        tmp += (83 - str[u][i]) * (83 - str[u][i]);
        tmp %= 97;
    }
    f[u].hp -= tmp;

    f[u].str = 22;
    tmp = 1;
    for(i = 0; i < len; i++) {
        tmp *= (int)str[u][i];
        tmp %= 79;
    }
    f[u].str += tmp;

    tmp = 0;
    for(i = 0; i < len; i++) {
        for(j = i+1; j < len; j++) {
            tmp += str[u][i] * str[u][j];
            tmp %= 11;
        }
    }
    f[u].spd = tmp;
}
int main() {
    int i;
    scanf("%d", &t);

    while(t--) {
        for(i = 0; i < 2; i++) {
            scanf("%s", str[i]);
            rt(i);
        }

        for(i = 1; ; i ++) {
            if(i % (20 - f[0].spd) == 0)
                f[1].hp -= f[0].str;
            if(i % (20 - f[1].spd) == 0)
                f[0].hp -= f[1].str;
            if(f[0].hp <= 0 || f[1].hp <= 0)
                break;
        }

        if(f[0].hp <= 0 && f[1].hp <= 0)
            printf("tie\n");
        else if(f[0].hp <= 0) 
            printf("lose\n");
        else
            printf("win\n");
    }

}
