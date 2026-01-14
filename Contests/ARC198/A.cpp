#include<bits/stdc++.h>

using namespace std;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    int n;
    cin>>n;

    if(n==1){
        cout<<1<<endl;
        cout<<1<<endl;
        return 0;
    }

    cout<<n/2<<endl;
    for(int i=2;i<=n;i+=2) cout<<i<<' ';cout<<endl;

    return 0;
}