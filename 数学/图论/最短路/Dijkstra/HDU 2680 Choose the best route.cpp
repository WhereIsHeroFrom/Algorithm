#include iostream

using namespace std;

int n, end;
int map[1001][1001];
int d[1001];
bool s[1001];

int Dijkstra(int start) {
    int i;

    for (i = 1; i = n; i++) {
        d[i] = map[start][i];
        s[i] = false;
    }
    d[start] = 0;
    s[start] = true;

    while (1) {

        int Min = 1000000000, u = -1;
        for (i = 1; i = n; i++) {
            if (!s[i] && d[i]  Min) {
                Min = d[i];
                u = i;
            }
        }

        if (u == -1) {
            return 0;
        }
        s[u] = true;

        for (i = 1; i = n; i++) {
            if (!s[i] && d[u] + map[u][i]  d[i]) {
                d[i] = d[u] + map[u][i];
            }
        }
    }
}


int main() {

    int i, j;
    int p, q, t, w, m, end;

    while (scanf(%d %d %d, &n, &m, &end) != EOF) {

        int Min = INT_MAX;

        for (i = 1; i = n; i++) {
            for (j = 1; j = n; j++) {
                map[i][j] = 1000000000;
            }
        }

        while (m--) {
            scanf(%d %d %d, &p, &q, &t);
            if (t  map[q][p])
                map[q][p] = t;
        }

        for (i = 1; i = n; i++)
            map[i][i] = 0;

        Dijkstra(end);


        scanf(%d, &w);

        while (w--) {
            int x;
            scanf(%d, &x);
            int y = d[x];
            if (y != 1000000000 && y  Min)
                Min = y;
        }

        if (Min == INT_MAX)
            printf(-1n);
        else
            printf(%dn, Min);
    }
}