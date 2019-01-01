/**
 * Chap05-1 线段树 逆序对
 */
#include <bits/stdc++.h>
typedef long long ll;
#define INF 1<<30
#define MAXN 60000
#define MAXM 32767

using namespace std;

struct Node {
    int l;
    int r;
    int lc;
    int rc;
    int v;
};

int root, z;
Node p[11 * MAXM];

void _set() {
    root = z = -1;
}

void _build(int &k, int l, int r) {
    k = ++z;
    p[k].l = l;
    p[k].r = r;
    p[k].lc = p[k].rc = -1;
    p[k].v = 0;
    if(l != r) {
        _build(p[k].lc, l, (l + r) / 2);
        _build(p[k].rc, (l + r) / 2 + 1, r);
    }
}

void _insert(int &k, int tag) {
    p[k].v++;
    if(p[k].lc == -1)
        return;
    if(tag <= p[p[k].lc].r)
        _insert(p[k].lc, tag);
    else
        _insert(p[k].rc, tag);
}

int _search(int &k, int tag) {
    if(tag == p[k].r)
        return p[k].v;
    if(tag > p[p[k].lc].r)
        return p[p[k].lc].v + _search(p[k].rc, tag);
    else
        return _search(p[k].lc, tag);
}

int a[MAXN];
int l[MAXN], r[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    _set();
    _build(root, 0, MAXM);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        if(a[i] != 0)
            l[i] = _search(root, a[i] - 1);
        _insert(root, a[i]);
    }
    _set();
    _build(root, 0, MAXM);
    for(int i = n; i >= 1; --i) {
        if(a[i] != 0) {
            r[i] = _search(root, a[i] - 1);
        }
        _insert(root, a[i]);
    }
    ll ans = 0;
    for(int i = 1; i <= n; ++i) {
        ans += (ll)l[i] * r[i];
    }
    cout << ans << endl;
    return 0;
}
