#include<iostream>
#include<windows.h>
using namespace std;
int n, a[105],x; // 这一行要怎么修改
int main() {
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x;
        a[x]++;
    }
    for(int i=0;i<=n;i++) cout<<a[i]<<' ';
    system("pause");
    for(int i=0;i<n;i++){
        for(int j=0;j<=a[i];j++){
            cout<<i<<' ';
        }
    }
    return 0;
}
    