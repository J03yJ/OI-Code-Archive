#include<bits/stdc++.h>

using namespace std;

const int V=1e9;

mt19937 rng(4649);

signed main(){
    int n=3e5,m=3e5;
    cout<<n<<' '<<m<<' '<<0<<endl;
    for(int i=1;i<=n;i++) cout<<rng()%V<<' ';cout<<endl;
    for(int i=1;i<=n;i++) cout<<rng()%200<<' ';cout<<endl;
    while(m--){
        // int l=rng()%n+1,r=rng()%n+1;
        int l=1,r=n;
        if(l>r) swap(l,r);
        cout<<l<<' '<<r<<' '<<rng()%V<<endl;
    }

    return 0;
}