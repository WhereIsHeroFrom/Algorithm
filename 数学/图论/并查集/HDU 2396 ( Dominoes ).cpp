#include <iostream>

using namespace std;

int deg[100];
int hash[100];
int pre[1000];


int find(int key){
    while(key != pre[ key ]){
        key = pre[ key ];
    }
    return key;
}

void union_(int s1, int s2){
    
    int p1 = find(s1);
    int p2 = find(s2);
    if( p1 == p2 )
        return ;

    pre[ p1 ] = p2;
}

int n, i, x, y;

int main(){

    int cas = 1;
    while(scanf("%d", &n) != EOF && n)
    {
        memset(deg, 0, sizeof(deg));
        memset(hash, 0, sizeof(hash));

        for(i = 1; i < n; i++)
            pre[i] = i;

        for(i = 0; i < n; i++){
            scanf("%d %d", &x, &y);
            deg[x] ++;
            deg[y] ++;
            hash[x] = hash[y] = 1;
            union_(x, y);
        }

        for(i = 1; i <= n; i++){
            if(deg[i] & 1)
                break;
        }

        printf("Set #%d: ", cas++);

        if(i <= n)
            puts("NO");
        else
        {
            for(i = 1; i <= n; i++){
                if(hash[i])
                    break;
            }

            int st = i;

            for(i = 1; i <= n; i++)
            {
                if(hash[i] && find(i) != find(st))
                    break;
            }

            if(i <= n)
                puts("NO");
            else
                puts("YES");
        }
    }
}

