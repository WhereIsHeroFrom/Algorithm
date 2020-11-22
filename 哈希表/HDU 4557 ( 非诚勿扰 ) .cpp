#include <iostream>
#include <cstring>
using namespace std;

struct Player{
    char name_[20];
    int score_;
    void read() {
        scanf("%s %d", name_, &score_);
    } 
}op[2000];

int tot_cnt, get_cnt;
bool hashv[2000];

void init() {
    tot_cnt = 0;
    get_cnt = 0; 
    memset(hashv, 0, sizeof(hashv));
}

int main() {
    int t, cases=0;
    int n, i, score;
    char str[10];
    
    scanf("%d", &t);
    while(t--) {
        init(); 
        scanf("%d", &n);
        printf("Case #%d:\n", ++cases);
        while(n--) {
            scanf("%s", str);
            if(str[0] == 'A') {
                op[tot_cnt].read();
                ++tot_cnt;
                printf("%d\n", tot_cnt - get_cnt);
            } else {
                scanf("%d", &score);
                int idx = -1;
                for(i = 0; i < tot_cnt; i++) {
                    if(!hashv[i]) {
                        if(op[i].score_ >= score) {
                            if(idx == -1 || op[i].score_ < op[idx].score_) {
                                idx = i;
                            }
                        }
                    }
                }
                if(idx == -1) {
                    printf("WAIT...\n");
                } else {
                    hashv[idx] = 1;
                    get_cnt ++;
                    printf("%s\n", op[idx].name_);
                }
            }
        }
    } 
    return 0;
} 
