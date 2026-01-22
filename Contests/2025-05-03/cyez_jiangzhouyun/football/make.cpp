#include<bits/stdc++.h>

using namespace std;

signed main(){
    mt19937 rng(4649);
    int n=1.5e3,k=64;
    cout<<n<<' '<<k<<endl;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=k;j++) cout<<(rng()&1);cout<<endl;
    }

    return 0;
}