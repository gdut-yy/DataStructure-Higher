/**
 * Chap07-2-1 Treap 星际争霸
 */
#include <bits/stdc++.h>
#define inf 1 << 30

using namespace std;

struct node {
    struct node *l;
    struct node *r;
    struct node *f;
    int key;
    int priority;
    int tot;
} * root;

// 左旋
void leftrotate(struct node *x) {
    struct node *y = x->f;
    x->f = y->f;
    if (y->f->l == y)
        x->f->l = x;
    else
        x->f->r = x;
    if (x->r)
        x->r->f = y;
    y->l = x->r;
    y->f = x;
    x->r = y;
}

// 右旋
void rightrotate(struct node *x) {
    struct node *y = x->f;
    x->f = y->f;
    if (y->f->l == y)
        x->f->l = x;
    else
        x->f->r = x;
    if (x->l)
        x->l->f = y;
    y->r = x->l;
    y->f = x;
    x->l = y;
}

// 删除
void del(struct node *x) {
    while (x->l || x->r) {
        if (x->l && (x->r && x->l->priority < x->r->priority || !x->r))
            leftrotate(x->l);
        else
            rightrotate(x->r);
    }
    if (x->f->l == x)
        x->f->l = 0;
    else
        x->f->r = 0;
    delete x;
}

// 插入
void ins(struct node *x, int k, int dir, struct node *fa) {
    if (!x) {
        x = new struct node;
        x->key = k;
        x->priority = rand() % inf;
        x->l = x->r = 0;
        x->tot = 1;
        x->f = fa;
        if (dir)
            fa->r = x;
        else
            fa->l = x;
    } else {
        if (k < x->key) {
            ins(x->l, k, 0, x);
            if (x->l->priority < x->priority)
                leftrotate(x->l);
        } else {
            ins(x->r, k, 1, x);
            if (x->r->priority < x->priority)
                rightrotate(x->r);
        }
    }
}

// 查找
struct node *exist(struct node *x, int k) {
    if (x == 0)
        return 0;
    if (x->key == k)
        return x;
    if (k < x->key)
        return exist(x->l, k);
    else
        return exist(x->r, k);
};

vector<int> rating;
bool cmp(int x, int y) {
    return x > y;
}
// 深度优先遍历
void dfs(struct node *x) {
    if (!x)
        return;
    dfs(x->r);
    rating.push_back(x->tot);
    dfs(x->l);
}

int main() {
    int t;
    cin >> t;
    root = new struct node;
    root->l = root->r = root->f = 0;
    while (t--) {
        getchar();
        char tag;
        struct node *tmp;
        int x, y;
        scanf("%c", &tag);
        switch (tag) {
        case 'C':
            scanf("%d", &x);
            tmp = exist(root->l, x);
            if (!tmp)
                ins(root->l, x, 0, root);
            else
                tmp->tot++;
            break;
        case 'D':
            scanf("%d", &x);
            tmp = exist(root->l, x);
            if (!tmp)
                continue;
            if (!--tmp->tot)
                del(tmp);
            break;
        case 'M':
            scanf("%d<%d", &x, &y);
            struct node *xNode = exist(root->l, x);
            struct node *yNode = exist(root->l, y);
            if (!xNode || !yNode)
                continue;
            if (xNode == yNode)
                continue;
            xNode->tot += yNode->tot;
            del(yNode);
            break;
        }
    }
    dfs(root->l);
    // 排序
    sort(rating.begin(), rating.end(), cmp);
    cin >> t;
    while (t--) {
        int x;
        scanf("%d", &x);
        if (x > rating.size())
            printf("NO\n");
        else
            printf("%d\n", rating[x - 1]);
    }
    return 0;
}
