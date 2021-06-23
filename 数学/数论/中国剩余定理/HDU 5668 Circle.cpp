#include <iostream>
#include <cstring>

using namespace std;

#define ll long long
const int MAXN = 100010;


ll GCD(ll a, ll b) {
    return b ? GCD(b, a%b) : a;
}

class ModPair {
    /*
        x = km + a
    */
private:
    ll m_;   // modulus
    ll a_;   // remainder
public:
    ModPair() {}
    ModPair(ll m, ll a) : m_(m), a_(a) {}

    // 标准化，将 m 和 a 都转化为正数
    void standardization() {
        if(m_ < 0) {
            m_ = -m_;
        }
        a_ = (a_ % m_ + m_) % m_;
    }

    ll lcm (ll om) const {
        ll g = GCD(om, m_);
        return om / g * m_;
    }

    ll getModulus() const { return m_;}
    void setModulus(ll m) {m_ = m;}
    ll getRemainder() const { return a_;}
    void setRemainder(ll a) {a_ = a;} 
};


// 扩展欧几里得
// aX + bY = 1 
ll ExpGcd(ll a, ll b, ll &X, ll &Y) {
    ll q, temp;
    if( !b ) {
        q = a; X = 1; Y = 0;
        return q;
    }else {
        q = ExpGcd(b, a % b, X, Y);
        temp = X; 
        X = Y;
        Y = temp - (a / b) * Y;
        return q;
    }
}

// long long 乘法，非溢出版本 
ll Product_Mod(ll a, ll b, ll mod) {
   ll sum = 0;
   int flag = (b >= 0 ? 1 : -1);
   if(flag < 0) {
       b = -b;
   }
   while(b) {
       if(b & 1) 
           sum = (sum + a) % mod;
       a = (a + a) % mod;
       b >>= 1;
   }
   return (sum * flag + mod) % mod;
}

// 中国剩余定理 模板
// return -1 表示无解 
ModPair chineseRemain(int n, ModPair* mp) {
    /********************(1)********************/
    for(int i = 0; i < n; ++i) {
        mp[i].standardization();
    } 
    ModPair ans = mp[0];
    ll A, B, C, X, Y;
    for(int i = 1; i < n; i++) {
        /********************(2)********************/
        A = ans.getModulus();         
        B = -mp[i].getModulus();
        C = mp[i].getRemainder() - ans.getRemainder();
        ll g = GCD(A, B);
        if( C % g ) {     
            ans.setRemainder(0);
            ans.setModulus(-1);             
            return ans;
        }
        /********************(3)********************/
        A /= g, B /= g, C /= g;
        /********************(4)********************/
        if(A < 0) {
            A = -A, B = -B, C = -C;
            B = ((B % A) + A) % A;
        }
        /********************(5)********************/
        ExpGcd(A, B, X, Y);
        Y = Product_Mod(Y, C, A);
        /********************(6)********************/
        ll tmpm = A * mp[i].getModulus();
        ll tmpr = (mp[i].getRemainder() + Product_Mod(mp[i].getModulus(), Y, tmpm)) % tmpm;
        
        ans.setModulus(tmpm);
        ans.setRemainder(tmpr);
    }
    return ans;
}

 

ModPair mp[MAXN];
ll m[MAXN], r[MAXN];
int top;
int pos[MAXN], hashv[MAXN];
int n;

int main() {
    int t;
    int i, x;
    
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 1; i <= n; i++) {
            scanf("%d", &x);
            pos[x] = i;
        }
        memset(hashv, 0, sizeof(hashv));
        top = 1;
        int x = 0;
        int cnt = 0;
        while(top <= n) {
            cnt = 0;
            while(1) {
                // 模拟约瑟夫环 
                if(++x > n) {
                    x = 1;
                }
                // 如果这个位置还有人在 
                if(!hashv[x]) {
                    ++cnt;
                    if(x == pos[top]) {
                        hashv[x] = 1;
                        m[top-1] = n-top+1, r[top-1] = cnt;
                        
                        //printf("%I64d %I64d\n", m[top-1], r[top-1]);
                        break;
                    }    
                }
            }
            ++top;
        }

        for(int i = 0; i < n; ++i) {
            mp[i] = ModPair(m[i], r[i]);
        }
        ModPair ans = chineseRemain(n, mp);
        if(ans.getModulus() == -1) {
            printf("Creation August is a SB!\n");
        }else {
            if(ans.getRemainder() == 0) {
                ans.setRemainder( ans.getModulus() );
            }
            printf("%lld\n", ans.getRemainder());
        }
    }
    return 0;
}

/*
10
7
2 7 6 1 4 3 5
*/
