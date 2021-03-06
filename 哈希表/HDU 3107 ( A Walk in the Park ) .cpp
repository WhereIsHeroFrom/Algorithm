#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

#define MAXN 200010
 
struct Tree {
    int idx;
    int x, y;
    Tree() {
    }
    Tree(int _x, int _y, int _idx) {
        x = _x;
        y = _y;
        idx = _idx;
    }
    void read(int _idx) {
        idx = _idx;
        scanf("%d %d", &x, &y);
    }
}TX[MAXN], TY[MAXN];

bool cmpx(const Tree& a, const Tree& b) {
    if(a.x == b.x) {
        return a.y < b.y;
    }
    return a.x < b.x;
}

bool cmpy(const Tree& a, const Tree& b) {
    if(a.y == b.y) {
        return a.x < b.x;
    }
    return a.y < b.y;
}


int n, m;
int nx, ny;
int has[MAXN];

int bin[4*MAXN], tot;

void unique_bin() {
    int i, tmp = 1;
    for(i = 1; i < tot; ++i) {
        if(bin[i] != bin[tmp-1]) {
            bin[tmp++] = bin[i];
        }
    }
    tot = tmp;
}

int get_bin(int v) {
    int l = 0, r = tot - 1;
    while(l <= r) {
        int mid = (l+r) >> 1;
        if(bin[mid] == v) {
            return mid;
        }else if(bin[mid] > v) {
            r = mid - 1;
        }else {
            l = mid + 1;
        }
    }
}

int cover[4*MAXN], coverIdx;

int main() {
    int i;
    while(scanf("%d %d", &n, &m) != EOF) {
        if(!n && !m) break;
        memset(has, 0, sizeof(has));
        nx = ny = n;
        tot = 0;
        for(i = 0; i < n; ++i) {
            Tree T;
            T.read(i);
            TX[i] = TY[i] = T;
            bin[tot++] = T.x;
            bin[tot++] = T.y; 
        }
        for(i = 0; i < m; ++i) {
            char str[30];
            int v;
            scanf("%s", str);
            if(str[0] == 'x') {
                sscanf(&str[2], "%d", &v);
                TX[nx++] = Tree(v, 0, -1);
            }else if(str[0] == 'y') {
                sscanf(&str[2], "%d", &v);
                TY[ny++] = Tree(0, v, -1);
            }
            bin[tot++] = v;
        }
        sort(bin, bin + tot);
        unique_bin();
        sort(TX, TX + nx, cmpx);
        sort(TY, TY + ny, cmpy);
        
        
        
        // 往左展望 
        coverIdx = 0;
        memset(cover, 0, sizeof(cover));
        for(i = 0; i < nx; ++i) {
            
            if(TX[i].idx == -1) {
                ++coverIdx;
            }else {
                int val = get_bin(TX[i].y);
                if(cover[val] < coverIdx) {
                    cover[val] = coverIdx;
                    has[TX[i].idx] = 1;
                    
                }
            }
        }
        
        
        
        // 往右展望 
        coverIdx = 0;
        memset(cover, 0, sizeof(cover));
        for(i = nx-1; i >= 0; --i) {
            if(TX[i].idx == -1) {
                ++coverIdx;
            }else {
                int val = get_bin(TX[i].y);
                if(cover[val] < coverIdx) {
                    cover[val] = coverIdx;
                    has[TX[i].idx] = 1;
                }
            }
        }
        
        // 往下展望 
        coverIdx = 0;
        memset(cover, 0, sizeof(cover));
        for(i = 0; i < ny; ++i) {
            if(TY[i].idx == -1) {
                ++coverIdx;
            }else {
                int val = get_bin(TY[i].x);
                if(cover[val] < coverIdx) {
                    cover[val] = coverIdx;
                    has[TY[i].idx] = 1;
                }
            }
        }

        // 往上展望 
        coverIdx = 0;
        memset(cover, 0, sizeof(cover));
        for(i = ny-1; i >= 0; --i) {
            if(TY[i].idx == -1) {
                ++coverIdx;
            }else {
                int val = get_bin(TY[i].x);
                if(cover[val] < coverIdx) {
                    cover[val] = coverIdx;
                    has[TY[i].idx] = 1;
                }
            }
        }
        
        int c = 0;
        for(i = 0; i < n; ++i) {
            if(has[i]) ++c;
        }
        printf("%d\n", c);
    }
    return 0;
}
