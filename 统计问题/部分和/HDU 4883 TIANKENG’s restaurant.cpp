#include <iostream>
#include <cstring>
using namespace std;

const int MAXT = 24*60+10;

int MaxT[MAXT];

int getT(char *str) {
	return ((str[0]-'0')*10 + str[1]-'0') *60 + (str[3]-'0')*10 + (str[4]-'0');
}

int main() {
	int t;
	int n, v, i;
	char S[10], T[10];
	
	scanf("%d", &t);
	
	while(t--) {
		memset(MaxT, 0, sizeof(MaxT));
		
		scanf("%d", &n);
		for(i = 0; i < n; ++i) {
			scanf("%d", &v);
			scanf("%s %s", S, T);
			MaxT[ getT(S) ] += v;
			MaxT[ getT(T) ] -= v;
			//printf("%d %d\n", getT(S), getT(T));
		}
		int Max = 0;
		int s = 0;
		for(i = 0; i < MAXT; ++i) {
			s += MaxT[i];
			if(s > Max) Max = s;
		}
		printf("%d\n", Max);
	}
	
	return 0;
} 
