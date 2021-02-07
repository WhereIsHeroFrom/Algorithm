#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

int n, m;
int nowRankType;

struct C {
	int goldNum, totalNum, peopleNum;
	double goldPercent;
	double totalPercent;
	int idx;
	
	void read(int i) {
		scanf("%d %d %d", &goldNum, &totalNum, &peopleNum);	
		goldPercent = goldNum * 1.0 / peopleNum;
		totalPercent = 	totalNum * 1.0 / peopleNum;	
		idx = i;
	}
	static bool cmp1(const C& a, const C& b) {
		return a.goldNum > b.goldNum;
	}
	static bool cmp2(const C& a, const C& b) {
		return a.totalNum > b.totalNum;
	}
	static bool cmp3(const C& a, const C& b) {
		return a.goldPercent > b.goldPercent;
	}	
	static bool cmp4(const C& a, const C& b) {
		return a.totalPercent > b.totalPercent;
	}	
	
	bool operator == (const C& c) {
		if(nowRankType == 1) {
			return c.goldNum == goldNum;
		}else if(nowRankType == 2) {
			return c.totalNum == totalNum;
		}else if(nowRankType == 3) {
			return fabs(c.goldPercent - goldPercent) < 1e-9;
		}else if(nowRankType == 4) {
			return fabs(c.totalPercent - totalPercent) < 1e-9;
		}
	}
}Co[100000], PCo[100000];

int getRank(int idx, int rankType) {
	if(rankType == 1) {
		sort(Co, Co + m, C::cmp1);
	}else if(rankType == 2) {
		sort(Co, Co + m, C::cmp2);
	}else if(rankType == 3) {
		sort(Co, Co + m, C::cmp3);
	}else if(rankType == 4) {
		sort(Co, Co + m, C::cmp4);
	}
	nowRankType = rankType;
	int rank = 0;
	for(int i = 0; i < m; ++i) {
		if(i == 0 || !(Co[i] == Co[i-1])  ) {
			rank = i + 1;
		}
		
		if(Co[i].idx == idx) {
			return rank;
		}
	}
	
}

int idx[10000];

int main() {
	while(scanf("%d %d", &n, &m) != EOF) {
		for(int i = 0; i < n; ++i) {
			PCo[i].read(i);
		}
		
		for(int i = 0; i < m; ++i) {
			int cIdx;
			scanf("%d", &cIdx);
			idx[i] = cIdx;
			Co[i] = PCo[ cIdx ];
		}
		
		for(int i = 0; i < m; ++i) {
			int cIdx = idx[i];
			int type = -1, optRank;
			for(int j = 1; j <= 4; ++j) {
				int rank = getRank(cIdx, j);
				if(type == -1 || (type != -1 && rank < optRank) ) {
					type = j;
					optRank = rank;
				}
			}
			printf("%d:%d\n", optRank, type);
		}
		puts("");
	}
	return  0; 
} 
 
