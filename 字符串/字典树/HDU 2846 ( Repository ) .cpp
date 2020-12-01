#include <iostream>

using namespace std;


struct trie {

    int color;
    int Num;
    trie *next[26];
    void Init() {
        int i;
        for(i = 0; i < 26; i++) {
            next[i] = NULL;
        }
        color = 0;
        Num = 0;
    }
} *root ;

char str[ 30 ];
int flag;
int T;

void Insert( char *str ) {
    int p = 0;

    trie *now;
    now = root;
    while( str[p] ) {
        char c = str[p] - 'a';
        
        if( !now->next[c] ) {
            now->next[c] = new trie;
            now->next[c]->Init();
        }
        now = now->next[c];
        if( now->Num < T )
            now->color ++;
        now->Num = T;
        p++;
    }
}

int find( trie * It, char *str ) {
    int p = 0;

    while( str[p] ) {
        char c = str[p] - 'a';

        if( !It->next[c] )
            return 0;
        It = It->next[c];
        p++;
    }
    return It->color;
}


int m, n;

int main() {

    int i, j;
    trie *now;

    root = new trie;
    root->Init();

    while( scanf("%d", &n) != EOF ) {

        T = 1;
        for(i = 0; i < n; i++) {
            T ++;
            scanf("%s", str);
            flag = 0;
            for( j = 0; str[j]; j++) {
                Insert( &str[j] );
            }
        }

        int ans = 0;
        scanf("%d", &m);
        for(i = 0; i < m; i++) {
            scanf("%s", str);
            now = root;
            printf("%d\n", find(now, str) );
        }
    }
    return 0;
}

/*
1
aabb

2
abb
a

*/

