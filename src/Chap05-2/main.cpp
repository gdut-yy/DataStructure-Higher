/**
 * Chap05-2 线段树 City Horizon
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int read() {
    int a = 0, b = 1;
    char c=getchar();
    while(!isdigit(c) && c != '-')
        c=getchar();
    if(c == '-') {
        b = -b;
        c=getchar();
    }
    while(isdigit(c)) {
        a = a * 10 + c - '0';
        c=getchar();
    }
    return a * b;
}
struct edge {
    int a, b, c;
    edge() {} edge(int x, int y, int z) {
        a = x;
        b = y;
        c = z;
    }
} a[40003];
bool operator<(edge a, edge b) {
    return a.c < b.c;
}
int tt = 0, b[80003], c[160003], n, x, y, _ll[640003], rr[640003];
ll tree[640003], lazy[640003];
#define ls nod<<1
#define rs nod<<1|1
void pushup(int nod) {
    tree[nod] = tree[ls] + tree[rs];
}
void pushdown(int nod) {
    if(lazy[nod]) {
        lazy[ls] = lazy[rs] = lazy[nod];
        tree[ls] = lazy[nod] * (rr[ls] - _ll[ls] + 1);
        tree[rs] = lazy[nod] * (rr[rs] - _ll[rs] + 1);
        lazy[nod] = 0;
    }
}
void build(int nod, int l, int r) {
    if(l == r) {
        _ll[nod] = c[l];
        rr[nod] = c[l + 1] - 1;
        tree[nod] = lazy[nod] = 0;
        return;
    }
    int mid = l + r >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    _ll[nod] = _ll[ls];
    rr[nod] = rr[rs];
    pushup(nod);
    lazy[nod] = 0;
}
void ins(int nod, int l, int r, int x, int y, int v) {
    if(l == x && r == y) {
        lazy[nod] = v;
        tree[nod] = (r - l + 1) * (ll)v;
        return;
    }
    pushdown(nod);
    int mid = rr[ls];
    if(x <= mid)
        ins(ls, l, mid, x, min(mid, y), v);
    if(y > mid)
        ins(rs, mid + 1, r, max(x, mid + 1), y, v);
    pushup(nod);
}
int main() {
    n = read();
    for(int i = 1; i <= n; i++) {
        a[i].a = read();
        a[i].b = read() - 1;
        a[i].c = read();
        b[++tt] = a[i].a;
        b[++tt] = a[i].b;
    }
    sort(a + 1, a + n + 1);
    sort(b + 1, b + tt + 1);
    x = tt;
    tt = 1;
    for(int i = 2; i <= x; i++)
        if(b[i] > b[i - 1])
            b[++tt] = b[i];
    x = tt;
    tt = 0;
    for(int i = 1; i <= x; i++) {
        c[++tt] = b[i];
        if(i < x && b[i + 1] - b[i] > 1)
            c[++tt] = b[i] + 1;
    }
    c[tt + 1] = c[tt] + 1;
    build(1, 1, tt);
    for(int i = 1; i <= n; i++) {
        ins(1, _ll[1], rr[1], a[i].a, a[i].b, a[i].c);
    }
    printf("%lld\n", tree[1]);
    return 0;
}
