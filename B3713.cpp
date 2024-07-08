#include<iostream>
#include<string>
#include<cstring>
using namespace std;
int main(){
    int n,m;//n XUANSHOU.M TIMU
    cin>>n>>m;
    string t[m],player[n],flie[m*n],out[m*n];
    for(int i=0;i<m;i++) cin>>t[i];
    for(int i=0;i<m;i++){
        cin>>player[i];
        for(int j=0;j<n;j++) cin>>flie[i*2+j];
        string ans[m];
        for(int j=0;j<n;j++) ans[j]==player[i]+".zip/"+player[i]+t[j]+t[j]+".cpp";//SD-114.zip/SD-114/ovo/ovo.cpp
        //strcmp(str1, str2) == 0 =player[i]+".zip/"+player[i]+t[//SD-114.zip/SD-114/ovo/ovo.cpp
        for(int j=0;j<n;j++) if((flie[i*2+j].compare(ans[j])) == 0) out[i*2+1]="Fusu is happy!"; else out[i*2+1]="Fusu is angry!";//
    }
    cout<<out;
    return 0;
}