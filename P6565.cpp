#include <iostream>
#include <string>
using namespace std;

int n;
string name[110], s[110]; // name数组存储求救者姓名，s数组存储求救信号字符串
int sosCount[110]; // 记录每个求救者的求救信号中 sos 的个数

int main() {
    cin >> n;
    
    // 读入求救者的姓名和求救信号
    for (int i = 1; i <= n; i++) {
        cin >> name[i] >> s[i];
        sosCount[i] = 0; // 初始化 sos 的个数为 0
    }
    
    // 计算每个求救者的求救信号中 sos 的个数
    for (int i = 1; i <= n; i++) {
        int len = s[i].length();
        for (int j = 0; j <= len - 3; j++) {
            if (s[i][j] == 's' && s[i][j+1] == 'o' && s[i][j+2] == 's') {
                sosCount[i]++;
            }
        }
    }
    
    // 找出最大的 sosCount
    int maxSosCount = 0;
    for (int i = 1; i <= n; i++) {
        if (sosCount[i] > maxSosCount) {
            maxSosCount = sosCount[i];
        }
    }
    
    // 输出所有 sosCount 等于 maxSosCount 的求救者姓名
    bool first = true;
    for (int i = 1; i <= n; i++) {
        if (sosCount[i] == maxSosCount) {
            if (!first) {
                cout << " ";
            }
            cout << name[i];
            first = false;
        }
    }
    cout << endl;
    cout << maxSosCount << endl;

    return 0;
}
/*
#include <string>
#include <iostream>
using namespace std;
int n;
string name[110], s[110];
int a[110]; // 定义一个变量记录每个求救者的求救信号中sos的个数
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> name[i] >> s[i];
    // 计算每个求救者的求救信号中sos的个数并寻找最紧急的求助者
    int maxnum = 0; // maxnum 表示最紧急求助者的求助次数
    for (int i = 1; i <= n; i++) {
        int len = s[i].length();
        for (int j = 0; j + 2 < len; j++)
            if (s[i][j] == 's' && s[i][j + 1] == 'o' && s[i][j + 2] == 's')
                a[i]++;
        if (a[i] > maxnum)
            maxnum = a[i];
    }
    // 按照题目要求输出结果
    for (int i = 1; i <= n; i++)
        if (a[i] == maxnum)
            cout << name[i] << " ";
    cout << endl
         << maxnum << endl;
    return 0;
}
*/