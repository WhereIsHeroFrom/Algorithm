#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

#define MAXR 250
#define MAXC 35
#define INF -1
#define INT64 __int64 

enum eCoverType {
	ECT_EXACT = 0,       // 精确覆盖
	ECT_REPEAT = 1,      // 重复覆盖
};

/*
DLXNode
left, right        十字交叉双向循环链表的左右指针
up, down           十字交叉双向循环链表的上下指针

<用于列首结点>
colSum             列的结点总数
colIdx             列的编号

<用于行首结点/元素结点>
colHead            指向列首结点的指针
rowIdx             DLXNode结点在原矩阵中的行标号
*/
class DLXNode {
public:
	DLXNode *left, *right, *up, *down;
	union {
		struct {
			DLXNode *colHead;
			int rowIdx;
		}node;
		struct {
			int colIdx;
			int colSum;
		}col;
	}data;
public:
	//////////////////////////////////////////////////////////
	// 获取/设置 接口
	void resetCol(int colIdx);
	void resetColSum();
	void updateColSum(int delta);
	int getColSum();

	void setColIdx(int colIdx);
	int getColIdx();

	void setColHead(DLXNode *colPtr);
	DLXNode *getColHead();

	void setRowIdx(int rowIdx);
	int getRowIdx();

	///////////////////////////////////////////////////////////
	// 搜索求解用到的接口
	void appendToCol(DLXNode *colPtr);
	void appendToRow(DLXNode *rowPtr);

	void deleteFromCol();
	void resumeFromCol();

	void deleteFromRow();
	void resumeFromRow();
	///////////////////////////////////////////////////////////
};

void DLXNode::resetCol(int colIdx) {
	// IDA*的时候需要用到列下标进行hash
	setColIdx(colIdx);
	// 初始化每列结点个数皆为0
	resetColSum();
}
void DLXNode::resetColSum() {
	data.col.colSum = 0;
}

void DLXNode::updateColSum(int delta) {
	data.col.colSum += delta;
}

int DLXNode::getColSum() {
	return data.col.colSum;
}

void DLXNode::setColIdx(int colIdx) {
	data.col.colIdx = colIdx;
}
int DLXNode::getColIdx() {
	return data.col.colIdx;
}

void DLXNode::setColHead(DLXNode * colPtr) {
	data.node.colHead = colPtr;
}

DLXNode* DLXNode::getColHead() {
	return data.node.colHead;
}

void DLXNode::setRowIdx(int rowIdx) {
	data.node.rowIdx = rowIdx;
}

int DLXNode::getRowIdx() {
	return data.node.rowIdx;
}

void DLXNode::appendToCol(DLXNode * colPtr) {
	// 赋值列首指针
	setColHead(colPtr);

	// 这几句要求插入结点顺序保证列递增，否则会导致乱序（每次插在一列的最后）
	up = colPtr->up;
	down = colPtr;
	colPtr->up = colPtr->up->down = this;

	// 列元素++
	colPtr->updateColSum(1);
}

void DLXNode::appendToRow(DLXNode* rowPtr) {
	// 赋值行编号
	setRowIdx(rowPtr->getRowIdx());

	// 这几句要求插入结点顺序保证行递增（每次插在一行的最后）
	left = rowPtr->left;
	right = rowPtr;
	rowPtr->left = rowPtr->left->right = this;
}

void DLXNode::deleteFromCol() {
	left->right = right;
	right->left = left;
}

void DLXNode::resumeFromCol() {
	right->left = left->right = this;
}

void DLXNode::deleteFromRow() {
	up->down = down;
	down->up = up;
	if (getColHead())
		getColHead()->updateColSum(-1);
}

void DLXNode::resumeFromRow() {
	if (getColHead())
		getColHead()->updateColSum(1);
	up->down = down->up = this;
}

/*
DLX （单例）
head               head 只有左右（left、right）两个指针有效，指向列首
rowCount, colCount 本次样例矩阵的规模（行列数）
row[]              行首结点列表
col[]              列首结点列表

dlx_pool           结点对象池（配合dlx_pool_idx取对象）
*/
class DLX {
	DLXNode *head;             // 总表头
	int rowCount, colCount;    // 本次样例矩阵的规模（行列数） 
	DLXNode *row, *col;        // 行首结点列表 / 列首结点列表

