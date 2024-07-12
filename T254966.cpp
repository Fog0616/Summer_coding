#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, id; 
    cin >> n;
    string max;
    string in;
	for (int i = 1; i <= n; i++) {
        cin >> in;
        int inSize = in.length();
        int maxSize = max.length();
        if (inSize > maxSize || (inSize >= maxSize && in > max)) {
            max = in;
            id = i;
        }
    }
    cout << id << endl << max << endl;
    return 0;
}
//hhh出去玩了一趟想出新方法了
//赞！