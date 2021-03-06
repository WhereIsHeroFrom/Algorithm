/*
    指针爬行 + KMP
*/

#include <iostream> 

using namespace std;

#define MAXN 1000010

char str[MAXN];
char S[MAXN*2], T[MAXN];
int next[MAXN]; 
int len;

void getNext(int m, char *str) {
    next[1] = 0;
    for(int j = 0, i = 2; i <= m; i++) {
        while(j>0 && str[i] != str[j+1]) j = next[j];
        if(str[i] == str[j+1]) j++;
        next[i] = j;
    }
}

int KMP(int m, char *T, int n, char *S) {
    int c = 0;
    for(int j = 0, i = 1; i < n; i++) {
        while( j>0 && S[i] != T[j+1]) j = next[j];
        if(S[i] == T[j+1]) j++;
        if(j == m) {
            c++;
            j = next[j];
            
        }
    }
    return c;
}


void process(int extrachar) {
    int i = 0, j = 1, k = 0; 
    while(i < len && j < len && k < len) {
        int pre = (i+k); if(pre >= len) pre -= len;
        int nex = (j+k); if(nex >= len) nex -= len;
        int sub = str[pre] - str[nex];
        if(!sub) {
            k++;
        }else {
            if(sub < 0) j += k + 1;
            else i += k + 1;
            if(i == j) j++;
            k = 0;
        }
    }
    int minidx;
    if(k == len) {
        // 所有字符都相等的情况 
        minidx = i<j?i:j;
    }else {
        minidx = (i>=len) ? j : i;
    }
    for(i = minidx; i < minidx + len; i++) {
        if(i < len)
            T[i-minidx+1] = str[ i ];
        else
            T[i-minidx+1] = str[ i - len];
    }
    T[i-minidx+1] = '\0';
    getNext(len, T);
    strcpy(&S[1], str);
    strcat(&S[1], str);
    printf("%d %d%c", minidx+1, KMP(len, T, len*2, S), extrachar);
}

int main() {
    int i;
    while ( scanf("%s", str) != EOF ) {
        /*for(i = 0; i < 1000000; i++) {
            str[i] = 'b';
        }
        str[i++] = 'a';
        str[i] = '\0';*/
        
        len = strlen(str);
        process(' ');
        for(i = 0; str[i]; i++) {
            str[i] = 25 - (str[i] - 'a') + 'a'; 
        }
        process('\n');
    }
    return 0;
}

