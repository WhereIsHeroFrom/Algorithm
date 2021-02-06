
/*
    坐标旋转 45 度角以后，原本坐标为 (x,y)， 变换为  (x+y-1, y-x+1)

    二维树状数组 进行下标映射的时候不用数组，采用整数哈希进行映射
*/

#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;


//***************************************** 二维树状数组 模板 *****************************************
#define ll int

int c[2520010];
int bins[2520010], binSize;

int lowbit(int x) {
    return x & (-x);
}

void pre(int x, int xmax, int y, int ymax) {
    while (x <= xmax) {
        int ty = y;
        while (ty <= ymax) {
            bins[binSize++] = (x * (ymax + 1) + ty);
            ty += lowbit(ty);
        }
        x += lowbit(x);
    }
}

void filterpre() {
    int size = 1;
    sort(bins, bins + binSize);
    for (int i = 1; i < binSize; ++i) {
        if (bins[i] != bins[size-1]) {
            bins[size++] = bins[i];
        }
    }
    binSize = size;
}

int BinGetPre(int now) {
    int l = 0;
    int r = binSize - 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (bins[mid] == now) {
            return mid;
        }
        else if (now < bins[mid]) {
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    return -1;
}


void clear() {
    memset(c, 0, sizeof(c));
}

void add(int x, int xmax, int y, int ymax, int v) {
    while (x <= xmax) {
        int ty = y;
        while (ty <= ymax) {
            int key = BinGetPre((x * (ymax + 1) + ty));
            c[key] += v;
            ty += lowbit(ty);
        }
        x += lowbit(x);
    }
}

ll sum(int x, int y, int ymax) {
    ll s = 0;
    while (x >= 1) {
        int ty = y;
        while (ty >= 1) {
            int key = BinGetPre((x * (ymax + 1) + ty));
            if (key != -1)
                s += c[key];

            ty -= lowbit(ty);
        }
        x -= lowbit(x);
    }
    return s;
}
//***************************************** 二维树状数组 模板 *****************************************

void xyRotate(int x, int y, int& outx, int& outy) {
    outx = (x + y - 4) / 2;
    outy = (y - x - 2) / 2;
}
int X[4*80010], Y[4*80010];
int XSize, YSize;

void addX(int value) {
    X[++XSize] = value;
}

void addY(int value) {
    Y[++YSize] = value;
}

void processXY(int x, int y) {
    int X, Y;
    xyRotate(x, y, X, Y);
    addX(X);
    addY(Y);
}

void sortXY() {
    sort(X + 1, X + XSize + 1);
    sort(Y + 1, Y + YSize + 1);
    int tmp = 1;
    for (int i = 2; i <= XSize; ++i) {
        if (X[i] != X[tmp]) {
            X[++tmp] = X[i];
        }
    }
    XSize = tmp;

    tmp = 1;
    for (int i = 2; i <= YSize; ++i) {
        if (Y[i] != Y[tmp]) {
            Y[++tmp] = Y[i];
        }
    }
    YSize = tmp;
}

int BinGet(int now, int val[], int valsize) {
    int l = 1;
    int r = valsize;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (val[mid] == now) {
            return mid;
        }
        else if(now < val[mid]) {
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
}

struct Point {
    int x, y;
    int tp, z;
    void read() {
        //scanf("%d %d %d %d", &tp, &x, &y, &z);
        tp = rand() % 2 + 1;
        x = rand() % 10000 + 1;
        y = rand() % 10000 + 1;
        z = rand() % 1000;
        scanf("%d %d %d %d", &tp, &x, &y, &z);

        x <<= 1;
        y <<= 1;
        z <<= 1;

        if (tp == 1) {
            processXY(x, y);
        }
        else {
            // 矩形右下角，没有任何套路
            processXY(x, y + z);

            // 矩形左上角
            processXY(x, y - z - 2);
            
            // 矩形右上角
            processXY(x - z - 1, y - 1);
            
            // 矩形左下角
            processXY(x + z + 1, y - 1);

        }
    }
}P[80010];


void getXY(int x, int y, int& outx, int& outy) {
    xyRotate(x, y, outx, outy);
    outx = BinGet(outx, X, XSize);
    outy = BinGet(outy, Y, YSize);
}


int main() {
    int n, m, i;
    while (scanf("%d %d", &n, &m) != EOF && n) {
        clear();
        XSize = YSize = 0;
        for (i = 0; i < m; ++i){
            P[i].read();
        }
        sortXY();
        binSize = 0;

        for (i = 0; i < m; ++i){
            int x, y;
            if (P[i].tp == 1) {
                getXY(P[i].x, P[i].y, x, y);
                pre(x, XSize, y, YSize);
            }
        }
        filterpre();

        for (i = 0; i < m; ++i){
            int x = 0, y = 0;
            if (P[i].tp == 1) {
                getXY(P[i].x, P[i].y, x, y);
                add(x, XSize, y, YSize, P[i].z);

            }
            else {
                ll s = 0;
                getXY(P[i].x, P[i].y + P[i].z, x, y);
                s += sum(x, y, YSize);

                getXY(P[i].x, P[i].y - P[i].z - 2, x, y);
                s += sum(x, y, YSize);

                getXY(P[i].x - P[i].z - 1, P[i].y - 1, x, y);
                s -= sum(x, y, YSize);

                getXY(P[i].x + P[i].z + 1, P[i].y - 1, x, y);
                s -= sum(x, y, YSize);
                
                printf("%d\n", s / 2);
            }
        }

    }

    return 0;
}

/*
10 30
1 1 1 1
1 1 2 2
1 2 1 -3
1 2 2 -5
1 1 3 8
1 2 3 9
1 3 1 4
1 3 2 7
1 3 3 2


2 1 1 1
2 1 1 2
2 1 1 3
2 1 1 4

2 1 2 1
2 1 2 2
2 1 2 3
2 1 2 4

2 2 2 1
2 2 2 2
2 2 2 3
2 2 2 4

2 3 3 0
2 3 3 1
2 3 3 2
2 3 3 3
2 3 3 4

2 3 1 1
2 3 1 2
2 3 1 3
2 3 1 4

0 7 23 25    6 19 25 25    10 25 25 25    2 18 25 24 25     8 6 17 25
*/