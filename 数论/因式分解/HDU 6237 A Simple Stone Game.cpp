#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAXN 100010

#define ll long long
#define MAXP 100000
int notprime[MAXP + 1];
int primes[MAXP];

struct factorComp {
	ll prime_;
	int num_;
	factorComp(ll prime, int num){
		prime_ = prime;
		num_ = num;
	}
	print() {
		printf("prime = %lld, count = %d\n", prime_, num_);
	}
};

void Eratosthenes() {
	notprime[0] = notprime[1] = true;
	primes[0] = 0;
	for (int i = 2; i < MAXP; i++) {
		if (!notprime[i]) {
			primes[++primes[0]] = i;
			// 注意整数乘积超过int32
			for (ll j = (ll)i*i; j < MAXP; j += i) {
				notprime[j] = true;
			}
		}
	}
}

void Factorization(ll value, vector<factorComp> &vf) {
	int i;
	vf.clear();
	for (i = 1; i <= primes[0]; i++) {
		if ((ll)i*i > value) {
			break;
		}
		int nowprime = primes[i];
		if (!(value % nowprime)) {
			factorComp f(nowprime, 0);
			while (!(value % nowprime)) {
				value /= nowprime;
				f.num_++;
			}
			vf.push_back(f);
		}
	}
	if (value > 1) {
		vf.push_back(factorComp(value, 1));
	}
}

void printFactor(vector<factorComp> &vf) {
	for (int i = 0; i < vf.size(); i++) {
		vf[i].print();
	}
}

int a[MAXN], b[MAXN];

int main() {
	Eratosthenes();

	// test
	//vector<factorComp> vf;
	//Factorization(3033, vf);
	//printFactor(vf);

	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		int i, j;
		ll sum = 0;
		scanf("%d", &n);
		for (i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			sum += (ll)a[i];
		}
		vector<factorComp> vf;
		Factorization(sum, vf);
		ll ans = -1;
		for (i = vf.size() - 1; i >= 0; i--) {
			ll p = vf[i].prime_;
			for (j = 0; j < n; j++) {
				b[j] = a[j] % p;
			}
			sort(b, b + n);
			ll now = 0;
			int start = 0;
			//printf("%d %d %d %d %d\n", b[0], b[1], b[2], b[3], b[4]);
			for (j = n - 1; j >= 0; j--) {
				if (ans >= 0 && now > ans) {
					break;
				}
				if (!b[j]) {
					break;
				}
				ll need = p - b[j];
				now += need;
				while (need && start < j) {
					if (!b[start]) {
						start++;
						continue;
					}
					if (b[start] <= need) {
						need -= b[start];
						b[start] = 0;
					}
					else {
						b[start] -= need;
						need = 0;
					}
				}

			}
			//printf("%lld %lld\n", now, p); 
			if (ans == -1 || now < ans) {
				ans = now;
			}
		}
		printf("%lld\n", ans);

	}
	return 0;
}


/*
5

3
9997 9998 9999

5
6 7 8 9 5

5
100000 9999 1 1 1
