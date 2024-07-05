#include<iostream>
#include<cmath>
using namespace std;
int main(){
    long long a,b,sum;
    cin>>a>>b;
    if(a==1){
        cout<<1<<endl;
        return 0;
    }
    if(b==1){
        cout<<1<<endl;
        return 0;
    }
    sum=pow(a,b);
    if(sum>1000000000) cout<<-1;
    else cout<<sum;
    return 0;
}