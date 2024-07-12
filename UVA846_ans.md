# UVA846 Steps.
[原题传送门](https://www.luogu.com.cn/problem/UVA846 "UVA846")  [题目PDF](https://uva.onlinejudge.org/external/8/p846.pdf)
## 思路：
##### 我们需要计算从位置 $x$ 到位置 $y$ 的最少步数，遵循以下规则：

1. 第一步和最后一步的距离必须为 $1$。

2. 除第一步外，每一步的距离都必须比前一步的距离最多相差$1$（其差值的绝对值为 $0$ 或 $1$ ）。

##### 实现方法：
- 首先计算从 $x$ 到 $y$ 的距离 $d$，即 $d = y - x$ 。
- 然后模拟步数的增长，直到达到或超过距离 $d$ 。

## AC Code:
```cpp
#include <iostream>
using namespace std;

int minSteps(int x, int y) {
    int d = y - x; // 计算距离
    if (d == 0) return 0; // 如果起点和终点相同，不需要移动
    int step = 0;
    int sum = 0;
    while (sum < d) {
        step++;
        sum += (step + 1) / 2; // 累加步数，模拟增长
    }
    return step;
}

int main() {
    int t; // 读取数据组数
    cin >> t;
    while (t--) {
        int x, y;
        cin >> x >> y;
        cout << minSteps(x, y) << endl; // 输出每组数据的最少步数
    }
    return 0;
}
```