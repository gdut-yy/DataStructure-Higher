/**
 * Chap05-3 线段树 Frequent Values
 */
#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;
int n, m, num[maxn], a[maxn], f[maxn][20];
int init() {
    int f = 1, p = 0;
    char c = getchar();
    while(c > '9' || c < '0') {
        if(c == '-')
            f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9') {
        p = p * 10 + c - '0';
        c = getchar();
    }
    return f * p;
}
void prepare() {
    memset(f, -1, sizeof(-1));
    for(int i = 1; i <= n; i++)
        f[i][0] = a[i];
    int k = log((double)(n + 1)) / log(2.0);
    for(int j = 1; j <= k; j++)
        for(int i = 1; i + (1 << j) - 1 <= n; i++)
            f[i][j] = max(f[i][j - 1], f[i + (1 << j - 1)][j - 1]);
}
int rmq(int l, int r) {
    if(l > r)
        return 0;
    int k = log((double)(r - l + 1)) / log(2.0);
    return max(f[l][k], f[r - (1 << k) + 1][k]);
}
int main() {
    int l, r;
    while(cin >> n && n) {
        m = init();
        for(int i = 1; i <= n; i++) {
            num[i] = init();
            if(i == 1) {
                a[i] = 1;
                continue;
            }
            if(num[i] == num[i - 1])
                a[i] = a[i - 1] + 1;
            else
                a[i] = 1;
        }
        prepare();
        for(int i = 1; i <= m; i++) {
            l = init();
            r = init();
            int t = l;
            while(t <= r && num[t] == num[t - 1])
                t++;
            int ans = rmq(t, r);
            ans = max(ans, t - l);
            printf("%d\n", ans);
        }
    }
    return 0;
}
