#include<bits/stdc++.h>
#include<string>
using namespace std;
string l;
int main(){
    int count_boy=0,count_girl=0;
    getline(cin,l);
    l=l+'.';//防止越界
//    cout<<l[0];
    int num=l.length()-3;
    for(int i=0;i<num;i++){
        if(l[i]=='b'||l[i]=='y') count_boy++;
        if(l[i]=='g'||l[i]=='l') count_girl++;
    }
    cout<<count_boy<<endl<<count_girl;
    return 0;
}