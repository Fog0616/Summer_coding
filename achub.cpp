#include<iostream>
#include<cmath>
#include<string>
using namespace std;

const int maxn = 5050;  // 定义最大数组大小
int a[maxn], b, c[maxn], p, len;
string A;

int main() {
    // 第一步：读入字符串 A 和 数字 b
    cin >> A >> b;
    len = A.length();

    // 循环，将 A[i-1] 的字符转成数字，放到 a[i] 中
    for (int i = 1; i <= len; ++i) {
        a[i] = A[i-1] - '0';
    }

    // 第二步：进行大整数除法
    int temp = 0;
    for (int i = 1; i <= len; ++i) {
        temp = temp * 10 + a[i];  // 临时数字右边拼接上 a[i]
        c[i] = temp / b;          // 商 c[i] 是临时数字除以 b 的值
        temp = temp % b;          // 临时数字变为余数
    }

    // 第三步：输出结果
    int flag = 0;  // 标志商是否已经有非零位输出
    for (int i = 1; i <= len; ++i) {
        if (c[i] != 0) {
            flag = 1;  // 有非零位输出，标志置为1
        }
        if (flag == 1) {
            cout << c[i];  // 输出这一位
        }
    }
    if (flag == 0) {
        cout << "0";  // 如果商全是零，输出0
    }
    cout << endl << temp;  // 输出余数
    return 0;
}

/*输出商和余数版本*/