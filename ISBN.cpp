#include <iostream>
#include <string>
using namespace std;
int main(void) {
    string a, mod = "0123456789X"; 
    cin >> a;
    int i, j = 0, t = 0;
    for(i = 0; i < 12; i++) {
        if(a[i] == '-') continue; 
        j++;
        t += (a[i] - '0') * j; 
    }
    if(mod[t % 11] == a[12]) 
        cout << "Right";
    else {
        a[12] = mod[t % 11]; 
        cout << a;
    }
    return 0;
}
//isbn 号码