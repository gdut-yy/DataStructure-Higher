/**
 * Chap03-1 优先队列和二叉堆 序列和的前n小元素
 */
#include <bits/stdc++.h>

using namespace std;

struct node {
    int sum;
    int no;
};
node heap[400400], tmp;
int a[400400], b[400400], d[400400], n, tot;

void put(int key, int sign) {
    int fa, son;
    node temp;
    tot = tot + 1;
    heap[tot].sum = key;
    heap[tot].no = sign;
    son = tot;
    fa = son / 2;
    while(fa > 0) {
        if(heap[fa].sum > heap[son].sum) {
            temp = heap[fa];
            heap[fa] = heap[son];
            heap[son] = temp;
            son = fa;
            fa /= 2;
        } else
            fa = 0;
    }
}

node getmin() {
    int fa, son;
    node temp, ans;
    ans = heap[1];
    heap[1] = heap[tot];
    tot = tot - 1;
    fa = 1;
    son = fa * 2;
    while(son <= tot) {
        if(son < tot && heap[son].sum > heap[son + 1].sum)
            son++;
        if(heap[fa].sum > heap[son].sum) {
            temp = heap[fa];
            heap[fa] = heap[son];
            heap[son] = temp;
            fa = son;
            son = fa * 2;
        } else
            son = tot + 1;
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    memset(d, 0, sizeof(d));
    memset(heap, 0, sizeof(heap));
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for(int i = 1; i <= n; i++)
        scanf("%d", &b[i]);
    tot = 0;
    for(int i = 1; i <= n; ++i) {
        d[i]++;
        put(a[i] + b[d[i]], i);
    }
    for(int i = 1; i <= n; ++i) {
        tmp = getmin();
        printf("%d\n", tmp.sum);
        d[tmp.no]++;
        put(a[tmp.no] + b[d[tmp.no]], tmp.no);
    }
    return 0;
}