	DLXNode *dlx_pool;         // 结点对象池
	int dlx_pool_idx;          // 结点对象池下标

	eCoverType eCType;
	int  *col_coverd;          // 标记第i列是否覆盖，避免重复覆盖
	INT64 *row_code;           // 每行采用二进制标记进行优化
	int limitColCount;         // 限制列的个数
	// 即 前 limitColCount 列满足每列1个"1"，就算搜索结束
	// 一般情况下 limitColCount == colCount 
public:
	int *result, resultCount;  // 结果数组

private:
	DLX() {
		dlx_pool_idx = 0;
		head = NULL;
		dlx_pool = new DLXNode[MAXR*MAXC];
		col = new DLXNode[MAXC + 1];
		row = new DLXNode[MAXR];
		result = new int[MAXR];
		col_coverd = new int[MAXC + 1];
		row_code = new INT64[MAXR];
	}

	~DLX() {
		delete[] dlx_pool;
		delete[] col;
		delete[] row;
		delete[] result;
		delete[] col_coverd;
		delete[] row_code;
	}

	void reset_size(int r, int c, int limitC = INF, eCoverType ect = ECT_EXACT) {
		rowCount = r;
		colCount = c;
		limitColCount = limitC != INF ? limitC : c;
		eCType = ect;
		dlx_pool_idx = 0;
		resultCount = -1;
	}

	void reset_col();
	void reset_row();
	DLXNode* get_node();
	DLXNode* get_min_col();
	int get_eval();                // 估价函数

	void cover(DLXNode *colPtr);
	void uncover(DLXNode *colPtr);

	void coverRow(DLXNode *nodePtr);
	void uncoverRow(DLXNode *nodePtr);

	bool isEmpty();
public:

	void init(int r, int c, int limitC, eCoverType ect);
	void add(int rowIdx, int colIdx);       // index 0-based
	void output();
	bool dance(int depth, int maxDepth);
	void preCoverRow(int rowIndex);

	static DLX& Instance() {
		static DLX inst;
		return inst;
	}
};

void DLX::reset_col() {
	// [0, colCount)作为列首元素，
	// 第colCount个列首元素的地址作为总表头head
	for (int i = 0; i <= colCount; ++i) {
		DLXNode *colPtr = &col[i];
		colPtr->resetCol(i);
		// 初始化，每列元素为空，所以列首指针上下循环指向自己
		colPtr->up = colPtr->down = colPtr;
		// 第i个元素指向第i-1个，当i==0，则指向第colCount个，构成循环
		colPtr->left = &col[(i + colCount) % (colCount + 1)];
		// 第i个元素指向第i+1个，当i==colCount，则指向第0个，构成循环
		colPtr->right = &col[(i + 1) % (colCount + 1)];
		col_coverd[i] = 0;
	}
	// 取第colCount个列首元素的地址作为总表头
	head = &col[colCount];
}

void DLX::reset_row() {
	for (int i = 0; i < rowCount; ++i) {
		// 初始化行首结点
		DLXNode *rowPtr = &row[i];
		// 初始化行，每行都为空，所以结点的各个指针都指向自己
		rowPtr->left = rowPtr->right = rowPtr->up = rowPtr->down = rowPtr;
		// 对应cover时候的函数入口的非空判断
		rowPtr->setColHead(NULL);
		rowPtr->setRowIdx(i);
		row_code[i] = 0;
	}
}

DLXNode* DLX::get_node() {
	return &dlx_pool[dlx_pool_idx++];
}

void DLX::init(int r, int c, int limitC, eCoverType ect) {
	reset_size(r, c, limitC, ect);
	reset_row();
	reset_col();
}

DLXNode* DLX::get_min_col() {
	DLXNode *resPtr = head->right;
	for (DLXNode *ptr = resPtr->right; ptr != head; ptr = ptr->right) {
		if (ptr->getColIdx() >= limitColCount)
			break;
		if (ptr->getColSum() < resPtr->getColSum()) {
			resPtr = ptr;
		}
	}
	return resPtr;
}

