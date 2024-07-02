
#include <bits/c++config.h>
#include <bits/stringfwd.h>
#include <bits/char_traits.h>  // NB: In turn includes stl_algobase.h
#include <bits/allocator.h>
#include <bits/cpp_type_traits.h>
#include <bits/localefwd.h>    // For operators >>, <<, and getline.
#include <bits/ostream_insert.h>
#include <bits/stl_iterator_base_types.h>
#include <bits/stl_iterator_base_funcs.h>
#include <bits/stl_iterator.h>
#include <bits/stl_function.h> // For less
#include <ext/numeric_traits.h>
#include <bits/stl_algobase.h>
#include <bits/range_access.h>
#include <bits/basic_string.h>
#include <bits/basic_string.tcc>
//=string
#include<iostream>
using namespace std;
const int maxn=1e6+5;
struct node{
    int head;
    string name;

}a[maxn];
int n,m,x,y;
int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++)
    {
        cin>>a[i].head>>a[i].name;
    }
    int now=0;
    for(int i=1;i<=m;i++)
    {
        cin>>x>>y;
        if(a[now].head==0&&x==0)now=(now+n-y)%n;
        else if(a[now].head==0&&x==1)now=(now+y)%n;
        else if(a[now].head==1&&x==0)now=(now+y)%n;
        else if(a[now].head==1&&x==1)now=(now+n-y)%n;
    }
    cout<<a[now].name<<endl;
    return 0;
}
