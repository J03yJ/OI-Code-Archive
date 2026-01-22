#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

using ll=long long;
const int N=2e5+9;
const int mod=998244353;

int a[N],n;
int FallPow(ll n,ll m){
    if(m>n||m<0) return 0;
    int res=1;
    for(int i=1;i<=m;i++) res=1ll*res*((n-i+1)%mod)%mod;
    return res;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    ll sum=0,prod=1;
    for(int i=1;i<=n;i++){
        sum+=a[i];
        prod=1ll*prod*a[i]%mod;
    }

    cout<<prod*FallPow(sum-n,n-2)%mod<<endl;

    return 0;
}