#include <iostream>

using namespace std;

#define MAXN 110

int mat[MAXN][MAXN];
int n, m;
int mini, minj;

int dir[4][2] = {
	{ -1, 0 },   // U
	{ 0, -1 },   // L
	{ 1, 0 },    // D
	{ 0, 1 },    // R
};
char dirChar[5] = "ULDR";

void printChar(char c, int cnt) {
	int i;
	for (i = 0; i < cnt; i++) printf("%c", c);
}

// rfirst ÊÇ·ñÏÈÏòÓÒ 
void printHorMove(int n, int m, int rfirst) {
	for (int i = 0; i < n; i++) {
		char c = ((i & 1) ^ rfirst) ? 'R' : 'L';
		printChar(c, m - 1);
		printChar('D', i < n - 1 ? 1 : 0);
	}
}

int moveIdx[2][4] = {
	{ 2, 3, 0, 3 },    // right move
	{ 2, 1, 0, 1 },    // left move
};

bool outBound(int x, int y) {
	return x < 0 || y < 0 || x == n || y == m;
}

void Move(int x, int y, int cnt, int movedir) {
	int ndir = moveIdx[movedir][cnt % 4];
	x += dir[ndir][0];
	y += dir[ndir][1];
	if (outBound(x, y)) return;

	if (x == mini && y == minj) {
		cnt++;
		x -= dir[ndir][0];
		y -= dir[ndir][1];
		ndir = moveIdx[movedir][cnt % 4];
		x += dir[ndir][0];
		y += dir[ndir][1];
		if (outBound(x, y)) return;
		printf("%c", dirChar[ndir]);
		Move(x, y, cnt - 1, movedir);
	}
	else {
		printf("%c", dirChar[ndir]);
		Move(x, y, cnt + 1, movedir);
	}
}

int main() {
	int i, j;
	while (scanf("%d %d", &n, &m) != EOF) {
		int sum = 0;
		mini = -1;

		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++) {
				scanf("%d", &mat[i][j]);
				sum += mat[i][j];

				if (i == 0 && j == 0 || i == n - 1 && j == m - 1) continue;
				if ((i + j) & 1) {
					if (mini == -1 || mat[i][j] < mat[mini][minj]) {
						mini = i;
						minj = j;
					}
				}
			}
		}
		if (n & 1) {
			printf("%d\n", sum);
			printHorMove(n, m, 1);
		}
		else if (m & 1) {
			printf("%d\n", sum);
			for (i = 0; i < m; i++) {
				char c = (i & 1) ? 'U' : 'D';
				printChar(c, n - 1);
				printChar('R', i < m - 1 ? 1 : 0);
			}
		}
		else {
			printf("%d\n", sum - mat[mini][minj]);
			if (mini == n - 1) {
				printHorMove(n - 2, m, 1);
				if (n > 2) {
					printf("D");
				}
				Move(n - 2, 0, 0, 0);
			}
			else {
				printHorMove(mini, m, 1);
				if (mini) {
					printf("D");
				}
				Move(mini, (mini & 1) ? m - 1 : 0, 0, mini & 1);
				if (mini < n - 2) {
					printf("D");
					printHorMove(n - (mini + 2), m, mini & 1);
				}
			}

		}
		puts("");
	}
	return 0;
}

/*
6 6
9 9 9 9 9 9
9 9 9 9 9 9
9 7 9 9 9 9
9 9 9 9 9 9
9 9 9 9 9 9
9 9 9 9 9 9

6 6
9 7 9 9 9 9
9 9 9 9 9 9
9 9 9 9 9 9
9 9 9 9 9 9
9 9 9 9 9 9
9 9 9 9 9 9

6 6
9 9 9 9 9 9
9 9 7 9 9 9
9 9 9 9 9 9
9 9 9 9 9 9
9 9 9 9 9 9
9 9 9 9 9 9

6 6
9 9 9 9 9 9
9 9 9 9 9 9
9 9 9 9 9 9
9 9 9 9 9 9
9 9 9 9 9 9
9 9 7 9 9 9

3 3
2 3 3
3 3 3
3 3 2

4 3
2 3 3
3 3 3
3 3 2
1 1 1

4 4
1 2 3 4
1 2 3 4
1 2 3 1
1 2 3 4

4 4
1 2 3 4
1 2 3 4
1 2 3 4
1 2 3 4

4 4
1 2 3 4
0 2 3 4
1 2 3 4
1 2 3 4

4 4
1 2 3 4
1 2 3 4
0 2 3 4
1 2 3 4

4 4
9 9 9 9
9 9 2 9
1 9 9 9
2 9 9 9

2 2
1 2
3 4

2 2
1 3
2 4
*/