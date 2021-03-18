#include <iostream>
#include <algorithm>
using namespace std;

int t;
int alti[101];
int n, m;
int d[101], s[101];
int map[101][101];
int sor[101];

int Dijkstra(int Min, int Max) {

    int i;

    for (i = 1; i <= n; i++) {
        if (alti[i] > Max || alti[i] < Min) {
            d[i] = 100000000;
            s[i] = 0;
        }
        else {
            d[i] = map[1][i];
            s[i] = 0;
        }
    }
    d[1] = 0;
    s[1] = 1;

    while (1) {
        int Mina = 100000000, u = -1;
        for (i = 1; i <= n; i++) {
            if (alti[i] > Max || alti[i] < Min)
                continue;
            if (!s[i] && d[i] < Mina) {
                Mina = d[i];
                u = i;
            }
        }
        if (u == n)
            return d[u];
        if (u == -1)
            return -1;
        s[u] = 1;
        for (i = 1; i <= n; i++) {
            if (alti[i] > Max || alti[i] < Min)
                continue;
            if (!s[i] && d[u] + map[u][i] < d[i]) {
                d[i] = d[u] + map[u][i];
            }
        }
    }
}

int main() {

    int i, j;
    scanf("%d", &t);
    int a, b, c;
    while (t--) {
        scanf("%d %d", &n, &m);

        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                map[i][j] = 100000000;
            }
        }
        for (i = 1; i <= n; i++) {
            scanf("%d", &alti[i]);
            sor[i - 1] = alti[i];
        }
        sort(sor, sor + n);

        while (m--){
            scanf("%d %d %d", &a, &b, &c);
            if (c < map[a][b]) {
                map[a][b] = map[b][a] = c;
            }
        }

        int Min = 2000000000, path;

        for (i = 0; i < n; i++) {
            for (j = i + 1; j < n; j++) {

                if (alti[n] > sor[j] || alti[n] < sor[i])
                    continue;
                if (alti[1] > sor[j] || alti[1] < sor[i])
                    continue;

                if (sor[j] - sor[i] > Min)
                    break;

                int yu;
                yu = Dijkstra(sor[i], sor[j]);
                //printf("%d %d %d\n", sor[i], sor[j], yu);

                if (yu + 1 && sor[j] - sor[i] == Min) {
                    if (yu < path)
                        path = yu;
                }

                if (yu + 1 && sor[j] - sor[i] < Min) {
                    Min = sor[j] - sor[i];
                    path = yu;
                }

                if (yu != -1)
                    break;
            }
        }
        if (n == 1)
            printf("0 0\n");
        else
            printf("%d %d\n", Min, path);
    }
}