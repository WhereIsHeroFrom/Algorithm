#include <iostream>
#include <cmath>
using namespace std;

#define pi acos( -1.0 )

int n;
int main() {
    while( scanf( "%d", &n ) != EOF && n ) {
        printf("%.2lf\n", n * n / pi / 2 );
    }
}

