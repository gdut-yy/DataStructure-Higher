/**
 * Chap04-2 并查集 食物链
 */
#include <bits/stdc++.h>

using namespace std;

int _set[50100], value[50100], n, k, x, y, d, cnt;

int fa(int id) {
    if (id != _set[id]) {
        int tmp = _set[id];
        _set[id] = fa(_set[id]);
        value[id] = (value[id] + value[tmp]) % 3;
    }
    return _set[id];
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        _set[i] = i;
    }
    for (int i = 0; i < k; i++) {
        scanf("%d %d %d", &d, &x, &y);
        if (x > n || y > n) {
            cnt++;
            continue;
        }
        if (d == 1) {
            if (fa(x) == fa(y)) {
                if (value[x] != value[y]) {
                    cnt++;
                }
            } else {
                value[_set[x]] = (value[y] - value[x] + 3) % 3;
                _set[_set[x]] = _set[y];
            }
        } else {
            if (x == y) {
                cnt++;
                continue;
            }
            if (fa(x) == fa(y)) {
                if (value[x] != (value[y] + 1) % 3) {
                    cnt++;
                }
            } else {
                value[_set[x]] = (value[y] - value[x] + 4) % 3;
                _set[_set[x]] = _set[y];
            }
        }
    }
    for (int i = 1; i <= 10; i++) {
        fa(i);
    }
    cout << cnt << endl;
    return 0;
}
