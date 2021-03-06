#include <iostream>

using namespace std;

#pragma warning(disable:4996)

#define NULL_MATCH (-1)
#define Type char
#define MAXN 1000010

/*
    "ababaaba"

*/
void GenNext(int *next, Type* M, int MLen) {
    // 0. 用 NULL_MATCH(-1) 代表一定没有真前缀，0的位置一定没有真前缀，所以为 NULL_MATCH
    int MPos = NULL_MATCH;
    next[0] = MPos;
    for (int TPos = 1; TPos < MLen; ++TPos) {
        // 1. M[TPos-MPos-1...TPos-1] 和 M[0...MPos] 完全匹配 
        //    检测 M[TPos] 和 M[MPos + 1] 是否匹配，不匹配，则找下一个 MPos' = next[MPos]；
        while (MPos != NULL_MATCH && M[TPos] != M[MPos + 1])
            MPos = next[MPos];
        // 2. 正确匹配上，自增 MPos
        if (M[TPos] == M[MPos + 1]) MPos++;
        // 3. M[TPos-MPos...TPos] 和 M[0...MPos] 完全匹配 
        next[TPos] = MPos;                                    
    }
    /*for (int i = 0; i < MLen; ++i) {
        printf("|%d", i);
    }
    puts("");

    for (int i = 0; i < MLen; ++i) {
        printf("|%c", M[i]);
    }
    puts("");

    for (int i = 0; i < MLen; ++i) {
        printf("|-");
    }
    puts("");



    for (int i = 0; i < MLen; ++i) {
        printf("%d --> %d\n", i, next[i]);
    }
    puts("");*/

    /*for (int i = 0; i < MLen; ++i) {
        printf("|%d", next[i]);
    }
    puts("");*/
    
}

int KMP(int *next, Type* M, int MLen, Type *T, int TLen) {
    // 1. 这里设置成 -1 的目的是：
    // 最初认为的情况是 目标串的空串 和 匹配串的空串 一定匹配
    int MPos = NULL_MATCH;
    for (int TPos = (TLen+1)/2; TPos < TLen; ++TPos) {
        // 2. 前提是 T[...TPos-1] == M[0...MPos] （MPos == -1 则代表两个空串匹配，同样成立)
        //    如果 T[TPos] != M[MPos + 1]，则 MPos = MPos' 继续匹配
        while (MPos != NULL_MATCH && T[TPos] != M[MPos + 1])
            MPos = next[MPos];
        // 3. 当 T[TPos] == M[MPos + 1] 则 TPos++, MPos++;
        if (T[TPos] == M[MPos + 1]) MPos++;
        // 4. 匹配完毕，返回 目标串 第一个匹配的位置
    }
    return MPos;
}



int Next[MAXN];
Type T[MAXN], TT[MAXN], M[MAXN];
bool has[MAXN];

int main() {
    int MLen;
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", M);
        MLen = strlen(M);
        GenNext(Next, M, MLen);
        memset(has, 0, sizeof(has));

        int v = Next[MLen - 1];
        while (v != NULL_MATCH) {
            has[v] = 1;
            v = Next[v];
        }

        int ans = MLen;


        // 将字符串当成是  X...XY 的形式来枚举;
        // 其中 X字符串的长度大于Y，Y 字符串的长度可能为 0；
        // 枚举的是 X 字符串的长度 XLen
        for (int XLen = 1; XLen <= MLen; ++XLen) {
            int K = (MLen / XLen);
            int YLen = (MLen % XLen) ? (MLen - XLen*K) : 0;
            if (YLen >= XLen) {
                continue;
            }

            int XTLen = XLen * K;
            if (XTLen % (XTLen - 1 - Next[XTLen - 1]) == 0) {
                if (K == XTLen / (XTLen - 1 - Next[XTLen - 1])) {
                    if (YLen == 0) {
                        if(K > 1)
                            ans = 0;
                    }
                    else if (has[YLen - 1]) {
                        if (XLen - YLen < ans) ans = XLen - YLen;
                    }
                }
            }

        }

        printf("%d\n", ans);

    }
    return 0;
}

/*
22
abcabca
aaa
abca
abcde
abcabc
abcdabcda
aaaaaaaaaaaaaaaaab
abcabcabcbc
abaabaabaa
abcca

*/
