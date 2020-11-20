#include <iostream>

using namespace std;

char timeStr[20];
int H, M, S, alpha;

void getTime(int t, int &h, int &m, int &s) {
	h = t / 3600;
	m = t / 60 % 60;
	s = t % 60;
}

double getAlpha(int t) {
	int h, m, s;
	getTime(t, h, m, s);
	// hour
	double hAlpha = 30 * h + 0.5*m + s / 120.0;
	double mAlpha = m * 6 + s / 10.0;
	double deltaAlpha = hAlpha - mAlpha;
	if (deltaAlpha < 0) {
		deltaAlpha = -deltaAlpha;
	}
	if (deltaAlpha > 180) {
		deltaAlpha = 360 - deltaAlpha;
	}

	return deltaAlpha;
}

bool fit(bool isstart, int t, int alpha) {
	double delta1 = getAlpha(t);
	double delta2 = getAlpha(t + 1);
	if (delta1 > delta2) {
		if (isstart) {
			if (delta1 > alpha && alpha > delta2) {
				return true;
			}
		}
		else {
			if (delta1 >= alpha && alpha > delta2) {
				return true;
			}
		}
	}
	else {
		if (isstart) {
			if (delta1 < alpha && alpha < delta2) {
				return true;
			}
		}
		else {
			if (delta1 <= alpha && alpha < delta2) {
				return true;
			}
		}
	}
	return false;
}

int main() {
	int i;
	int cases = 0;
	while (scanf("%s %d", timeStr, &alpha) != EOF) {
		sscanf(timeStr, "%d:%d:%d", &H, &M, &S);
		int start = H * 3600 + M * 60 + S;
		int end = 11 * 3600 + 59 * 60 + 59;
		for (i = start; i <= end; ++i) {
			if (fit(i == start, i, alpha)) {
				break;
			}
		}
		if (i == end + 1) {
			for (i = 0;; ++i) {
				if (fit(false, i, alpha)) break;
			}
		}
		getTime(i, H, M, S);

		printf("Case #%d: ", ++cases);
		if (H == 0) {
			printf("00:");
		}
		else {
			printf("%02d:", H);
		}
		printf("%02d:%02d\n", M, S);

	}
	return 0;
}