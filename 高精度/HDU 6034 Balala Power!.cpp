#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

/*
    模拟 26 进制数的 相加、进位 
*/

#define ll long long
const int maxn = 100010;
const int mod = 1e9+7;
ll mod26[maxn];

void init() {
    mod26[0] = 1;
    for(int i = 1; i < maxn; ++i) {
        mod26[i] = mod26[i-1] * 26 % mod;
    }
}

struct Po {
    int len;
    bool canzero;
    int data[maxn];
    void reset() {
        memset(data, 0, sizeof(data));
        len = 0;     
        canzero = true; 
    }
    void add(int a, int k) {
        int cap = a;
        // 进位 
        while(cap) {
            data[k] += cap;
            len = max(k+1, len);
            if(data[k] >= 26) {
                cap = data[k] / 26;
                data[k] %= 26;
                ++k; 
            }else {
                cap = 0;
            }
        }
    }
    
    ll getmod() {
        ll ans = 0;
        for(int i = len-1; i >= 0; --i) {
            ans += mod26[i] * data[i] % mod;
            if(ans >= mod) {
                ans %= mod;
            }
        }
        return ans;
    }
    
    bool operator < (const Po& o) const {
        if(len != o.len) {
            return len < o.len;
        }
        for(int i = len-1; i >= 0; --i) {
            if(data[i] != o.data[i]) {
                return data[i] < o.data[i];  
            }
        }
        return false;
    }
    
}P[27];

char str[maxn];

void process(char *str) {
    int len = strlen(str);
    // 不允许有前导零 
    if(len > 1) {
        int c = (str[0] - 'a');
        P[c].canzero = false;
    }
    for(int i = 0; i < len; ++i) {
        int power = len - i - 1;
        int c = (str[i] - 'a');
        P[c].add(1, power);
    }
}
 
int main() {
    int n, cas = 0;
    int i, j;
    init();
    while(scanf("%d", &n) != EOF) {
        for(i = 0; i < 26; ++i) {
            P[i].reset();
        }
        for(i = 0; i < n; ++i) {
            scanf("%s", str);
            process(str);
        }
        sort(P, P + 26);
        
        ll ans = 0;
        
        for(i = 0; i < 26; ++i) {
            if(P[i].canzero) {
                break;
            }
        }
        Po tmp = P[i];
        for(j = i; j > 0; --j) {
            P[j] = P[j-1];
        }
        P[0] = tmp;
        
        
        for(i = 0; i < 26; ++i) {
            ans += P[i].getmod() * i;
            ans %= mod;
        }
        printf("Case #%d: %lld\n", ++cas, ans);
    }
    
    return 0;
} 
