//auto.cpp  升级版测试
#include<bits/stdc++.h>
using namespace std;
int main(){
    vector<int>a={0,0,0};
    for(auto &v:a) cin>>v;
    for(auto &v:a) v=v*2;
    for(auto &v:a) cout<<v;
    return 0;
}
//auto:自适应类型，必须指定初始量
//添加输入