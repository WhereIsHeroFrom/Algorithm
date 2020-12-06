/*
浮点数大于小于的判定问题
*/

#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

int n, m;

#define eps 1e-5
#define MAXN 100
#define MAXP 5

char name[MAXN][30];
double dor[MAXN];
char item[1000];

char comp[MAXP][3] = {
	"<", ">", "<=", ">=", "="
};

int findName(char *kname) {
	int i;
	for (i = 0; i < n; ++i) {
		if (!strcmp(kname, name[i])) {
			return i;
		}
	}
	return -1;
}

int findComp(char *cmpname) {
	int i;
	for (i = 0; i < MAXP; ++i) {
		if (!strcmp(cmpname, comp[i])) {
			return i;
		}
	}
	return -1;
}

bool EQ(double a, double b) {
	return fabs(a - b) < eps;
}

bool NEQ(double a, double b) {
	return !EQ(a, b);
}

int main() {
	int i, cas = 0;
	scanf("%d %d", &n, &m);
	for (i = 0; i < n; ++i) {
		scanf("%s %lf", name[i], &dor[i]);
	}

	for (i = 1; i <= m; ++i) {

		double s = 0;
		bool flag;
		while (scanf("%s", item) != EOF) {
			int id = findName(item);
			int cp = findComp(item);

			if (id >= 0) {
				s += dor[id];
			}
			else if (cp >= 0) {
				int val;
				scanf("%d", &val);

				if (cp == 0) {
					flag = (s < val) && NEQ(s, val);
				}
				else if (cp == 1) {
					flag = (s > val) && NEQ(s, val);
				}
				else if (cp == 2) {
					flag = (s < val) || EQ(s, val);
				}
				else if (cp == 3) {
					flag = (s > val) || EQ(s, val);
				}
				else if (cp == 4) {
					flag = EQ(s, val);
				}

				printf("Guess #%d was ", ++cas);
				printf("%s\n", flag ? "correct." : "incorrect.");
				break;
			}
		}

	}

	return 0;
}

/*
6 5
CDU 30.7
SPD 20.8
Gruene 12.1
FDP 11.0
DIELINKE 7.5
CSU 7.2
FDP > 11
CDU + SPD < 50
SPD + CSU >= 28
FDP + SPD + CDU <= 42
CDU + FDP + SPD + DIELINKE = 70

2 1
rt .1
gh .9
rt + gh =   1
*/