#include<bits/stdc++.h>
using namespace std;
int n,m;
int mm[105][105];
char a[105][105];
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        scanf("%s",&a[i]);//我之前想的读入好复杂，，结果。。。
    }
    for(int i=1;i<=n;i++){//穷举
        for(int j=0;j<m;j++){
            if(a[i][j]=='*'){//是炸弹的情况
                mm[i][j]=-100000000;//其实一个点最多就加8下
                mm[i-1][j-1]++;//不停加，8个
                mm[i-1][j]++;
                mm[i-1][j+1]++;
                mm[i][j-1]++;
                mm[i][j+1]++;
                mm[i+1][j-1]++;
                mm[i+1][j]++;
                mm[i+1][j+1]++;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<m;j++){
            if(mm[i][j]<0){//是地雷就输出*
                cout<<"*";
            }
            else{
                cout<<mm[i][j];//不是就输出周围个数
            }
        }
        cout<<endl;
    }
    return 0;
}