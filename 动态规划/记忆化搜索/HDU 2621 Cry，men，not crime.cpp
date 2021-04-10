#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

#define ll long long
ll m, n, temp;
ll rt[1350][1350];
const int inf = -1;

char r1[1000], r2[1000];
int i, j;

ll dfs(int x, int y) {
	if(x == 1 && y == 1) {
		return 1;
	}
	if(x < 1 || y < 1) {
		return 0;
	}
	ll &val = rt[x][y];
	if(val != inf) {
		return val;
	}
	return val = dfs(x-1, y) + dfs(x, y-1);
} 

int main()
{

    //printf("%lf\n", pow( 6.0 * INT_MAX, 1.0 / 3) );
    //freopen("1003.in", "r", stdin );
    //freopen("1003.out", "w", stdout );

memset(rt, -1, sizeof(rt));

    while( scanf("%s %s", r1, r2 ) != EOF )
    {
    	
        if(r1[0] == '0' && r2[0] != '0' || r1[0] != '0' && r2[0] == '0') {
            printf("1\n");
            continue;
        }

		
        sscanf(r1, "%I64d", &n);
        sscanf(r2, "%I64d", &m);

        if(!n && !m)
            break;

        if(n > m)
        {
            temp = n;
            n = m;
            m = temp;
        }

        if(n == 0)
            printf("1\n");
        else if(n == 1)
            printf("%I64d\n", m+1);
        else if(n == 2)
            printf("%I64d\n", (m+1)*(m+2)/2 );
        else if(n == 3)
            printf("%I64d\n", (m+1)*(m+2)/2*(m+3)/3);
        else if(n == 4)
            printf("%I64d\n", (m+1)*(m+2)/2*(m+3)*(m+4)/12);
        else
        {
        	
            printf("%I64d\n", dfs(n+1, m+1) );
        }
    }
}

