#include<bits/stdc++.h>
using namespace std;
int main(){
    vector<int>a={1,1,4,5,1,4};
    for(auto &v:a) v=v*2;
    for(auto &v:a) cout<<v;
    return 0;
}
//auto:自适应类型，必须指定初始量