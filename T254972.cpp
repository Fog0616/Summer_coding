#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int a[10100], b[10100], c[10100];

int main() {
    string A, B;
    cin >> A >> B;

    if (A == B) {
        cout << 0;
        return 0;
    }
    // 如果(字符串A的长度<字符串B长度)，或者(字符串A的长度==字符串B长度 且 字符串A<字符串B)
    // 则将 A 和 B 交换, 并输出一个负号
    if (A.length() < B.length() || (A.length() == B.length() && A < B)) {
        swap(A, B);
        cout << "-";
    }

    int len = max(A.length(), B.length());
    for (int i = A.length() - 1, j = 1; i >= 0; i--, j++)
        a[j] = A[i] - '0';
    for (int i = B.length() - 1, j = 1; i >= 0; i--, j++)
        b[j] = B[i] - '0';
    for (int i = 1; i <= len; i++) { // 每一位要处理
        c[i] = c[i] + a[i] - b[i];
        if (c[i] < 0) {
            c[i] += 10;
            c[i + 1] -= 1;
        }
    }
    int len2;
    for (len2 = len; len2 >= 1; len2--)
        if (c[len2] != 0)
            break;
    if (len2 == 0) len2 = 1; // 如果答案是0，c数组的值全是0，也就是len2是0时，要把len2赋值为1，使其至少输出一个0
    for (int i = len2; i >= 1; i--)
        cout << c[i];
    return 0;
}