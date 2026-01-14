#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=4e5+9;

int a[N],n,m;

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i+1],a[i+n+1]=a[i+1];

    int ans=0;
    map<int,int> mp;
    for(int i=1;i<=n+n;i++) a[i]+=a[i-1];
    for(int i=1;i<=n;i++) mp[a[i]%m]++;
    for(int i=n+1;i<=n+n;i++){
        mp[a[i-n]%m]--;
        ans+=mp[a[i]%m];
        mp[a[i]%m]++;
    }

    cout<<ans<<endl;

    return 0;
}