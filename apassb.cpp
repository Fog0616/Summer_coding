

#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>
using namespace std;
int main()
{
	string a;
	string b;
	string c;
	cin >> a >> b;
	if (a.size() < b.size()) {
		swap(a, b); // 确保 a 是较长的字符串
	}
	reverse(a.begin(), a.end());//反转字符串能够初始化成相同长度的字符串
	reverse(b.begin(), b.end());
	b.resize(a.size(),'0');//必须初始化为字符零进行运算不然会导致计算的值丢失
	c = a;  //赋值c字符串
	//a 123
	//b  12   
	//c 123
	int jin = 0;
	for (int i = 0; i < a.size(); i++)
	{
		//数字 = 字符 - '0'
		int a1=a[i] -= '0';//字符'0'转换成 数字'0' 
		int a2=b[i] -= '0';
		int temp = a1 + a2 + jin;
		 jin = 0;
		 if(temp>9)
		 {
			 jin++; //1
			 c[i] = (temp % 10+'0');
	 	 }
		 else 
		 {
			 //字符 = 数字 + '0'
			 c[i] = temp + '0';//数字'0' 转换成 字符'0'
		 }
	}

	if (jin == 1) { c += '1';}// 尾插字符'1'
	
	auto it = c.rbegin();
	while (it != c.rend())
	{
		cout << *it;
		it++;
	}
	return 0;
}


