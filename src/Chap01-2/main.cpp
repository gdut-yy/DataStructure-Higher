/**
 * Chap01-2 线性结构 表中每个数之前的所有数中，它最接近的数
 */
#include <bits/stdc++.h>
using namespace std;

// 数据结构
struct Node {
    struct Node *pre;
    struct Node *next;
    int data;
} ;

struct Ndee{
    int value;          // 值
    struct Node *point; // 根指针
    struct Node *pre;   // 前指针
    struct Node *next;  // 后指针
} _list;

// 查找最接近数
void calculateMin(int data, struct Node *head, int *__min, int index) {
    struct Node *p = head;
    int prevData, nextData;
    while(p->next != NULL) {
        // 在排序数列中定位目标数
        if(p->data == data) {
            break;
        }
        p = p->next;
    }
    prevData = p->pre->data;
    if(p->next != NULL) {
        nextData = p->next->data;
        __min[index] = (data - prevData) > (nextData - data) ? (nextData) : (prevData);// 查找最接近数
        p->next->pre = p->pre;
        p->pre->next = p->next; // 在排序数列中删除目标数
    } else { // 目标数最大时
        __min[index] = prevData;
        p->pre = NULL;
    }
    free(p);
}

// 从数组里创建双向链表
struct Node * buildListByArray(int *arr, int length) {
    int i;
    struct Node *head, *nodePre, *nodeNext;
    nodeNext = nodePre = (struct Node *)malloc(sizeof(struct Node));
    nodeNext->data = *(arr + 0);
    head = nodeNext;
    head->pre = NULL;
    for(i = 1; i < length; i++) {
        nodeNext = (struct Node *)malloc(sizeof(struct Node));
        nodeNext->data = *(arr + i);
        nodePre->next = nodeNext;
        nodeNext->pre = nodePre;
        nodePre = nodeNext;
    }
    nodePre->next = NULL;
    return head;
}

int n, originalArr[1005], sortedArr[1005], _min[1005];

int main() {
    list<int> originList,
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int in;
        scanf("%d", &in);
        originalArr[i] = in;
        sortedArr[i] = in;
    }
    // 排序
    sort(sortedArr, sortedArr + n);

    for(int i = 0; i < n; i++) {
        cout << sortedArr[i] << " ";
    }
    cout << endl;

    _list = buildListByArray(sortedArr, n);

    for(int i = n - 1; i > 0; i--) {
        calculateMin(originalArr[i], _list, _min, i);
    }

    _min[0] = sortedArr[0];
    for(int i = 0; i < n; i++) {
        cout << _min[i] << " ";
    }
    cout << endl << "Ci = ";
    for(int i = 0; i < n; i++) {
        cout << abs(originalArr[i] - _min[i]) << " ";
    }
    return 0;
}
