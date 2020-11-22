/*
题意：给定 NAND 操作：
0 NAND 0 = 1
0 NAND 1 = 1
1 NAND 0 = 1
1 NAND 1 = 0
然后是 N <= 200000 次操作，包含：

1) PUSH x ：  往栈顶放一个元素 x (x=0,1)； 
2) POP :      弹出一个栈顶元素； 
3) REVERSE：  对栈执行反序操作； 
4) QUERY：    求从栈顶到栈底元素的  NAND 和； 

题解：
用一个双端队列， REVERSE 操作只需要交换指针方向；

PUSH 的是按照如下规则：
1. 队列为空的情况，直接插入 
2. 队列对应元素为0，无论哪个方向都直接插入 
3. 队列对应元素大于1，肯定是多个1累加起来的 
3.1 插入元素也为1，直接在原来元素基础上自增
3.2 插入元素为 0，往两边方向插入新的值 

POP 是按照如下规则进行的：  
1. 队列为空，无法 POP 
2. 所在位置有一个 0 元素，则 POP 完偏移指针 
3. 所在位置有若干个1，则 POP完，如果变成0以后，进行指针偏移

REVERSE 的操作直接交换指针方向；

QUERY 的是按照如下规则：

1. 空队列直接输出 Invalid.
2. 当对应元素 cur = 0
2.1 如队列长度为1，则输出0； 
2.2 如队列长度大于1，则输出1； 

3. 当对应元素 cur > 1
3.1 如果队列长度小于等于2，输出 cur & 1；
3.2 如果队列长度大于2，输出 !(cur & 1)； 

*/ 

#include <iostream>
#include <cstring> 
using namespace std;

#define START 200000

int Q[400010];
int ileft, iright;
int dir;

void resetQueue() {
	ileft = iright = START;
	Q[START] = -1;
}

void initQueue() {
	dir = 1;
	resetQueue();
}

void addEleByDir(int dir, int v) {
	if(dir == 1) {
		Q[++iright] = v;	
	}else {
		Q[--ileft] = v;
	}
}

void popEleByDir(int dir) {
	if(dir == 1) {
		--iright;
	}else {
		++ileft;
	}
	if(ileft > iright) {
		resetQueue();		
	}
}

int getQueueSize() {
	if(Q[ileft] == -1) {
		return 0;
	}
	return iright - ileft + 1;	
}

void Output() {
	for(int i = ileft; i <= iright; ++i) {
		printf("%d ", Q[i]);
	} 	
	puts("");
}

int main() {
	int t;
	int m, cas = 0;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &m);
		initQueue();
		
		printf("Case #%d:\n", ++cas);
		while(m--) {
			char str[100];
			scanf("%s", str);
			
			
			if( !strcmp(str, "PUSH") ) {
				int v;
				int &p = (dir==1) ? Q[iright] : Q[ileft];
				scanf("%d", &v);
				
				if(p == -1) {
					// 队列为空的情况，直接插入 
					p = v;
				}else if(p == 0){
					// 队列对应元素为0，无论哪个方向都直接插入 
					addEleByDir(dir, v);
				}else if(p >= 1) {
					// 队列对应元素为1，肯定是多个1累加起来的 
					if(v == 1) {
						// 插入元素也为1，直接在原来元素基础上自增
						p ++; 
					}else {
						// 插入元素为 0，往两边方向插入新的值 
						addEleByDir(dir, v);
					}
				}
			}else if( !strcmp(str, "POP") ) {
				int &p = (dir==1) ? Q[iright] : Q[ileft];
				if(p == -1) {
					// 队列为空，无法 POP 
				} else if( p == 0 ) {
					// 所在位置有一个 0 元素，则 POP 完偏移指针 
					popEleByDir(dir);
				} else if(p >= 1) {
					// 所在位置有若干个1，则 POP完，判空后进行指针偏移
					p--;
					if(p == 0) {
						popEleByDir(dir);
					} 
				}
				
			}else if( !strcmp(str, "REVERSE") ) {
				dir *= -1;
			}else if( !strcmp(str, "QUERY") ) { 
				int &p = (dir==1) ? Q[ileft] : Q[iright];
				if(p == -1) {
					printf("Invalid.\n");
				}else if (p == 0) {
					// 只有一个元素，那就是0无疑；
					// 如果一旦有多个元素，任何和0操作完都等于1 
					int val = getQueueSize()==1 ? 0 : 1;
					printf("%d\n", val);
				}else {
					int now;
					if(getQueueSize() == 1) {
						// 如果只有一个元素
						now = (p&1); 
					}else if(getQueueSize() == 2) {
						// 那一个必定是 0，操作完就是： 
						now = (p&1); 
					}else {
						// 否则前面所有数操作完一定是 1，再和1 NAND 之后得到：
						now = (p&1)?0:1;
					}
					
					printf("%d\n", now  );
				}
			} 
			
			//Output();
		}
	}
	return 0;
} 
