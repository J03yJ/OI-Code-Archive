#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e6+9;

int a[N],x[N];

signed main(){
    int n,q;
    cin>>n;
    x[0]=-1e9-7;
    for(int i=1;i<=n;i++) cin>>x[i];
    for(int i=1;i<=n;i++) cin>>a[i],a[i]+=a[i-1];

    set<pair<int,int>> s;
    for(int i=0;i<=n;i++) s.insert({x[i],a[i]});
    cin>>q;
    while(q--){
        int l,r;
        cin>>l>>r;
        int sl=(--s.upper_bound({l-1,1e18}))->second;
        int sr=(--s.upper_bound({r,1e18}))->second;
        cout<<sr-sl<<endl;
    }
}