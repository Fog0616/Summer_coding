#include <iostream>
#include <string>
using namespace std;
int s[155] = {0}, t[155] = {0}, ans, n;
int main() {
    cin >> n;
    t[1] = 1;
    for(int i = 1; i <= n; i++) {
        for(int k = 1; k <= 150; k++) 
            t[k] = t[k] * i;
        for(int k = 1; k <= 150; k++) {
            t[k + 1] += t[k] / 10;
            t[k] = t[k] % 10;
        }
        for(int k = 1; k <= 150; k++) {
            s[k] = s[k] + t[k];
            s[k + 1] += s[k] / 10;
            s[k] = s[k] % 10;
        }
    }
    int flag = 0;
    for(int i = 150; i >= 1; i--) {
        if(s[i] != 0) flag = 1;
        if(flag) cout << s[i];
    }
}