/*
功能：估价函数
注意：估计剩余列覆盖完还需要的行的个数的最小值 <= 实际需要的最小值
*/
int DLX::get_eval() {
	int eval = 0;
	INT64 row_status = 0;
	DLXNode *colPtr;

	// 枚举每一列
	for (colPtr = head->right; colPtr != head; colPtr = colPtr->right) {
		int colIdx = colPtr->getColIdx();
		if (!(row_status & ((INT64)1) << colIdx)) {
			row_status |= (((INT64)1) << colIdx);
			++eval;
			// 枚举该列上的么个元素
			for (DLXNode *nodePtr = colPtr->down; nodePtr != colPtr; nodePtr = nodePtr->down) {
				row_status |= row_code[nodePtr->getRowIdx()];
			}
		}
	}
	return eval;
}

/*
功能：插入一个(rowIdx, colIdx)的结点（即原01矩阵中(rowIdx, colIdx)位置为1的）
注意：按照行递增、列递增的顺序进行插入
*/
void DLX::add(int rowIdx, int colIdx) {
	DLXNode *nodePtr = get_node();
	// 将结点插入到对应列尾
	nodePtr->appendToCol(&col[colIdx]);
	// 将结点插入到对应行尾
	nodePtr->appendToRow(&row[rowIdx]);
	row_code[rowIdx] |= ((INT64)1 << colIdx);
}

/*
功能：输出当前矩阵
调试神器
*/
void DLX::output() {
	for (int i = 0; i < rowCount; i++) {
		DLXNode *rowPtr = &row[i];
		printf("row(%d)", i);
		for (DLXNode *nodePtr = rowPtr->right; nodePtr != rowPtr; nodePtr = nodePtr->right) {
			printf(" [%d]", nodePtr->getColHead()->getColIdx());
		}
		puts("");
	}
}

/*
功能：删除行
精确覆盖在删除列的时候，需要对行进行删除处理
枚举每个和nodePtr在同一行的结点p，执行删除操作
*/
void DLX::coverRow(DLXNode* nodePtr) {
	for (DLXNode *p = nodePtr->right; p != nodePtr; p = p->right) {
		p->deleteFromRow();
	}
}

/*
功能：恢复行
coverRow的逆操作
*/
void DLX::uncoverRow(DLXNode* nodePtr) {
	for (DLXNode *p = nodePtr->left; p != nodePtr; p = p->left) {
		p->resumeFromRow();
	}
}

/*
功能：覆盖colPtr指向的那一列
说是覆盖，其实是删除那一列。
如果是精确覆盖，需要删除那列上所有结点对应的行，原因是，cover代表我会选择这列，这列上有1的行必须都删除
*/
void DLX::cover(DLXNode *colPtr) {
	if (!colPtr) {
		return;
	}
	if (!col_coverd[colPtr->getColIdx()]) {
		// 删除colPtr指向的那一列
		colPtr->deleteFromCol();
		// 枚举每个在colPtr对应列上的结点p
		if (eCType == ECT_EXACT) {
			for (DLXNode* nodePtr = colPtr->down; nodePtr != colPtr; nodePtr = nodePtr->down) {
				coverRow(nodePtr);
			}
		}
	}
	++col_coverd[colPtr->getColIdx()];
}

/*
功能：恢复colPtr指向的那一列
cover的逆操作
*/
void DLX::uncover(DLXNode* colPtr) {
	if (!colPtr) {
		return;
	}
	--col_coverd[colPtr->getColIdx()];
	if (!col_coverd[colPtr->getColIdx()]) {
		// 枚举每个在colPtr对应列上的结点p
		if (eCType == ECT_EXACT) {
			for (DLXNode* nodePtr = colPtr->up; nodePtr != colPtr; nodePtr = nodePtr->up) {
				uncoverRow(nodePtr);
			}
		}
		// 恢复colPtr指向的那一列
		colPtr->resumeFromCol();
	}
}

