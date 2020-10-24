// HDU 2093
// 模拟题： 
// sccanf 的使用
// STL sort 函数的应用

#include <iostream>
#include <algorithm>
using namespace std;

struct Peo {
	char name[100];
	int cnt, score;

	bool operator < (const Peo& o) const {
		if (cnt != o.cnt) {
			return cnt > o.cnt;
		}
		if (score != o.score) {
			return score < o.score;
		}
		return strcmp(name, o.name) < 0;
	}
}P[100000];


void check(char *score, int punish_score, Peo& p) {
	if (score[0] == '-') {
		return;
	}
	int i;
	int haspa = false;
	for (i = 0; score[i]; ++i) {
		if (score[i] == '(') {
			haspa = true;
		}
	}
	int  a, b;
	if (haspa) {
		sscanf(score, "%d(%d)", &a, &b);
		p.cnt++;
		p.score += a + b*punish_score;
	}
	else {
		sscanf(score, "%d", &a);
		if (a > 0) {
			p.cnt++;
		}
		p.score += a;
	}

}
int main() {
	int n, punish_score;
	int i;
	while (scanf("%d %d", &n, &punish_score) != EOF) {
		int c = 0;
		while (scanf("%s", P[c].name) != EOF) {
			P[c].cnt = 0;
			P[c].score = 0;
			for (i = 0; i < n; ++i) {
				char score[100];
				scanf("%s", score);
				check(score, punish_score, P[c]);
			}

			++c;
		}
		sort(P, P + c);

		for (i = 0; i < c; ++i) {
			printf("%-10s %2d %4d\n", P[i].name, P[i].cnt, P[i].score);

		}
	}

	return 0;
}