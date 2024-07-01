#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;

const int fx[] = {0, -2, -1, 1, 2, 2, 1, -1, -2};
const int fy[] = {0, 1, 2, 2, 1, -1, -2, -2, -1};
int bx, by, mx, my;
ll f[2][40];    //第一维大小为 2 就好
bool s[40][40];

int main(){
    scanf("%d%d%d%d", &bx, &by, &mx, &my);
    bx += 2; by += 2; mx += 2; my += 2;
    f[1][2] = 1; //初始化
    s[mx][my] = 1;
    for(int i = 1; i <= 8; i++) s[mx + fx[i]][my + fy[i]] = 1;
    for(int i = 2; i <= bx; i++){
        for(int j = 2; j <= by; j++){
            if(s[i][j]){
                f[i & 1][j] = 0; //被马拦住了记住清零
                continue;
            }
            f[i & 1][j] = f[(i - 1) & 1][j] + f[i & 1][j - 1]; 
            //新的状态转移方程
        }
    }
    printf("%lld\n", f[bx & 1][by]);
    //输出的时候第一维也要按位与一下
    return 0;
} 