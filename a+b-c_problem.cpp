#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int a[10090], b[10090], c[10090];

void add(){
    string A, B;
    cin >> A >> B;
    int len = max(A.length(), B.length());
    for (int i = A.length() - 1, j = 1; i >= 0; i--, j++)
        a[j] = A[i] - '0';
    for (int i = B.length() - 1, j = 1; i >= 0; i--, j++)
        b[j] = B[i] - '0';

    // 第二步：处理每一位数字（共 len 位），从个位开始操作
    for (int i = 1; i <= len; i++) {
        c[i] = a[i] - b[i] + c[i]; // 答案的第 i 位就是 c[i] 本身加上 a[i] 减去 b[i]
        if (c[i] < 0) {
            // 第 i 位向第 i+1 位借一个。第 i 位加 10，第 i+1 位减 1
            c[i] += 10;
            c[i + 1]--;
        }
    }

    // 第三步：输出
    // 找到 c[i] 最右边的非零数字。len2 从 len 枚举到 1
    int len2;
    for (len2 = len; len2 >= 1; len2--)
        if (c[len2] != 0) // 如果这一位不是 0
            break; // 跳出循环

    if (len2 == 0) // 如果答案是0，c数组的值全是0，也就是len2是0时，要把len2赋值为1，使其至少输出一个0
        len2 = 1;

    // 从后往前，输出答案
    //for (int i = len2; i >= 1; i--)
    //    cout << c[i];
    
}
int main() {
    add();
    string A,B;
    cin>>B;
    for(auto &v:A.length()) A[v]=c[v];
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
