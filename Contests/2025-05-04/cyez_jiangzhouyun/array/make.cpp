#include<bits/stdc++.h>

using namespace std;

signed main(){
    mt19937 rng(4649);
    int n=1e5,m=2e3;
    cout<<0<<' '<<n<<' '<<m<<endl;
    for(int i=1;i<=n;i++) cout<<(rng()>>2)<<' ';cout<<endl;

    return 0;
}