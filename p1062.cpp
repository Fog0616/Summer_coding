#include<bits/stdc++.h>
using namespace std;
long long a,b=1,j;
int main(n,k){
	for(scanf("%d%d",&k,&n);n;++j,b*=k)
    if(n&1<<j)n^=1<<j,a+=b;
    printf("%lld",a);
}