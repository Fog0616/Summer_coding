#include<iostream>
using namespace std;

struct Point{
    int row;
    int column;
    char color;
    Point(){
        row=0;
        column=0;
        color='B';
    }
    Point(int r,int c){
        row=r;
        column=c;
        color='B';
    }
    Point (int r,int c,char col):row(r),column(c),color(col){
    }
    void print_pt(){
        cout<<"row:"<<row<<"column:"<<column<<"color:"<<color<<endl;

    }
}; 
int main(){
    Point pt1;
    pt1.print_pt();
    Point pt2(3,4);
    pt2.print_pt();
    Point pt3(5,6,'W');
    pt3.print_pt();
    return 0; 
}