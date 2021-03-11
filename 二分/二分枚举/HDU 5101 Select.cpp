#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define ll long long


int sum[1100];

struct IQ {
    int size;
    int rpot;
    int iqs[110];

    void reset() {
        rpot = size - 1;
    }

    int getCur() {
        if (rpot == -1) {
            return -1;
        }
        return iqs[rpot];
    }

    void left() {
        --rpot;
    }

    int sortKey() const {
        if (size == 0) {
            return -1;
        }
        return iqs[size - 1];
    }

    void dsort() {
        sort(iqs, iqs + size);
    }

    bool operator < (const IQ& o) const {
        return sortKey() > o.sortKey();
    }
}I[1100];

vector <int> total;

ll innersum(int size, IQ *q, int k) {
    ll ret = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < q[i].size; ++j) {
            int l = j + 1, r = q[i].size - 1;
            int ans = q[i].size;
            int sub = k - q[i].iqs[j];
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (q[i].iqs[mid] > sub) {
                    r = mid - 1;
                    ans = mid;
                }
                else {
                    l = mid + 1;
                }
            }
            ret += q[i].size - ans;
        }
    }
    return ret;
}

ll totalsum(vector <int>& total, int k) {
    sort(total.begin(), total.end());
    ll ret = 0;
    for (int i = 0; i < total.size(); ++i) {
        int l = i + 1, r = total.size() - 1;
        int sub = k - total[i];
        int ans = r + 1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (total[mid] > sub) {
                r = mid - 1;
                ans = mid;
            }
            else {
                l = mid + 1;
            }
        }
        ret += total.size() - ans;
    }
    return ret;
}

int main() {
    int t;
    int n, k;
    int i, j, o;
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &k);
        total.clear();

        for (i = 0; i < n; ++i) {
            scanf("%d", &I[i].size);
            for (j = 0; j < I[i].size; ++j) {
                scanf("%d", &I[i].iqs[j]);
                total.push_back(I[i].iqs[j]);
            }
            I[i].dsort();

        }


        printf("%lld\n", totalsum(total, k) - innersum(n, I, k));

    }
    return 0;
}

/*
10
3 5
2 1 2
3 2 3 4
4 5 6 7 8
*/