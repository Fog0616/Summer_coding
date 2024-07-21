#include<iostream>
using namespace std;
const int maxn = 10010;
int a[maxn], b[maxn], g[maxn], k[maxn];
int main() {
    int n, i, x, y;
    cin >> n;
    for (i = 1; i <= n; i++)
        cin >> a[i] >> b[i] >> g[i] >> k[i];
    cin >> x >> y;
    for (i = n; i >= 1; i--) {
        if (x >= a[i] && x <= a[i] + g[i]
                && y >= b[i] && y <= b[i] + k[i]) {
            cout << i;
            return 0;
            //逆序找，发现有解，输出并退出
        }
    }
    cout << "-1"; //如果找遍了都没解就输出-1
    return 0;
}