/*
功能：用于预先选择某行
*/
void DLX::preCoverRow(int rowIndex) {
	DLXNode *rowPtr = &row[rowIndex];
	for (DLXNode *p = rowPtr->right; p != rowPtr; p = p->right) {
		cover(p->getColHead());
	}
}

bool DLX::isEmpty() {
	if (head->right == head) {
		return true;
	}
	return head->right->getColIdx() >= limitColCount;
}

bool DLX::dance(int depth, int maxDepth = INF) {
	// 当前矩阵为空，说明找到一个可行解，算法终止 
	if (isEmpty()) {
		resultCount = depth;
		return true;
	}
	if (maxDepth != INF) {
		if (depth + get_eval() > maxDepth) {
			return false;
		}
	}

	DLXNode *minPtr = get_min_col();
	// 删除minPtr指向的列 
	cover(minPtr);
	// minPtr为结点数最少的列，枚举这列上所有的行
	for (DLXNode *p = minPtr->down; p != minPtr; p = p->down) {
		// 令r = p->getRowIdx()，行r放入当前解 
		result[depth] = p->getRowIdx();
		// 行r上的结点对应的列进行删除 
		for (DLXNode *q = p->right; q != p; q = q->right) {
			cover(q->getColHead());
		}
		// 进入搜索树的下一层 
		if (dance(depth + 1, maxDepth)) {
			return true;
		}
		// 行r上的结点对应的列进行恢复 
		for (DLXNode *q = p->left; q != p; q = q->left) {
			uncover(q->getColHead());
		}
	}
	// 恢复minPtr指向的列
	uncover(minPtr);
	return false;
}

#define MAXN 20
int N, M;
char str[MAXN][MAXN];

int dir[4][2] = {
	{ 0, 1 },
	{ 0, -1 },
	{ 1, 0 },
	{ -1, 0 }
};

struct oWall {
	int idx;
	int r, c;
	oWall(){
	}
	oWall(int _idx, int _r, int _c) {
		idx = _idx;
		r = _r;
		c = _c;
	}
}ow[50];
int wall_cnt;
int hash_wall[MAXN][MAXN];

int mat[MAXR][MAXC];

bool is_border(int r, int c) {
	return r < 0 || c < 0 || r >= N || c >= M;
}

int main() {
	int i, j, k;
	while (scanf("%d %d", &N, &M) != EOF) {
		memset(hash_wall, -1, sizeof(hash_wall));
		memset(mat, 0, sizeof(mat));

		for (i = 0; i < N; ++i) {
			scanf("%s", str[i]);
		}
		wall_cnt = 0;
		for (i = 0; i < N; ++i) {
			for (j = 0; j < M; ++j) {
				if (str[i][j] == '#') {
					ow[wall_cnt] = oWall(wall_cnt, i, j);
					hash_wall[i][j] = wall_cnt++;
				}
			}
		}

		int row_cnt = 0;
		for (i = 0; i < N; ++i) {
			for (j = 0; j < M; ++j) {
				if (str[i][j] == '.'){
					for (k = 0; k < 4; k++) {
						int ti = i, tj = j;
						while (1) {
							ti = ti + dir[k][0];
							tj = tj + dir[k][1];
							if (is_border(ti, tj)) break;
							char &cb = str[ti][tj];
							if (cb == '#') {
								int colIdx = hash_wall[ti][tj];
								mat[row_cnt][colIdx] = 1;
								//printf("%d %d\n", row_cnt, colIdx);
								break;
							}
							else if (cb == '.'){

							}
							else {
								break;
							}
						}
					}
					++row_cnt;
				}
			}
		}
		DLX &dlx = DLX::Instance();
		dlx.init(row_cnt, wall_cnt, INF, ECT_REPEAT);

		for (i = 0; i < row_cnt; i++) {
			for (j = 0; j < wall_cnt; j++) {
				if (mat[i][j]) {
					dlx.add(i, j);
				}
			}
		}
		for (i = 0; i < row_cnt; i++) {
			if (dlx.dance(0, i)) break;
		}
		printf("%d\n", i);

	}
	return 0;
}