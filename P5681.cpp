#include<iostream>
using namespace std;
long long a,b,c;
int main(){
    cin>>a;
    cin>>b>>c;
    long long s=a*a,s2=b*c;
    if(s>s2) cout<<"Alice";
    else cout<<"Bob";
    return 0;
}