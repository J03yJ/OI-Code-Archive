#include<bits/stdc++.h>

using namespace std;

#define int long long
const int inf=1e18;

signed main(){
    int a;
    cin>>a;
    int l=a-inf%a*9%a*9%a;
    int r=l+inf-1;
    cout<<l<<' '<<r<<endl;
}