/**
 * Chap01-3 线性结构 表中“移动窗口”求最小值
 */
#include <bits/stdc++.h>

using namespace std;


vector<int> minInWindows(const vector<int>& num, unsigned int _size) {
    vector<int> minInWindows;
    if(num.size() >= _size && _size >= 1) {
        // 双端队列
        deque<int> index;

        for(int i = 0; i < _size; ++i) {
            while(!index.empty() && num[i] < num[index.back()])
                index.pop_back();

            index.push_back(i);
        }
        for(int i=0;i<index.size();i++){
            cout << index.at(i) << " ";
        }
        cout << endl;

        for(int i = _size; i < num.size(); ++i) {
            minInWindows.push_back(num[index.front()]);
            // 如果已有的数字大于待存入的数字，那么这些数字不可能是滑动窗口的最小值
            while(!index.empty() && num[i] < num[index.back()])
                // 从队列尾部删除
                index.pop_back();
            // 如果队列头部的数字已经从窗口里滑出，那么滑出的数字也需要从队列头的头部删除
            if(!index.empty() && index.front() <= (int)(i - _size))
                index.pop_front();

            index.push_back(i);
            for(int i=0;i<index.size();i++){
            cout << index.at(i) << " ";
        }
        cout << endl;

        }
        minInWindows.push_back(num[index.front()]);
    }
    return minInWindows;
}

int main() {
    int n, in;
    scanf("%d", &n);
    vector<int> vec;
    for(int i = 0; i < n; i++) {
        scanf("%d", &in);
        vec.push_back(in);
    }
    int _size;
    scanf("%d", &_size);
    vector<int> ans = minInWindows(vec, _size);
    for(int i = 0; i < ans.size(); i++) {
        cout << ans.at(i) << " ";
    }
    return 0;
}
