#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int maxn = 25;
const int inf = -1;

int n, m;
char Map[maxn][maxn];
int state[maxn][maxn][maxn][maxn];

int dir[4][2] = {
	{0, 1}, {0, -1}, {1, 0}, {-1, 0}
};

struct Point {
	int x, y;
	Point() {
	}
	Point(int _x, int _y): x(_x), y(_y) {
	}
	int getChar() {
		return Map[x][y];
	}
	
	bool operator == (const Point& other) {
		return x == other.x && y == other.y;
	}
};

Point fPoint[2];

struct State {
	Point p[2];
	
	bool isFinalState() {
		bool a = (fPoint[0] == p[0] && fPoint[1] == p[1]);
		bool b = (fPoint[0] == p[1] && fPoint[1] == p[0]);
		return a || b;
	}
	
	void setStep(int step) {
		state[p[0].x][p[0].y][p[1].x][p[1].y] = step;
	}
	
	int getStep() {
		return state[p[0].x][p[0].y][p[1].x][p[1].y];
	}
	
	State Move(int dirIdx) {
		State ret = *this;
		if(p[0].getChar() == 'H') {
			ret.p[1].x += dir[dirIdx][0];
			ret.p[1].y += dir[dirIdx][1];
			
			if(ret.p[1].getChar() == '*') {
				// 撞到墙，回退 
				ret.p[1] = p[1];
			}
			
		}else if(p[1].getChar() == 'H') {
			
			ret.p[0].x += dir[dirIdx][0];
			ret.p[0].y += dir[dirIdx][1];
			
			if(ret.p[0].getChar() == '*') {
				// 撞到墙，回退 
				ret.p[0] = p[0];
			}
		}else {
			ret.p[0].x += dir[dirIdx][0];
			ret.p[0].y += dir[dirIdx][1];
			
			if(ret.p[0].getChar() == '*') {
				ret.p[0] = p[0];
			}
			
			ret.p[1].x += dir[dirIdx][0];
			ret.p[1].y += dir[dirIdx][1];
			
			if(ret.p[1].getChar() == '*') {
				ret.p[1] = p[1];
			}
			
			// 两个球往同一个方向走，最后到了同一个位置
			// 说明前面那个球前面是无论可走的，回退状态 
			if(ret.p[0] == ret.p[1]) {
				ret = *this;
			} 
		}
		
		return ret;
	}
	
};



int bfs(State s) {
	memset(state, inf, sizeof(state));
	s.setStep(0);
	
	queue <State> Q;
	Q.push(s);
	
	while(!Q.empty()) {
		s = Q.front();
		Q.pop();
		
		if(s.isFinalState()) {
			return s.getStep();
		}
		int stp = s.getStep() + 1;
		
		for(int i = 0; i < 4; ++i) {
			State to = s.Move(i);
			if( to.getStep() == -1 ) {
				Q.push( to );
				to.setStep( stp );
			}
		}
	}
 	return -1;
}

int main() {
	int t;
	int i, j;
	scanf("%d", &t);
	
	while(t--) {
		
		scanf("%d %d", &n, &m);
		int points = 0, holes = 0;
		State s, t;
		for( i = 0; i < n; ++i) {
			scanf("%s", Map[i]);
			for(j = 0; j < m; ++j) {
				if(Map[i][j] == 'B') {
					s.p[ points++ ] = Point(i, j);	
				}else if(Map[i][j] == 'H') {
					fPoint[ holes++ ] = Point(i, j);
				}
			}
		}
		int ans = bfs(s);
		if(ans == -1) {
			printf("Sorry , sir , my poor program fails to get an answer.\n");
		}else {
			printf("%d\n", ans);
		}
	}	
	
	return 0;
} 

/* 
56
5 6
****** 
*.*BB*
*.*.**
*..HH*
****** 
*/
