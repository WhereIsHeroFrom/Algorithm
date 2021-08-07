#include <iostream>

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
ll chineseRemain(int n, ModPair* mp) {
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
            return -1;
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
    return ans.getRemainder();
}

 

ModPair mp[MAXN];
ll r[MAXN];

int main() {
    int t;
    int i;
    mp[0].setModulus(23);
    mp[1].setModulus(28);
    mp[2].setModulus(33);
    
    while( scanf("%d", &t) != EOF) {
        while( t-- ){
            int cases = 0;
            while(scanf("%lld", &r[0]) != EOF) {
                for(i = 1; i < 4; ++i) {
                    scanf("%lld", &r[i]);
                }
                if(r[0] < 0) break;
                mp[0] = ModPair(23, r[0]);
                mp[1] = ModPair(28, r[1]);
                mp[2] = ModPair(33, r[2]);
                

                ll ans = (chineseRemain(3, mp) - r[3]) % 21252 + 21252;
                ans %= 21252;
                if(ans == 0) ans += 21252; 
                printf("Case %d: the next triple peak occurs in %lld days.\n", ++cases, ans);
            }        
        }
    }
    return 0;
}

/*
3
107 1
1007 3
10007 5
796407100
*/
