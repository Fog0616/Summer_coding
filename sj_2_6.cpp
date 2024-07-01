#include<bits/stdc++.h>
using namespace std;
int m,t,s;
int main()
{
	cin>>m>>t>>s;
	if(t==0)
	{
		cout<<0<<endl;
		return 0;
	}
	if(s%t==0) cout<<max(m-s/t,0)<<endl;
	else cout<<max(m-s/t-1,0)<<endl;
	return 0;
}
//<不如检查一下被0除>