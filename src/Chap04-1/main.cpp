/**
 * Chap04-1 并查集 破译密文
 */
#include<bits/stdc++.h>
using namespace std;

struct zm {
    char ch;
    int num;
};

string s1, s2, d[3000];
zm a[30];
int father[6000];
int n, len = 0, lend = 0, tot = 0;

int _find(int x) {
    if(father[x] == x)
        return x;
    father[x] = _find(father[x]);
    return father[x];
}

int find_zm(char ch) {
    for(int i = 1; i <= n; i++)
        if(ch == a[i].ch)
            return i;
    return 0;
}

void exchange(string s, string b[]) {
    len = 0;
    // 拆解，比如字母a 长度为3，则拆为3个变量，a,aa,aaa;并存储在b数组里
    // 其实也可以拆成a1,a2,a3；怎么做自己去实现
    for(int i = 0; i < s.size(); i++)        {
        if(s[i] == '1' || s[i] == '0') {
            len++;
            b[len] += s[i];
            continue;
        }
        int k = find_zm(s[i]); // 找到字符s[i]在字母表中的下标,才能知道 a[k].num
        for(int j = 1; j <= a[k].num; j++) {
            len++;
            b[len].assign(j, a[k].ch);
        }
    }
}

int find_k(string s) {
    for(int i = 1; i <= lend; i++)
        if(s == d[i])
            return i;
    return 0;
}

void _merge(int x, int y) {
    // 合并时如果有1或者0，则一定要让1或0当根
    if(d[x] == "1" || d[x] == "0") {
        father[y] = x;
        return;
    }
    father[x] = y;
}

int main() {
    cin >> s1;
    cin >> s2;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i].ch >> a[i].num;
    }
    string b[3000], c[3000];
    exchange(s1, b);        // 把s1展开存储在b字符串数组
    exchange(s2, c);        // 把s2展开存储在b字符串数组
    for(int i = 1; i <= 2 * len; i++) {
        father[i] = i;      // 先初始化，最终的去掉重复的字符串，长度肯定会小于等于2*len
    }
    for(int i = 1; i <= len; i++) {
        int k1, k2;
        k1 = find_k(b[i]);  //查找b[i]在d数组中的位置
        k2 = find_k(c[i]);  //查找c[i]在d数组中的位置
        // 说明d数组中没有则，加入d数组
        if(k1 == 0) {
            lend++;
            d[lend] = b[i];
            k1 = lend;
        }
        if(k2 == 0) {
            lend++;
            d[lend] = c[i];
            k2 = lend;
        }
        int f1, f2;
        f1 = _find(k1);
        f2 = _find(k2);
        if(f1 != f2)
            _merge(f1, f2); // 如果不在一个集合则合并
    }
    for(int i = 1; i <= lend; i++) {
        if(father[i] == i && (d[i] != "0" && d[i] != "1"))
            tot++;          // 寻找根节点为非零的集合
    }
    tot = 1 << tot;         // 有几个不确定的集合就有2~tot中可能
    cout << tot << endl;
    return 0;
}
