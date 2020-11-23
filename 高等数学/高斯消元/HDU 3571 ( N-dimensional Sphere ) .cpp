#include <iostream>

using namespace std;

#define MAXN 55
#define LL __int64
// 利用 拉宾米勒 生成的大素数
// (446744082487542857LL) 
#define MOD    (446744082487542857LL)
#define DELTA  (100000000000000000LL)

/*
高斯消元 - 同余方程
一般只要求求一个解/而且必然有解
1、解不超过某个大的素数
2、解如果有负数，需要预先加上偏移量
*/

// 计算(a + b) % n
LL AddMod(LL a, LL b, LL mod) {
	// 保证传进来的 a, b在 (-MOD, MOD)范围内
	a += b;
	if (a >= mod) a -= mod;
	while (a < 0) {
		a += mod;
	}
	return a;
}

//计算 (a * b) % mod
LL ProductMod(LL a, LL b, LL mod) {
	if (!a || !b || mod == 1) {
		return 0;
	}
	LL sum = 0;
	bool negtive = (b < 0);
	if (b < 0) b = -b;
	while (b) {
		if (b & 1) {
			sum = AddMod(sum, a, mod);
		}
		a = AddMod(a, a, mod);
		b >>= (LL)1;
	}
	sum = (sum * (negtive ? -1 : 1) + mod);
	if (sum >= mod) sum -= mod;
	return sum;
}

LL GCD(LL a, LL b) {
	if (!b) {
		return a;
	}
	return GCD(b, a%b);
}

LL ExpGcd(LL a, LL b, LL &X, LL &Y) {
	LL q, temp;
	if (!b) {
		q = a; X = 1; Y = 0;
		return q;
	}
	else {
		q = ExpGcd(b, a % b, X, Y);
		temp = X;
		X = Y;
		Y = temp - (a / b) * Y;
		return q;
	}
}



class GaussMatrix {
public:
	int r, c;
	LL d[MAXN][MAXN];
	LL x[MAXN];       // 某个解集 
	LL  xcnt;          // 解集个数 

	LL ABS(LL v) {
		return v < 0 ? -v : v;
	}

	void swap_row(int ra, int rb) {
		for (int i = 0; i <= c; i++) {
			LL tmp = d[ra][i];
			d[ra][i] = d[rb][i];
			d[rb][i] = tmp;
		}
	}
	void swap_col(int ca, int cb) {
		for (int i = 0; i < r; i++) {
			LL tmp = d[i][ca];
			d[i][ca] = d[i][cb];
			d[i][cb] = tmp;
		}
	}

	void getAns(LL mod) {
		for (int i = c - 1; i >= 0; i--) {
			LL tmp = d[i][c];
			// d[i][i] * x[i] + (d[i][i+1]*x[i+1] + ... + d[i][c]*x[c]) = K*mod + tmp;
			for (int j = i + 1; j < c; j++) {
				tmp -= ProductMod(d[i][j], x[j], mod);
				tmp = (tmp % mod + mod) % mod;
			}
			// d[i][i] * x[i] = K * mod + tmp;
			// d[i][i] * x[i] + (-K) * mod = tmp;
			// a * x[i] + b * (-K) = tmp;
			LL X, Y;
			ExpGcd(d[i][i], mod, X, Y);
			x[i] = ProductMod(X % mod, tmp, mod);
		}
	}

	// -1 表示无解 
	LL gauss(LL mod) {
		int i, j, k;
		int col, maxrow;

		// 枚举行，步进列 
		for (i = 0, col = 0; i < r && col < c; i++) {
			//debug_print();
			maxrow = i;
			// 找到i到r-1行中col元素最大的那个值 
			for (j = i + 1; j < r; j++) {
				if (ABS(d[j][col]) > ABS(d[maxrow][col])){
					maxrow = j;
				}
			}
			// 最大的行和第i行交换 
			if (maxrow != i) {
				swap_row(i, maxrow);
			}
			if (d[i][col] == 0) {
				// 最大的那一行的当前col值 等于0，继续找下一列
				col++;
				i--;
				continue;
			}

			for (j = i + 1; j < r; j++) {
				if (d[j][col]) {
					// 当前行的第col列如果不为0，则进行消元
					// 以期第i行以下的第col列的所有元素都消为0 
					LL lastcoff = d[i][col];
					LL nowcoff = d[j][col];
					for (k = col; k <= c; k++) {
						d[j][k] = (ProductMod(d[j][k], lastcoff, mod) - ProductMod(d[i][k], nowcoff, mod));
						if (d[j][k] < 0) d[j][k] += mod;
						else if (d[j][k] >= mod) d[j][k] -= mod;
					}
				}
			}
			col++;
		}
		// i表示从i往后的行的矩阵元素都为0 
		// 存在 (0 0 0 0 0 0 d[j][c]) (d[j][c] != 0) 的情况，方程无解 
		for (j = i; j < r; j++) {
			if (d[j][c]) {
				return -1;
			}
		}
		// 自由变元数 为 (变量数 - 非零行的数目)
		int free_num = c - i;

		// 交换列，保证最后的矩阵为严格上三角，并且上三角以下的行都为0 
		for (i = 0; i < r && i < c; i++) {
			if (!d[i][i]) {
				// 对角线为0 
				for (j = i + 1; j < c; j++) {
					// 在该行向后找第一个不为0的元素所在的列，交换i和这一列 
					if (d[i][j]) break;
				}
				if (j < c) {
					swap_col(i, j);
				}
			}
		}
		xcnt = (((LL)1) << (LL)free_num);

		getAns(mod);
		return xcnt;
	}

	void debug_print() {
		int i, j;
		printf("-------------------------------\n");
		for (i = 0; i < r; i++) {
			for (j = 0; j <= c; j++) {
				printf("%I64d ", d[i][j]);
			}
			puts("");
		}
		printf("-------------------------------\n");
	}
};

LL v[MAXN][MAXN];

int main() {
	int t;
	int i, j, k;
	int cases = 1;
	int n;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (i = 0; i < n + 1; i++) {
			for (j = 0; j < n; j++) {
				scanf("%I64d", &v[i][j]);
				v[i][j] += DELTA;
				v[i][j] = (v[i][j] % MOD + MOD) % MOD;
				// 由于值有可能是负数，同余求出来的肯定为非负，
				// 所以初始化需要加上一个数，保证他一定大于等于0
			}
		}
		GaussMatrix M;
		M.r = M.c = n;
		for (i = 0; i < M.r; i++) {
			for (j = 0; j <= M.c; j++) {
				if (j < M.c) {
					M.d[i][j] = ProductMod(2, ((v[i + 1][j] - v[i][j]) % MOD + MOD) % MOD, MOD);
					if (M.d[i][j] < 0) M.d[i][j] += MOD;
				}
				else {
					LL s = 0;
					for (k = 0; k < M.r; k++) {
						s += (ProductMod(v[i + 1][k], v[i + 1][k], MOD) - ProductMod(v[i][k], v[i][k], MOD));
						s %= MOD;
						if (s<0) s += MOD;
					}
					M.d[i][j] = s;
				}
			}
		}

		M.gauss(MOD);
		printf("Case %d:\n", cases++);
		for (i = 0; i < M.c; i++) {
			if (i) printf(" ");
			printf("%I64d", M.x[i] - DELTA);
		}
		puts("");

	}
	return 0;
}


/*
10
2
1 0
-1 0
0 1

3
2 2 3
0 2 3
1 3 3
1 2 4

*/