/*
题意：3 X 3 的格子中，可以放置 B/R/G/Y 四种块，每个块有自己的分数，放置规则如下：
0. 当格子中原本已经有块的时候，也是允许放置的，可以先把那个块拿出来，拿出的过程不算步数；
1. 任何时候都可以放置一个 B ；
2. 当旁边有 B 的时候，可以放一个 R ；
3. 当旁边有 B 和 R 的时候，可以放一个 G ；
4. 当旁边有 B、R、G，可以放 Y ；
求所有在格子上的块的分数之和达到 w 的最小步数；

题解：BFS + 预处理（BFS最重要的就是状态分析）
1）每个格子总共有 5（B/R/G/Y/空白） 种状态，所以9个格子总共 5^9 种状态 (实际上由于各种限制，状态数远小于这个值)；
2）四种格子的分数总和只和他们的【组合】有关系，和【排列】没关系，所以可以事先筛选出所有的组合，每个的范围为 [0,9], 加起来的值 <= 9，预先筛选出来，总共 715 种情况；
3）将所有这 715 种状态，对应的分数和计算出来，如果分数和大于等于w的，则把这个状态标记为 1，否则标记为 0；
4）对所有状态进行编码，编码权重按照从左到右，从上到下进行，最左上角的格子作为 5^0，然后是 5^1 ... 最右下角的格子权重为 5^8，空为0，B、R、G、Y对应1、2、3、4；
5) 从 0 状态开始BFS，结束状态为 3）中预处理出来的那几种状态，但是判断结束状态的编码需要从【排列】转变成【组合】的形式；
6）搜索扩展状态的时候可以这么来：枚举每种块（编号分别为1，2，3，4），枚举每个格子，将四周对应位置的状态组合到一个位组里；
1 -> 1<<(0)
2 -> 1<<(2-1)
3 -> 1<<(3-1)
4 -> 1<<(4-1)
那么 1 号块需要满足的条件是：  位组结果  & 0 == 0
2 号块需要满足的条件是:   位组结果  & 1 == 1
3 号块需要满足的条件是:   位组结果  & 11 == 11
4 号块需要满足的条件是:   位组结果  & 111 == 111

7）注意，这里每次搜索其实都是重复的，所以可以预先跑一次广搜把所有状态需要消耗多少步都先跑出来，然后根据输入计算可行情况；
*/

#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

#define COMB_MAX 10000
#define MAXC 3
bool validState[COMB_MAX];

const int BLOCK_TOTAL_MASK[5] = { -1, 0, 1, 3, 7 };
const int BLOCK_SINGLE_MASK[5] = { 0, 1, 2, 4, 8 };

int power5[] = { 1, 5, 25, 125, 625, 3125, 15625, 78125, 390625, 1953125 };

int changeToComb(int arrangeCode) {
	int has[5] = { 0, 0, 0, 0, 0 };
	while (arrangeCode) {
		++has[arrangeCode % 5];
		arrangeCode /= 5;
	}
	int combCode = 1000 * has[1] + 100 * has[2] + 10 * has[3] + has[4];
	return combCode;
}

int getValueInPower(int arrangeCode, int pos) {
	return arrangeCode / power5[pos] % 5;
}

int getNextValue(int arrangeCode, int pos, int block) {
	return arrangeCode + (block - (arrangeCode / power5[pos] % 5)) * power5[pos];
}

int dir[4][2] = {
	{ 0, 1 },
	{ 0, -1 },
	{ 1, 0 },
	{ -1, 0 }
};

int step[2000000];

bool outOfBound(int posx, int posy) {
	return posx < 0 || posx >= 3 || posy < 0 || posy >= 3;
}

struct State {
	int arrageState;
	int combState;
	int cnt;

	State() {}
	State(int _a, int _c, int _cnt) : arrageState(_a), combState(_c), cnt(_cnt) {
	}
}allState[300000];
int stateTop;

void bfs() {
	int block, pos, d;
	memset(step, -1, sizeof(step));

	queue <int> Q;
	stateTop = 0;
	Q.push(0);
	step[0] = 0;
	allState[stateTop++] = State(0, 0, 0);


	while (!Q.empty()) {
		int nowState = Q.front();
		Q.pop();

		for (pos = 0; pos < 9; ++pos) {
			int posx = (pos / 3);
			int posy = (pos % 3);
			int adjMask = 0;
			for (d = 0; d < 4; ++d) {
				int nexposx = posx + dir[d][0];
				int nexposy = posy + dir[d][1];
				if (outOfBound(nexposx, nexposy)) {
					continue;
				}
				int nexpos = nexposx * 3 + nexposy;
				int adjBlock = getValueInPower(nowState, nexpos);
				adjMask |= BLOCK_SINGLE_MASK[adjBlock];
			}

			for (block = 1; block <= 4; ++block) {
				if ((adjMask & BLOCK_TOTAL_MASK[block]) == BLOCK_TOTAL_MASK[block]) {
					// 这种情况才能往 pos 上放置 block
					int nextState = getNextValue(nowState, pos, block);
					if (step[nextState] == -1) {
						Q.push(nextState);
						step[nextState] = step[nowState] + 1;
						allState[stateTop++] = State(nextState, changeToComb(nextState), step[nextState]);
					}
				}
			}
		}
	}
}

int main() {
	int a, b, c, d, w;
	int i, j, k, l;
	int cas = 0;
	bfs();

	while (scanf("%d", &a) != EOF && a) {
		scanf("%d %d %d %d", &b, &c, &d, &w);

		for (i = 0; i <= 9; ++i) {
			for (j = 0; j + i <= 9; ++j) {
				for (k = 0; k + j + i <= 9; ++k) {
					for (l = 0; l + k + j + i <= 9; ++l) {
						validState[i * 1000 + j * 100 + k * 10 + l] = ((a*i + b*j + c*k + d*l) >= w);
					}
				}
			}
		}
		int ans = -1;
		for (i = 0; i < stateTop; ++i) {
			if (validState[allState[i].combState]) {
				if (allState[i].cnt < ans || ans == -1) {
					ans = allState[i].cnt;
				}
			}
		}
		printf("Case %d: ", ++cas);
		if (ans == -1) {
			printf("Impossible");
		}
		else {
			printf("%d", ans);
		}

		puts("");
	}
	return 0;
}
