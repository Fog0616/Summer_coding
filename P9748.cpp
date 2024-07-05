#include <bits/stdc++.h>

using namespace std;

int n, a, b;

int main()
{
		cin >> n;
	
	for (int i = 1; ; ++ i )
	{
		if (n == 0) break;
		if (!a && n % 3 == 1) b = i;
		n -= ceil(n / 3.0);
		++ a;
	}
	
	cout << a << ' ' << b << endl;
	
	return 0;	
}