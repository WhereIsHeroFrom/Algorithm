#include <iostream>

using namespace std;
int t, e, r, c;
int main()
{
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d%d", &r, &e, &c);
        if(e - c > r)
            printf("advertise\n");
        else if(e - c == r)
            printf("does not matter\n");
        else printf("do not advertise\n");

    }
}

