#include <iostream>
#include <queue>
using namespace std;

#define MAXN 55
#define MAP_BASE 2000

int dir[4][9][2] = {
	{ { 0, 0 }, { -1, -1 }, { -1, 0 }, { -1, 1 }, { -2, -2 }, { -2, -1 }, { -2, 0 }, { -2, 1 }, { -2, 2 } },
	{ { 0, 0 }, { 1, -1 }, { 1, 0 }, { 1, 1 }, { 2, -2 }, { 2, -1 }, { 2, 0 }, { 2, 1 }, { 2, 2 } },
	{ { 0, 0 }, { -1, -1 }, { 0, -1 }, { 1, -1 }, { -2, -2 }, { -1, -2 }, { 0, -2 }, { 1, -2 }, { 2, -2 } },
	{ { 0, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { -2, 2 }, { -1, 2 }, { 0, 2 }, { 1, 2 }, { 2, 2 } },
};

int sdir[5][2] = {
	{ -1, 0 },
	{ 1, 0 },
	{ 0, -1 },
	{ 0, 1 },
	{ 0, 0 }
};

int n, m, k;
char str[MAXN][MAXN];
int mat[MAXN][MAXN];

struct Monster {
	// x表示竖着，y表示横着 
	int x, y;
	int d;

	Monster() {
	}
	Monster(int _x, int _y, int _d) {
		x = _x;
		y = _y;
		d = _d;
	}

	void read() {
		scanf("%d %d %d", &x, &y, &d);
		x--;
		y--;
		d--;
	}
}M[1000];

class posInfo {
public:
	int x, y, step;
	posInfo(){}
	posInfo(int _x, int _y, int _s) {
		x = _x;
		y = _y;
		step = _s;
	}
};

short vis[1010][MAXN][MAXN];

int getInvDir(int d) {
	if (d == 0 || d == 1) {
		return 1 - d;
	}
	else {
		return 5 - d;
	}
}

void printMonsterView(Monster monsterInfos) {
	for (int i = 0; i < 9; i++) {
		int dx = dir[monsterInfos.d][i][0];
		int dy = dir[monsterInfos.d][i][1];
		str[dx + monsterInfos.x][dy + monsterInfos.y] = monsterInfos.d + '0';
	}
}

bool isBlock(int x, int y) {
	if (x < 0 || y < 0 || x >= n || y >= m) {
		return true;
	}
	if (str[x][y] == '*') {
		return true;
	}
	return false;
}

bool isInMonsterView(posInfo p) {
	return mat[p.x][p.y] == p.step;
}

void singleMonsterViewHash(Monster monsterInfos, int hashVal) {
	for (int i = 0; i < 9; i++) {
		int tx, ty;
		tx = monsterInfos.x + dir[monsterInfos.d][i][0];
		ty = monsterInfos.y + dir[monsterInfos.d][i][1];

		if (isBlock(tx, ty))
			continue;
		mat[tx][ty] = hashVal;
	}
}

void monsterViewHash(int hashVal) {
	for (int i = 0; i < k; i++) {
		singleMonsterViewHash(M[i], hashVal);
	}
}

void singleMonsterMove(Monster& monsterInfos) {
	int tx = monsterInfos.x + sdir[monsterInfos.d][0];
	int ty = monsterInfos.y + sdir[monsterInfos.d][1];

	if (isBlock(tx, ty)) {
		monsterInfos.d = getInvDir(monsterInfos.d);
	}
	else {
		monsterInfos.x = tx;
		monsterInfos.y = ty;
	}
}

void monsterMove() {
	for (int i = 0; i < k; i++) {
		singleMonsterMove(M[i]);
	}
}

bool reachVis[MAXN][MAXN];

bool isReachable(posInfo start, posInfo end) {
	memset(reachVis, 0, sizeof(reachVis));

	queue < posInfo > Q;
	reachVis[start.x][start.y] = 1;

	Q.push(start);
	while (!Q.empty()) {
		posInfo now = Q.front();
		Q.pop();
		if (now.x == end.x && now.y == end.y) {
			return true;
		}

		posInfo next;
		for (int i = 0; i < 4; i++) {
			next.x = now.x + sdir[i][0];
			next.y = now.y + sdir[i][1];
			if (isBlock(next.x, next.y)) {
				continue;
			}
			if (!reachVis[next.x][next.y]) {
				reachVis[next.x][next.y] = 1;
				Q.push(next);
			}
		}
	}
	return false;
}

int solve(int caseID) {
	int i, j;
	posInfo start, end;
	scanf("%d %d", &n, &m);
	for (i = 0; i < n; i++) {
		scanf("%s", str[i]);
		for (j = 0; j < m; j++) {
			if (str[i][j] == 'A') {
				start = posInfo(i, j, 0);
			}
			else if (str[i][j] == 'B') {
				end = posInfo(i, j, 0);
			}
			mat[i][j] = MAP_BASE + str[i][j];
		}
	}
	scanf("%d", &k);
	for (i = 0; i < k; i++) {
		M[i].read();
		//printMonsterView(M[i]);
	}
	monsterViewHash(0);

	//for(i = 0; i < n; i++) puts(mat[i]);

	int prestep = 0;
	int ans = -1;

	if (isReachable(start, end)) {
		queue <posInfo> Q;
		vis[start.step][start.x][start.y] = caseID;
		Q.push(start);

		while (!Q.empty()) {
			posInfo now = Q.front();
			Q.pop();

			if (now.step > 1000) continue;

			if (prestep != now.step) {
				// 怪物移动一格
				monsterMove();
				// 怪物的占领区域hash
				monsterViewHash(now.step);
				prestep = now.step;
			}

			/*for(i = 0; i < n; i++) {
			for(j = 0; j < m; j++) {
			printf("%d ", mat[i][j]);
			}
			puts("");
			}
			puts("");*/

			if (isInMonsterView(now)) {
				continue;
			}

			if (now.x == end.x && now.y == end.y) {
				ans = now.step;
				break;
			}

			posInfo next;
			for (i = 0; i < 5; i++) {
				next.x = now.x + sdir[i][0];
				next.y = now.y + sdir[i][1];
				next.step = now.step + 1;
				if (isBlock(next.x, next.y)) {
					continue;
				}
				if (vis[next.step][next.x][next.y] != caseID) {
					vis[next.step][next.x][next.y] = caseID;
					Q.push(next);
				}
			}
		}
	}
	printf("Case %d: ", caseID);
	if (ans == -1) {
		printf("胜败兵家事不期 卷土重来是大侠");
	}
	else {
		printf("%d", ans);
	}
	puts("");
}


int main() {
	int T;

	scanf("%d", &T);
	for (int i = 1; i <= T; i++) {
		solve(i);
	}
	return 0;
}

/*
100
16 20
....................
....................
....................
A...................
....................
..................B.
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................
4
3 4 1
10 4 2
5 8 3
10 8 4

100
3 4
*.*.
.A.B
***.
1
3 4 1

3 4
*.*.
A..B
***.
1
3 4 1

50 50
A.................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
..................................................
.............................................*....
.............................................B*...
.............................................*....
..................................................
1
4 4 1


*/