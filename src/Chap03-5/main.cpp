/**
 * Chap03-5 优先队列和二叉堆 猴王（左偏树）
 */
#include <bits/stdc++.h>
#define maxn 200000
using namespace std;

struct Node {
    int key, dist;
    Node *lch;
    Node *rch;
    Node *parent;
} LT[maxn + 1];

Node *p, *q, *A, *B;

int n, i, j, x, m, y;

int getDist(Node *A) {
    if (A == NULL)
        return (-1);
    else
        return (A->dist);
}

// 合并操作
Node *MERGE(Node *A, Node *B) {
    if (A == NULL)
        return (B);
    if (B == NULL)
        return (A);
    if (A->key < B->key)
        swap(A, B);
    A->rch = MERGE(A->rch, B);
    if (A->rch != NULL)
        A->rch->parent = A;
    if (A->lch != NULL)
        A->lch->parent = A;
    if (getDist(A->lch) < getDist(A->rch))
        swap((A->lch), (A->rch));
    A->dist = getDist(A->rch) + 1;
    return (A);
}

// 查找一只猴子所在的堆，并返回堆头
Node *getRoot(int x) {
    Node *q;
    q = &LT[x];
    while (q->parent != NULL)
        q = q->parent;
    return q;
}

// 一个单独结点的左偏树
void _clear(Node *p) {
    p->key /= 2;
    p->lch = NULL;
    p->rch = NULL;
    p->dist = 0;
    p->parent = NULL;
}

// 一只猴子单独构成一棵左偏树
Node *first(int x) {
    Node *p;
    p->key = x;
    p->lch = NULL;
    p->rch = NULL;
    p->dist = 0;
    p->parent = NULL;
    return p;
}

int main() {

    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &x);
        // 初始化，每只猴子单独构成一棵左偏树
        LT[i] = *first(x);
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) {  // 每次决斗的处理
        scanf("%d %d", &x, &y);     // 输入两只猴子编号
        // 找到两个堆头
        p = getRoot(x);
        q = getRoot(y);
        // 通过合并操作，删除 A 根结点
        A = MERGE(p->lch, p->rch);
        if (A != NULL)
            A->parent = NULL;
        // 通过合并操作，删除 B 根结点
        B = MERGE(q->lch, q->rch);
        if (B != NULL)
            B->parent = NULL;
        // 单独处理两个根结点形成的左偏树
        _clear(p);
        _clear(q);
        p = MERGE(p, q);
        A = MERGE(A, B);
        A = MERGE(A, p);
        printf("%d\n", A->key);
    }
    return 0;
}
