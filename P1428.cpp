#include<bits/stdc++.h>
using namespace std;
int a[200],cnt[200],t,n;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		for(int s=1;s<=i;s++)
		{
			if(a[i]>a[s])
			{
				cnt[i]++;
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		cout<<cnt[i]<<" ";
	}
	return 0;
}