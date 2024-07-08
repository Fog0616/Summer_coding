#include<iostream>
#include<string>

using namespace std;

string gu;
int main(){
    cin>>gu;
    string target="luogu";
    int count=0;
    for(int i=0;i<=gu.length(); ){
        if(gu[i]='l'){
            if(gu[i+1]='u'){
                if(gu[i+2]='o'){
                    if(gu[i+3]='g'){
                        if(gu[i+4]='u'){
                            i=i+3;count++;
                        }
                    }
                    else i=i+2;count++;
                }
                else i=i+1;count++;
            }
            else count++;
        }
        
    }
    cout<<count;
    return 0;

}
