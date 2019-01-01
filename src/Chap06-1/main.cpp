/**
 * Chap06-1 树状数组 逆序对
 */
#include <bits/stdc++.h>
const int MAXN = 100000;
typedef long long ll;
using namespace std;

struct node {
    ll v;
    int id;
    bool operator<(const node&p)const {
        return v < p.v;
    }
};

node a[MAXN + 10];
ll b[MAXN + 10];
ll c[MAXN + 10];
int n;

inline int lowbit(int x) {
    return x & -x;
}

ll query(int x) {
    ll ans = 0;
    while(x) {
        ans += c[x];
        x -= lowbit(x);
    }
    return ans;
}

void change(int x) {
    while(x <= n) {
        c[x]++;
        x += lowbit(x);
    }
}

int main() {
    scanf("%d", &n);
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    memset(c, 0, sizeof(c));
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &(a[i].v));
        a[i].id = i;
    }
    sort(a + 1, a + n + 1);
    int pre = -1;
    int prevalue = 0;
    for(int i = 1; i <= n; i++) {
        if(pre != a[i].v) {
            pre = a[i].v;
            a[i].v = ++prevalue;
        } else
            a[i].v = prevalue;
    }
    for(int i = 1; i <= n; i++) {
        b[a[i].id] = a[i].v;
    }
    ll s = 0;
    for(int i = n; i >= 1; i--) {
        change(b[i]);
        s += query(b[i] - 1);
    }
    cout << s << endl;
    return 0;
}
