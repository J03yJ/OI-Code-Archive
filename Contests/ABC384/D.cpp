#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;

int a[N],pre[N],suf[N],n,s;

signed main(){
    cin>>n>>s;
    for(int i=1;i<=n;i++) cin>>a[i];

    for(int i=1;i<=n;i++) pre[i]=pre[i-1]+a[i];
    for(int i=n;i>=1;i--) suf[i]=suf[i+1]+a[i];

    s%=pre[n];
    map<int,int> mp;
    for(int i=0;i<=n;i++) mp[s+pre[i]]=1;
    for(int i=0;i<=n;i++){
        if(mp[pre[i]]){
            cout<<"Yes"<<endl;
            return 0;
        }
    }

    mp.clear();
    for(int i=0;i<=n;i++) mp[s-pre[i]]=1;
    for(int i=0;i<=n;i++){
        if(mp[suf[i]]){
            cout<<"Yes"<<endl;
            return 0;
        }
    }

    cout<<"No"<<endl;

    return 0;
}