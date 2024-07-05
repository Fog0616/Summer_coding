#include<bits/stdc++.h>
using namespace std;
int a[]={0};
int n;
int main(){
    cin>>n;
    for(int i=0;i<n;i++) cin>>a[i];
    sort(a[0],a[n-1]);
    for(int i=0;i<n;i++) cout<<a[i];
}
