/**
 * Chap01-3 ���Խṹ ���С��ƶ����ڡ�����Сֵ
 */
#include <bits/stdc++.h>

using namespace std;


vector<int> minInWindows(const vector<int>& num, unsigned int _size) {
    vector<int> minInWindows;
    if(num.size() >= _size && _size >= 1) {
        // ˫�˶���
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
            // ������е����ִ��ڴ���������֣���ô��Щ���ֲ������ǻ������ڵ���Сֵ
            while(!index.empty() && num[i] < num[index.back()])
                // �Ӷ���β��ɾ��
                index.pop_back();
            // �������ͷ���������Ѿ��Ӵ����ﻬ������ô����������Ҳ��Ҫ�Ӷ���ͷ��ͷ��ɾ��
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
