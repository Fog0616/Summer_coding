#include<bits/stdc++.h>
using namespace std;
int a[100],n;
bool is_prime(int x){
    if(x==0||x==1) return 0;
    for(int i=2;i*i<=x;i++)
        if(x%i==0)
            return 0;
        return 1;
        //如果为质数则返回1
}
int main(){
    int n,a;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
		if(is_prime(a)){
			cout<<a<<" ";//是素数，就输出
		}
	}
	return 0;
}