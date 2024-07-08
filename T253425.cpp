#include<iostream>
#include<cstring>
using namespace std;

string s1,s2;

using namespace std;
int main(){
    getline(cin,s1);
    cout<<s1;
    int num=s1.length();
    for(int i=0;i<num;i++){
        switch(s1[i]){
            case 'A': s2[i]='T';
            case 'G': s2[i]='C';
            case 'T': s2[i]='A';
            case 'C': s2[i]='G';
        }
    }
    cout<<s2;
    return 0;
}