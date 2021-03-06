//HDU 2429 Word Game

#include <iostream>

using namespace std;
#define MAXN 30
struct Matrix {
    int Describe[MAXN][MAXN];
    int n;
}temp, tt;
int m, n;

void Mutiple(Matrix &c, Matrix a, Matrix &b) {
    int i, j, t;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            c.Describe[i][j] = 0;
            for(t = 0; t < n; t++) {
                c.Describe[i][j] += (a.Describe[i][t] * b.Describe[t][j]) ;
            }
            if(c.Describe[i][j] >= m)
                c.Describe[i][j] %= m;
        }
    }
}

void MatrixAdd(Matrix &c, Matrix &a, Matrix &b) {
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            c.Describe[i][j] = (a.Describe[i][j] + b.Describe[i][j]) % m;
}

void MatrixOutput(Matrix M, int x, int y, int n){
    int i, j;
    for(i = x; i < x+n; i++){
        for(j = y; j < y+n; j++){
            if(j == y)
                printf("%d", M.Describe[i][j]);
            else
                printf(" %d", M.Describe[i][j]);
        }
        printf("\n");
    }
}

Matrix CreatEMatrix(int n){
    Matrix c;
    int i, j;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(i == j)
              c.Describe[i][j] = 1;
            else
              c.Describe[i][j] = 0;
        }
    }
    c.n = n;
    return c;
}

void Matrix_K(Matrix &c, int n, int k) {
    Matrix AK;

    //递归
    if(k == 1) {
        c = temp;
        return ;
    }
    Matrix_K(AK, n, k/2);
    Mutiple(c, AK, AK);
    if(!(k & 1)) {
        return ;
    }else {
        Mutiple(c, c, temp);
        return ;
    }
    /*二进制
    Matrix tp;
    int i;
    c = CreatEMatrix(n);
    tp = temp;
    while(k) {
        if(k & 1) {
            Mutiple(AK, tp, c);
            c = AK;
        }
        Mutiple(AK, tp, tp);
        tp = AK;
        k >>= 1;
    }*/

} // calculate A^k

/*
void Matrix_K_Sum(Matrix &c, int n, int k) {
    Matrix rt;
    Matrix AK, AKS;
    if(k == 0) {
        c = CreatEMatrix(n);
        return ;
    }
    if(k == 1) {
        c = temp;
        return ;
    }
    if(!(k & 1) ) {
        Matrix_K_Sum(AKS, n, k / 2);   // AKS = S(k/2);
        Matrix_K(AK, n, k / 2);        // AK = A^(k/2);
        Mutiple(rt, AK, AKS);          // rt = A^(k/2) * S(k/2);
        MatrixAdd(c, AKS, rt);         // c = AKS + rt; [S(k) = S(k/2) + S(k/2) * A^(k/2)]
    }else {
        Matrix_K_Sum(AKS, n, k-1);       // AKS = S(k-1);
        Matrix_K(AK, n, k);            // AK = A^(k);
        MatrixAdd(c, AKS, AK);         // c = AKS + AK; [S(k) = S(k-1) + A^k]
    }
} // calculate S(k) = A^1 + A^2 + A^3 + ...... + A^k
*/



void Matrix_K_Sum(Matrix &c, int n, int k) {

    Matrix rt;
    Matrix AK, AKS;
    if(k == 0) {
        c = CreatEMatrix(n);
        return ;
    }
    if(k == 1) {
        c = temp;
        return ;
    }

    if((k / 2) & 1) {
        Matrix_K_Sum(AKS, n, k / 2);   // AKS = S(k/2);
        Matrix_K(AK, n, (k+1) / 2);    // AK = A^((k+1)/2);
        Mutiple(rt, AK, AKS);          // rt = A^((k+1)/2) * S(k/2);
        MatrixAdd(c, AKS, rt);         // c = AKS + rt; [S(k) = S(k/2) + S(k/2) * A^((k+1)/2)]

    }else {
        Matrix_K_Sum(AKS, n, k-2);       // AKS = S(k-2);
        Matrix_K(AK, n, k);            // AK = A^(k);
        MatrixAdd(c, AKS, AK);         // c = AKS + AK; [S(k) = S(k-2) + A^k]
        
    }
} // calculate S(k) = A^1 + A^3 + A^5 ...... + A^k

char str[100][100];
char st[100], en[100];
int u, v;

int main(){

    m = 10001;
    Matrix T;
    int t, k;
    int i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);

        for(i = 0; i < n; i++) {
            scanf("%s", str[i]);
        }

        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                T.Describe[i][j] = 0;
            }
        }

        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                if(str[i][strlen(str[i])-1] == str[j][0])
                    T.Describe[i][j] = 1;
                if(str[j][strlen(str[j])-1] == str[i][0])
                    T.Describe[j][i] = 1;
            }
        }

        scanf("%s %s", st, en);

        for(i = 0; i < n; i++) {
            if(strcmp(str[i], st) == 0)
                u = i;
            if(strcmp(str[i], en) == 0)
                v = i;
        }

        scanf("%d", &k);

        if(k % 2 == 0)
            k --;

        temp = T;
        Matrix_K_Sum(T, n, k);

        printf("%d\n", T.Describe[u][v]);
    }
}
