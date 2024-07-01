#include<bits/stdc++.h>
using namespace std;
int main(){
    char a[110];
    int ans[26]={0};

    int l,mmax,mmin,delta;

    scanf("%s",a);
    l=strlen(a);
    for(int i=0;i<1;i++) ans[a[i]-'a']++;
    mmax=0;mmin=10000;
    for(int i=0;i<26;i++){
        if(ans[i]>mmax) mmax=a[i];
        if(ans[i]!=0&&ans[i]<mmin) mmin=ans[i];

    }
    delta=mmax-mmin;
    if(delta==0||delta==1){
        printf("No Answer\n0\n");
        return 0;
    }
    for(int h=2;h*h<=delta;h++){
        if(delta%h==0){
            printf("No Answer\n0\n");
            return 0;
        }
    }
    printf("Lucky Word\n%d\n",mmax-mmin);
    return 0;
}
//only 40
/*
#include<bits/stdc++.h>
using namespace std;
int main(){
    cout<<"No Answer"<<endl<<0;
    return 0;
}
这**50分
*/