#include <iostream>

using namespace std;

struct Mat {
	int a[2][2];
	void read() {
		int i, j;
		for (i = 0; i < 2; i++) {
			for (j = 0; j < 2; j++) {
				scanf("%d", &a[i][j]);
			}
		}
	}

	Mat get_rotate() {
		Mat ret;
		int i, j;
		for (i = 0; i < 2; i++) {
			for (j = 0; j < 2; j++) {
				ret.a[i][j] = a[1 - j][i];
			}
		}
		return ret;
	}

	bool equal(Mat t) {
		int i, j;
		for (i = 0; i < 2; i++) {
			for (j = 0; j < 2; j++) {
				if (a[i][j] != t.a[i][j]) {
					return false;
				}
			}
		}
		return true;
	}
}X, Y;

int main() {
	int i, t, cases = 0;
	scanf("%d", &t);

	while (t--) {
		X.read();
		Y.read();
		for (i = 0; i < 4; i++) {
			if (X.equal(Y)) {
				break;
			}
			X = X.get_rotate();
		}
		printf("Case #%d: ", ++cases);
		if (i < 4) {
			printf("POSSIBLE\n");
		}
		else {
			printf("IMPOSSIBLE\n");
		}
	}
	return 0;
}