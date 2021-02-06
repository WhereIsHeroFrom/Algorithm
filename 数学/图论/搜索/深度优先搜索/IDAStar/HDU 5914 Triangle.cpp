/*
    给定  1,2,3,4...n 根木棍，求去掉多少根，使得剩下的木棍不能组成三角形；

    IDA*

    i 从大到小枚举
        枚举 i 根的所有组合情况，如果 i 根中有排好序的两两相邻的只要有一个满足：两边之和大于第三边
    那么这种方案就不可行，一旦找到所有的数都不能满足：两边之和大于第三边，则为一个可行方案，直接返回，答案为 n-i；

    剪枝：注意搜索的时候，有序从小到大搜索，剩余可枚举根数如果已经小于实际需要枚举的根数，说明这个搜索方案不可行，直接返回；

*/
#include <iostream>

using namespace std;

int has[21];
int sta[21], top;


bool dfs(int depth, int idx, int maxn) {

    if (depth == 0) {
        int bfind = false;
        for (int i = 0; i + 2 < top; ++i) {
            if (sta[i] + sta[i + 1] > sta[i + 2]) {
                bfind = true;
            }
        }
        return (!bfind);
    }

    // 强剪枝
    if (depth > maxn - idx + 1) {
        return false;
    }

    for (int i = idx; i <= maxn; ++i) {
        sta[top++] = i;
        if (dfs(depth - 1, i + 1, maxn)) {
            return true;
        }
        --top;
    }
    return false;
}

int IDA_dfs(int n) {
    if (n < 3) {
        return 0;
    }
    top = 0;
    for (int i = n; i >= 0; --i) {
        if (dfs(i, 1, n)) {
            return n - i;
        }
    }
}

int main() {
   
    int t, cas = 0, n;
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);
        printf("Case #%d: %d\n", ++cas, IDA_dfs(n));
    }

    return 0;
}
