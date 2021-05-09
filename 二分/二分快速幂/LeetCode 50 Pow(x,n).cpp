class Solution {
public:
    double myPow(double x, int n) {
        if(n == 0) {
            return 1;
        }else if(n < 0) {
            if(n == -2147483648) {
                ++n;
                return 1 / myPow(x, -n) / x;
            }
            return 1 / myPow(x, -n);
        }else {
            double t = myPow(x*x, n>>1);
            if(n & 1) {
                t = t * x;
            }
            return t;
        }
    }
};
