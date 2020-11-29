// HDU 5903 
// BFS

#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

#define MAXL 1010
#define BITS 11

bool visit[MAXL][MAXL];
int pre[MAXL][MAXL];
char chr[MAXL][MAXL], ans[MAXL], tmpans[MAXL];
int anstop;

int n;
char str[MAXL];

int packstate(int step, int cnt) {
	return (step << BITS) | cnt;
}

void unpackstate(int s, int &step, int& cnt) {
	step = s >> BITS;
	cnt = s & ((1 << BITS) - 1);
}

short genval(char *str, int step, char c) {
	int a1 = (str[step - 1] == c) ? 0 : 1;
	int a2 = (str[n / 2 + step - 1] == c) ? 0 : 1;
	return a1 + a2;
}

void addstate(queue<int> &Q, int step, int cnt, int prestate, char c) {
	Q.push(packstate(step, cnt));
	visit[step][cnt] = true;
	pre[step][cnt] = prestate;
	chr[step][cnt] = c;
}

bool bfs(int m) {
	int startL = 0, endL = n / 2;
	int i;
	int has[26], hascas = 1;
	memset(has, 0, sizeof(has));
	memset(visit, 0, sizeof(visit));
	memset(pre, -1, sizeof(pre));
	queue<int> Q;
	addstate(Q, startL, m, -1, -1);
	ans[0] = '\0';

	while (!Q.empty()) {
		int nowstate = Q.front();
		Q.pop();

		int step, cnt;
		unpackstate(nowstate, step, cnt);

		if (step == endL) {
			if (cnt == 0) {
				// find
				anstop = 0;
				while (pre[step][cnt] != -1) {
					tmpans[n / 2 - anstop - 1] = chr[step][cnt];
					++anstop;
					nowstate = pre[step][cnt];
					unpackstate(nowstate, step, cnt);
				}
				tmpans[n / 2] = '\0';
				strcpy(ans, tmpans);
				break;
			}
			continue;
		}
		++hascas;
		for (i = 0; i < 26; ++i) {
			int nexstep = step + 1;
			int needcnt = genval(str, nexstep, 'a' + i);
			if (has[needcnt] == hascas) {
				continue;
			}
			has[needcnt] = hascas;
			int nexcnt = cnt - needcnt;
			if (nexcnt < 0) {
				continue;
			}
			if (visit[nexstep][nexcnt]) {
				continue;
			}
			addstate(Q, nexstep, nexcnt, nowstate, 'a' + i);
		}
	}
	if (ans[0]) {
		printf("%s%s\n", ans, ans);
		return true;
	}
	return false;
}

int main() {
	int t;
	int m;
	scanf("%d", &t);

	while (t--) {
		scanf("%d %d", &n, &m);
		scanf("%s", str);

		if ((n & 1) || !bfs(m)) {
			puts("Impossible");
		}
	}

	return 0;
}

/*
10
6 0
retert
6 1
retert
6 2
retert
6 3
retert
6 4
retert
6 5
retert
6 6
retert


10 0
ajkdlajdkd
10 1
ajkdlajdkd
10 2
ajkdlajdkd
10 3
ajkdlajdkd
10 4
ajkdlajdkd
10 5
ajkdlajdkd
10 6
ajkdlajdkd
10 7
ajkdlajdkd
10 8
ajkdlajdkd
10 9
ajkdlajdkd
10 10
ajkdlajdkd

10 0
aaaaaaaaaa

10 2
aaaaaaaaaa



10
6 2
aaaaaa
6 4
aaaaaa
*/