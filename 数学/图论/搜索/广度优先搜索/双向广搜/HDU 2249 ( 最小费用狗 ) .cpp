#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n[2], d;
vector < int > vec[120011];
int in[120011];
int hash[120011];
int buf[120011];
queue < int > q[2];
int temp, tt;
int i, j, k;

int start[2], end[2];

int main() {

    int x, y;

    while(scanf("%d %d %d", &n[0], &n[1], &d) != EOF) {
        
        if(!n[0] && !n[1] && !d)
            break;

        start[0] = 1; end[0] = n[0];
        start[1] = n[0] + 1; end[1] = n[0] + n[1];

        for(i = 1; i <= n[0] + n[1]; i++)
            vec[i].clear();

        memset(buf, 0, sizeof(buf));

        for(i = 0; i < d; i++) {
            scanf("%d %d", &x, &y);
            vec[y].push_back(x);
            buf[ x ] ++;
        }

        int ans = 999999999;
        for(i = 0; i < 2; i++) {
            
            int coun = 1;
            for(j = 1; j <= n[0] + n[1]; j++)
                in[j] = buf[j];

            memset(hash, 0, sizeof(hash));

            while(!q[0].empty())
                q[0].pop();

            while(!q[1].empty())
                q[1].pop();

            for(j = 1; j <= n[0] + n[1]; j++) {
                if(!in[ j ]) {
                    if(j <= n[0])
                        q[0].push( j );
                    else
                        q[1].push( j );
                    hash[ j ] = 1;
                }
            }

            int mode = i;

            while(!q[0].empty() || !q[1].empty()) {    

                while(!q[ mode ].empty()) {
                    temp = q[ mode ].front();
                    q[ mode ].pop();

                    int size = vec[ temp ].size();

                    for(j = 0; j < size; j++) {

                        tt = vec[ temp ][j];                
                        in[ tt ] --;

                        if(!hash[tt] && !in[ tt ]) {
                            hash[ tt ] = 1;
                            if(tt <= n[0]) {
                                q[0].push( tt );
                            }else {
                                q[1].push( tt );
                            }
                        }
                    }
                }
                mode ^= 1;
                coun ++;
            }
            if(coun < ans)
                ans = coun;
        }
        printf("%d\n", ans);
    }
}

