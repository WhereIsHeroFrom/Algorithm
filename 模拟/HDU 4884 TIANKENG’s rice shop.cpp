/*
	题意：
	n：  代表 n 种米饭 （对应kindid）；
	t：  一次炒饭耗费的时间 
	k：  最多 k 碗相同 kind 的米饭可以在一起炒
	m：  m 个客人  
	
	n,t,k,m
	time, kindid, num 
*/ 

#include <iostream>
#include <cstring>

using namespace std;

struct Co {
	int time;
	int kind, num;
	int endtime; 
	Co() {
	}
	Co(int t, int k, int n) {
		time = t;
		kind = k;
		num = n;
	}
}C[1100];

int getT(char *s) {
	return ((s[0]-'0')*10 + s[1]-'0') * 60 + ((s[3]-'0')*10 + s[4]-'0');
}

void puttime(int time) {
	int hour = time / 60;
	int min = time % 60;
	
	if(hour >= 24) hour %= 24;
	printf("%02d:%02d\n", hour, min);
}

int has[1100];

int main() {
	
	int n, t, k, m;
	int cas, i;
	
	scanf("%d", &cas);
	while(cas--) {
		scanf("%d %d %d %d", &n, &t, &k, &m);
		
		for(i = 0; i < m; ++i) {
			char ch[10];
			int kindid, num;
			scanf("%s %d %d", ch, &kindid, &num);
			C[i] = Co( getT(ch), kindid, num );	
		}
		
		int endTime = 0;
		memset(has, 0, sizeof(has));
		
		while(1) {
			
			int cur = -1; 
			for(i = 0; i < m; ++i) {
				if( !has[i] ) {
					cur = i;
					break;
				}
			}
			if(cur == -1) {
				break;
			}
			if(endTime < C[cur].time) {
				endTime = C[cur].time;
			}
			
			// 开始炒饭的时间是 endTime 
			// 处理这个区间段的炒饭，更新每个的结束时间 
			i = cur;
				
			int kind = C[i].kind;
			int num = C[i].num;
			int cnt = (num + k - 1) / k; 
			int rem = cnt * k - num;
			
			C[i].endtime = endTime + t * cnt;
			endTime = C[i].endtime;
			has[i] = 1;
			
			if ( !rem )  {
				continue;
			}
			
			for(int j = i + 1; j < m; ++j) {
				if(has[j]) {
					continue;
				}
				if(C[j].kind != kind) {
					continue;
				}
				
				if(C[j].time <= endTime - t) {
					if( C[j].num <= rem ) {
						rem -= C[j].num;
						has[j] = 1;
						C[j].endtime = endTime;
					}else {
						C[j].num -= rem;
						rem = 0;
						break;	
					}
				}
			}			
		}

		for(i = 0; i < m; ++i) {
			puttime(C[i].endtime);
		}
		
		if(cas) {
			puts("");
		}
	}
	
	return 0;
} 

/*
6
1 9 4 1
08:00 1 10

2 1 4 2
08:00 1 5
09:00 2 1

2 5 4 3
08:00 1 4
08:01 2 2
08:02 2 2

2 5 4 2
08:00 1 1
08:04 1 1

2 5 4 4
08:00 1 4
08:01 2 2
08:02 1 1
08:03 2 10

2 5 6 4
08:00 1 4
08:01 2 2
08:02 1 1
08:03 2 4

1 10 12 6
08:00 1 13
08:01 1 2
08:02 1 2
08:03 2 2
08:04 2 2
08:05 1 6


*/ 
