#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
using namespace std;

const int MAXN = 1000; // Adjust the size as needed

int a[MAXN], b[MAXN], c[2 * MAXN]; // Arrays to store digits of numbers and the result

int main() {
    string A, B;
    cin >> A >> B;
    int lena = A.length(), lenb = B.length();

    // Initialize arrays to store digits
    for (int i = 0; i < MAXN; i++) a[i] = b[i] = c[i] = 0;
    for (int i = MAXN; i < 2 * MAXN; i++) c[i] = 0;

    // Convert string A to integer array a
    for (int i = lena - 1; i >= 0; i--) a[lena - i] = A[i] - '0';
    // Convert string B to integer array b
    for (int i = lenb - 1; i >= 0; i--) b[lenb - i] = B[i] - '0';

    int len = lena + lenb; // The maximum possible length of the result

    // Perform multiplication
    for (int i = 1; i <= lena; i++)
        for (int j = 1; j <= lenb; j++)
            c[i + j - 1] += a[i] * b[j];

    // Handle carry
    for (int i = 1; i <= len; i++) {
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    }

    // Remove leading zeros
    while (len > 1 && c[len] == 0) len--;

    // Output the result
    for (int i = len; i >= 1; i--) printf("%d", c[i]);
    cout << endl;

    return 0;
}
//赶时间先提交，抱歉助教，之前缺课