#include<iostream>
#include<string.h>
#define MAXN 1024
using namespace std;
int n,x,ans;
struct student{
    int id;
    int academic,quality;
    double overall;
    student(int _id;int _ac;int _qu){
        this->id=_id;
        this->academic=_ac;
        this->quality=_qu;
        //这TM不就是偷懒写法吗
        this->overall=0.7*_ac+0.3*_qu;
    }
};
//unfinish