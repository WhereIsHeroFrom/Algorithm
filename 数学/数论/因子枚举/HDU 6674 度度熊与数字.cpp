
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath> 
#include <algorithm>

using namespace std;


int digitSum(int v) {
    int s = 0;
    while(v) {
        s += v %10;
        v /= 10;
    }
    return s;
}

vector <int> X;

int main() {
	/*vector <factor> ans;
	Factorization(252, ans);
	printf("%d = \n", 252);
	for(int i = 0; i < ans.size(); i++) {
		ans[i].print();
	}*/
	int t, V;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &V);
        X.clear();
        int s = digitSum(V);
        for(int i = 1; i*i <= V; ++i) {
            if(V % i == 0) {
                if(s % i == 0) {
                    X.push_back(i);
                }
                if(i < V/i) {
                    if(s % (V/i) == 0) {
                        X.push_back(V/i);
                    }
                }
            }
        }
        sort(X.begin(), X.end());
        printf("%d\n", X.size());
        for(int i = 0; i < X.size(); ++i) {
            if(i) printf(" ");
            printf("%d", X[i]);
        }
        puts("");
    }
	
	return 0;
}



