/**
 * Chapt07-2-2 Treap 金矿
 */
#include<bits/stdc++.h>
#define maxn 15005
#define max(a,b) ((a)>(b)?(a):(b))
int n, m, s, w, num, ans, x[2 * maxn], y[2 * maxn], yy[2 * maxn];
struct {
    int y;
    int sum;
    int maxsum;
} t[4 * maxn];

void qsX(int l, int r) {
    int i = l, j = r, k = x[(l + r) / 2], t;
    do {
        while(x[i] < k)
            ++i;
        while(x[j] > k)
            --j;
        if(i <= j) {
            t = x[i];
            x[i] = x[j];
            x[j] = t;
            t = y[i];
            y[i] = y[j];
            y[j] = t;
            ++i;
            --j;
        }
    } while(i < j);
    if(i < r)
        qsX(i, r);
    if(j > l)
        qsX(l, j);
}

void qsY(int l, int r) {
    int i = l, j = r, k = yy[(l + r) / 2], t;
    do {
        while(yy[i] < k)
            ++i;
        while(yy[j] > k)
            --j;
        if(i <= j) {
            t = yy[i];
            yy[i] = yy[j];
            yy[j] = t;
            ++i;
            --j;
        }
    } while(i < j);
    if(i < r)
        qsY(i, r);
    if(j > l)
        qsY(l, j);
}

void buildtree(int now) {
    if(2 * now <= m)
        buildtree(2 * now);
    t[now].y = yy[++num];
    t[now].sum = t[now].maxsum = 0;
    if(2 * now + 1 <= m)
        buildtree(2 * now + 1);
}

void ins(int now, int num, int p) {
    if(num < t[now].y)
        ins(now * 2, num, p);
    if(num > t[now].y)
        ins(now * 2 + 1, num, p);
    t[now].sum += p;
    t[now].maxsum = max(t[now * 2].maxsum, max(t[now].sum - t[now * 2 + 1].sum, t[now].sum - t[now * 2 + 1].sum + t[now * 2 + 1].maxsum));
}

int main() {
    int i, j, k;
    for(i = 0; i <= 4 * maxn - 1; i++)
        t[i].y = -30001;
    scanf("%d%d%d", &s, &w, &n);
    for(i = 1; i <= n; i++) {
        scanf("%d%d", &x[i], &y[i]);
        yy[i] = y[i];
        yy[n + i] = y[i] + w + 1;
    }
    yy[2 * n + 1] = -30001;
    qsY(1, 2 * n);
    m = 0;
    for(i = 1; i <= 2 * n; i++)
        if(yy[i] != yy[i + 1])
            yy[++m] = yy[i];
    num = 0;
    buildtree(1);
    qsX(1, n);
    i = 1;
    j = 1;
    k = x[j];
    while(i <= n && j <= n) {
        while(x[i] <= k + s && i <= n) {
            ins(1, y[i], 1);
            ins(1, y[i] + w + 1, -1);
            i++;
        }
        if(ans < t[1].maxsum)
            ans = t[1].maxsum;
        while(x[j] == k && j <= n) {
            ins(1, y[j], -1);
            ins(1, y[j] + w + 1, 1);
            j++;
        }
        k = x[j];
    }
    printf("%d", ans);
    return 0;
}
