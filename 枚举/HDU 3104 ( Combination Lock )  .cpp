#include <iostream>

using namespace std;

int N, T[3];

int goc(int cc, int start, int end) {
    if(cc) {
        if(start < end) {
            return end - start;
        }else {
            return N - start + end;
        }
    }else {
        if(start < end) {
            return N - end + start;
        }else {
            return start - end;
        }
    }
}
int main() {
    int i;
    while(scanf("%d", &N) != EOF) {
        int s = N;
        for(i = 0; i < 3; ++i) {
            scanf("%d", &T[i]);
            s += T[i];
        }
        if(!s) break;
        int ans = 0;
        for(i = 0; i < N; ++i) {
            int nans = 3*N;
            nans += goc(0, i, T[0]);
            nans += goc(1, T[0], T[1]);
            nans += goc(0, T[1], T[2]);
            if(nans > ans) ans = nans;
        }
        printf("%d\n", ans);
    }
}
