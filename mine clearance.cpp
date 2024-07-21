#include <iostream>
using namespace std;
const int dx[] = {1, 1, 1, 0, 0, -1, -1, -1};
const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
const int maxn = 105;
char g[maxn][maxn]; // 默认初始化为0
int n, m;
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> g[i][j];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            if(g[i][j] != '*') {
                int cnt= 0; 
                for(int k = 0; k < 8; k++) 
                if(g[i + dx[k]][j + dy[k]] == '*') cnt++; 
                cout<< cnt; 
            }
            else cout<< "*";
    
            cout << endl; // 行末空格
    }
    return 0;
}
