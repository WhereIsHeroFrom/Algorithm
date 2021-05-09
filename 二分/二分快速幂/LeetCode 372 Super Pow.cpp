#define MAXN 1338

int F[MAXN+1], FPos[MAXN+1];

int f(int a, vector<int>& b, int c) {
    if(a % c == 0) {
        return 0;
    } 
	memset(FPos, -1, sizeof(FPos));
    int pv, nv;
	F[0] = 1 % c;
	FPos[ F[0] ] = 0;
	for(int i = 1; ; ++i) {
		F[i] = F[i-1] * a % c;
		int &pre =  FPos[ F[i] ];
		if( pre == -1) {
			pre = i;
		}else {
            pv = pre;
            nv = i;
            break;
		}
	}
    int modLen = nv - pv;
    int s = 0;
    for(int i = 0; i < b.size(); ++i) {
        s = (s * 10 + b[i]) % modLen;
    }
    return F[s];
}


class Solution {
public:
    int superPow(int a, vector<int>& b) {
        return f(a % 1337, b, 1337);
    }
};
