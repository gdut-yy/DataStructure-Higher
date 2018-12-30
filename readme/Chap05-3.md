# 题目：Chap05-3 线段树 Frequent Values（poj 3368）

## 问题描述
You are given a sequence of n integers a1 , a2 , ... , an in non-decreasing order. In addition to that, you are given several queries consisting of indices i and j (1 ≤ i ≤ j ≤ n). For each query, determine the most frequent value among the integers ai , ... , aj.
## 输入格式
The input consists of several test cases. Each test case starts with a line containing two integers n and q (1 ≤ n, q ≤ 100000). The next line contains n integers a1 , ... , an (-100000 ≤ ai ≤ 100000, for each i ∈ {1, ..., n}) separated by spaces. You can assume that for each i ∈ {1, ..., n-1}: ai ≤ ai+1. The following q lines contain one query each, consisting of two integers i and j (1 ≤ i ≤ j ≤ n), which indicate the boundary indices for the 
query.

The last test case is followed by a line containing a single 0.
## 输出格式
For each query, print one line with one integer: The number of occurrences of the most frequent value within the given range.
## 输入样例
	10 3
	-1 -1 1 1 1 1 3 10 10 10
	2 3
	1 10
	5 10
	0
## 输出样例
	1
	4
	3

----

## AC 代码

	/**
	 * Chap05-3 线段树 Frequent Values
	 */
	#include<bits/stdc++.h>
	using namespace std;
	const int maxn = 100010;
	int n, m, num[maxn], a[maxn], f[maxn][20];
	int init() {
	    int f = 1, p = 0;
	    char c = getchar();
	    while(c > '9' || c < '0') {
	        if(c == '-')
	            f = -1;
	        c = getchar();
	    }
	    while(c >= '0' && c <= '9') {
	        p = p * 10 + c - '0';
	        c = getchar();
	    }
	    return f * p;
	}
	void prepare() {
	    memset(f, -1, sizeof(-1));
	    for(int i = 1; i <= n; i++)
	        f[i][0] = a[i];
	    int k = log((double)(n + 1)) / log(2.0);
	    for(int j = 1; j <= k; j++)
	        for(int i = 1; i + (1 << j) - 1 <= n; i++)
	            f[i][j] = max(f[i][j - 1], f[i + (1 << j - 1)][j - 1]);
	}
	int rmq(int l, int r) {
	    if(l > r)
	        return 0;
	    int k = log((double)(r - l + 1)) / log(2.0);
	    return max(f[l][k], f[r - (1 << k) + 1][k]);
	}
	int main() {
	    int l, r;
	    while(cin >> n && n) {
	        m = init();
	        for(int i = 1; i <= n; i++) {
	            num[i] = init();
	            if(i == 1) {
	                a[i] = 1;
	                continue;
	            }
	            if(num[i] == num[i - 1])
	                a[i] = a[i - 1] + 1;
	            else
	                a[i] = 1;
	        }
	        prepare();
	        for(int i = 1; i <= m; i++) {
	            l = init();
	            r = init();
	            int t = l;
	            while(t <= r && num[t] == num[t - 1])
	                t++;
	            int ans = rmq(t, r);
	            ans = max(ans, t - l);
	            printf("%d\n", ans);
	        }
	    }
	    return 0;
	}
