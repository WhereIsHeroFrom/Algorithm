/*
题意：
如下的 2X2 的卡片，问是否能够通过某种方式用最多6个卡片摆放出给定的格子
 _ _ 
|   |
|_ _|

例如：
   _ _   #
 _|   |_ #
| |_ _| |#
|_|   |_|#
  |_ _|_|#


题解：DFS
	能够放置卡片的位置最多9个；枚举9个位置，最多 9! 种情况，然后判断枚举出来的情况是否和目标情况匹配即可；
  
*/



#include <iostream>
#include <cmath>
using namespace std;

#define ROW_SINGLE_MAXC 5
#define COL_SINGLE_MAXC 3

char Square[COL_SINGLE_MAXC][ROW_SINGLE_MAXC + 1] = {
	" _ _ ",
	"|   |",
	"|_ _|",
};

#define ROW_MAX_POS 3
#define COL_MAX_POS 3
#define MAX_POS 9

#define ROW_MAXC 9
#define COL_MAXC 5

#define MAXS 6

char res[COL_MAXC][ROW_MAXC+20];
char mat[COL_MAXC][ROW_MAXC];

bool checkRow(int rowIdx, char from[COL_MAXC][ROW_MAXC], char to[COL_MAXC][ROW_MAXC+20]) {
	int i;
	for (i = 0; i < ROW_MAXC; ++i) {
		if (from[rowIdx][i] != to[rowIdx][i]) {
			return false;
		}
	}
	return true;
}

bool checkPreRow(int preRowIdx, char from[COL_MAXC][ROW_MAXC], char to[COL_MAXC][ROW_MAXC+20]) {
	int i;
	for (i = 0; i <= preRowIdx; ++i) {
		if (!checkRow(i, from, to)) {
			return false;
		}
	}
	return true;
}


void copyToStackMat(char copyTo[COL_SINGLE_MAXC][ROW_SINGLE_MAXC + 1], char copyFrom[COL_MAXC][ROW_MAXC], int pos) {
	int posc = pos / ROW_MAX_POS;
	int posr = 2 * (pos % ROW_MAX_POS);
	int i, j;
	for (i = 0; i < COL_SINGLE_MAXC; ++i) {
		for (j = 0; j < ROW_SINGLE_MAXC; ++j) {
			copyTo[i][j] = copyFrom[i+posc][j+posr];
		}
	}
}

void copyToGlobalMat(char copyTo[COL_MAXC][ROW_MAXC], char copyFrom[COL_SINGLE_MAXC][ROW_SINGLE_MAXC + 1], int pos, bool blend) {
	int posc = pos / ROW_MAX_POS;
	int posr = 2 * (pos % ROW_MAX_POS);
	int i, j;
	for (i = 0; i < COL_SINGLE_MAXC; ++i) {
		for (j = 0; j < ROW_SINGLE_MAXC; ++j) {
			if (blend) {
				// i,j = (0,0), (0,2), (0,4)
				if (!i && !(j&1)) continue;
			}
			copyTo[i + posc][j + posr] = copyFrom[i][j];
		}
	}
}

void printGlobalMat() {
	int i, j;
	for (i = 0; i < COL_MAXC; ++i) {
		for (j = 0; j < ROW_MAXC; ++j) {
			printf("%c", mat[i][j]);
		}
		puts("");
	}
	puts("");
}

int has[MAX_POS];

bool dfs(int startIdx, int cnt) {
	int i;
	//printGlobalMat();

	if (checkPreRow(4, mat, res)) {
		return true;
	}

	if (cnt < MAXS) {
		for (i = 0; i < MAX_POS; ++i) {

			char stackmat[COL_SINGLE_MAXC][ROW_SINGLE_MAXC + 1];
			copyToStackMat(stackmat, mat, i);
			copyToGlobalMat(mat, Square, i, true);
			if (!has[i]) {
				has[i] = 1;
				if (dfs(i + 1, cnt + 1)) {
					return true;
				}
				has[i] = 0;
			}
			copyToGlobalMat(mat, stackmat, i, false);

		}
	}
	return false;
}

int main() {
	int i, j;
	int cas = 0;
	while (gets(res[0])) {

		if (res[0][0] == '0') {
			break;
		}

		for (i = 1; i < 5; ++i) {
			gets(res[i]);
		}
		memset(has, 0, sizeof(has));

		for (i = 0; i < COL_MAXC; ++i) {
			for (j = 0; j < ROW_MAXC; ++j) {
				mat[i][j] = ' ';
			}
		}

		printf("Case %d: %s\n", ++cas, dfs(-1, 0) ? "Yes" : "No");
	}
	return 0;
}
