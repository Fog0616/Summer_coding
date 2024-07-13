#include <bits/stdc++.h>
using namespace std;

int main(){
    string s;
    int n;
    cin>>s>>n;
    int tmp=n;
    for(int i=1,j=0;i<s.length();i++){
    	while(s[j]>s[i]&&tmp){
    		s[j]='x';
    		tmp--;
    		while(j>=0&&s[j]=='x')j--;
		}
		j=i;
    }
    
    int t=s.length()-n;
    int flag=1;
    for(int i=0;i<s.length();i++){
    	if(s[i]=='0'&&flag)continue;

    	if(s[i]!='x'&&t){
    	    flag=0;
    		t--;
    		cout << s[i];
		}
	}
	if(flag)cout <<0; 
	return 0;
}
