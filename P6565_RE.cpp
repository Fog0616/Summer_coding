#include<iostream>
#include<string>
using namespace std;
int n;
string name[105],s[105];
int sos[105],big_sos;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>name[i]>>s[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<=s[i].length()-3;j++){
            if(s[i][j]=='s'&&s[i][j+1]=='o'&&s[i][j+2]=='s'){
                sos[i]++;
            }
        }
        if(sos[i]>big_sos)big_sos=sos[i];
    }
    for(int i=1;i<=n;i++){
        if(sos[i]==big_sos)cout<<name[i]<<" ";
    }
    cout<<"\n";
    cout<<big_sos;
    return 0;
}