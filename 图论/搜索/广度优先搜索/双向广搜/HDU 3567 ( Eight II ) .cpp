#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define TOTAL 9
#define MAXSTATE 362880

int fac[TOTAL];
int c[TOTAL + 1];

char idx2Dir[5] = {
	'd', 'l', 'r', 'u'
};
int dirConvert[4] = {
	3, 2, 1, 0
};

int dir[4][2] = {
	{ 1, 0 }, { 0, -1 }, { 0, 1 }, { -1, 0 }
};

int lowbit(int x) {
	return x & -x;
}

void add(int x, int v) {
	while (x <= TOTAL) {
		c[x] += v;
		x += lowbit(x);
	}
}

int sum(int x) {
	int s = 0;
	while (x) {
		s += c[x];
		x ^= lowbit(x);
	}
	return s;
}

int getDigit(char ch) {
	if (ch == 'X') {
		return 0;
	}
	return ch - '0';
}

int getHashCode(char* str) {
	int i, s = 0;
	for (i = 1; i <= TOTAL; i++) {
		c[i] = 0;
	}
	for (i = 1; i <= TOTAL; i++) {
		add(i, 1);
	}
	for (i = 0; i < TOTAL; i++) {
		int d = getDigit(str[i]) + 1;
		s += (sum(d) - 1) * fac[TOTAL - 1 - i];
		add(d, -1);
	}
	return s;
}

int getXPos(char *str) {
	for (int i = 0; str[i]; i++) {
		if (str[i] == 'X') {
			return i;
		}
	}
	return -1;
}

void getXY(int pos, int &x, int &y) {
	x = pos / 3;
	y = pos % 3;
}

int getPos(int x, int y) {
	return x * 3 + y;
}

bool validBound(int x, int y) {
	return !(x < 0 || x >= 3 || y < 0 || y >= 3);
}

int pre[2][MAXSTATE];          // 当前状态的前驱状态 
int pre_dir[2][MAXSTATE];      // 从 pre[state] => state 的方向 (d, l, r, u) 
int dis[2][MAXSTATE];          // 起点(or 终点)到当前状态的最短路长度 
int xy[2][MAXSTATE];           // 每个状态X标记所在的位置(下标从0开始) 012X345678  则值为3 
char stateStr[MAXSTATE][10];   // 状态对应的字符串表示，即  "012X345678"

void fillData(int p, int stateID, int dist, char* sstr, int xPos, int prev, int predir) {
	dis[p][stateID] = dist;
	pre[p][stateID] = prev;
	pre_dir[p][stateID] = (p == 0 || predir == -1) ? predir : dirConvert[predir];
	xy[p][stateID] = xPos;
	strcpy(stateStr[stateID], sstr);
}


bool check(int p, int prestateID, int stateID, int newpredir, int newdist) {
	// 新找到的路径比之前的短，返回true，需要更新 
	if (dis[p][stateID] == -1 || newdist < dis[p][stateID]) {
		return true;
	}

	// 新找到的路径比之前的长，返回false 
	if (newdist > dis[p][stateID]) {
		return false;
	}

	// 路径一样长，并且是正向搜索，那么字典序一定不会比之前的小，返回false 
	if (p == 0) {
		return false;
	}

	if (pre_dir[p][stateID] != newpredir) {
		return (newpredir < pre_dir[p][stateID]);
	}

	int x = prestateID;
	int y = pre[p][stateID];

	while (x != -1 && y != -1) {
		if (pre_dir[p][x] != pre_dir[p][y]) {
			return pre_dir[p][x] < pre_dir[p][y];
		}
		x = pre[p][x];
		y = pre[p][y];
	}
	return false;
}

int path[1000];

void bfs(char *beg, char *end) {
	memset(dis, -1, sizeof(dis));

	queue <int> Q[2];
	int i;
	int s = getHashCode(beg);
	int e = getHashCode(end);

	// 初始化起点 
	fillData(0, getHashCode(beg), 0, beg, getXPos(beg), -1, -1);
	Q[0].push(s);
	// 初始化终点
	fillData(1, getHashCode(end), 0, end, getXPos(end), -1, -1);
	Q[1].push(e);

	int p = 0;
	char tmpStr[10];
	while (!Q[0].empty() || !Q[1].empty()) {
		queue <int> tmpQ;
		while (!Q[p].empty()) {
			int now = Q[p].front();
			Q[p].pop();

			if (dis[p ^ 1][now] != -1) {
				if (p == 0) {
					int step = dis[p][now] + dis[p ^ 1][now];
					path[0] = 0;

					int tmp = now;
					while (tmp != -1) {
						if (pre_dir[p][tmp] == -1) {
							break;
						}
						path[++path[0]] = pre_dir[p][tmp];
						tmp = pre[p][tmp];
					}
					for (i = 1; i <= path[0] / 2; i++) {
						int d = path[i];
						path[i] = path[path[0] + 1 - i];
						path[path[0] + 1 - i] = d;
					}

					tmp = now;
					while (tmp != -1) {
						if (pre_dir[p ^ 1][tmp] == -1) {
							break;
						}
						path[++path[0]] = pre_dir[p ^ 1][tmp];
						tmp = pre[p ^ 1][tmp];
					}

					printf("%d\n", step);
					for (i = 1; i <= path[0]; i++) {
						printf("%c", idx2Dir[path[i]]);
					}
					puts("");

					return;
				}
			}

			int x, y, tx, ty;
			char ch;
			int pre_pos = xy[p][now];

			getXY(pre_pos, x, y);

			strcpy(tmpStr, stateStr[now]);

			// 从当前状态扩展出四个状态
			for (i = 0; i < 4; i++) {
				tx = x + dir[i][0];
				ty = y + dir[i][1];

				if (validBound(tx, ty)) {

					int next_pos = getPos(tx, ty);

					// X位置交换 
					ch = tmpStr[pre_pos]; tmpStr[pre_pos] = tmpStr[next_pos]; tmpStr[next_pos] = ch;
					int stateID = getHashCode(tmpStr);

					if (check(p, now, stateID, dirConvert[i], dis[p][now] + 1)) {
						fillData(p, stateID, dis[p][now] + 1, tmpStr, next_pos, now, i);
						tmpQ.push(stateID);
					}

					// 交换回来 
					ch = tmpStr[pre_pos]; tmpStr[pre_pos] = tmpStr[next_pos]; tmpStr[next_pos] = ch;

				}
			}

		}

		while (!tmpQ.empty()) {
			Q[p].push(tmpQ.front());
			tmpQ.pop();
		}
		p ^= 1;
	}
}

char str[2][20];
int main() {
	int i, j;
	int t, cases = 0;

	fac[0] = 1;
	for (i = 1; i < TOTAL; i++) {
		fac[i] = fac[i - 1] * i;
	}

	scanf("%d", &t);
	while (t--) {
		scanf("%s %s", str[0], str[1]);
		printf("Case %d: ", ++cases);
		bfs(str[0], str[1]);
	}
	return 0;
}

/*
10
12X456783
X15742836
*/