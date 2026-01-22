#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e5+9;
const int mod=998244353;
const int lim=1e5+5;

int f[N],g[N],cf[N],cg[N],a[N],n;
vector<int> p[N],q[N];

namespace Fen1{
    int tr[N];
    void Add(int x,int f){
        while(x<=lim){
            tr[x]=max(tr[x],f);
            x+=x&-x;
        }
    }
    int Ask(int x){
        int ans=0;
        while(x){
            ans=max(ans,tr[x]);
            x&=x-1;
        }
        return ans;
    }
}
namespace Fen2{
    int tr[N];
    void Add(int x,int c){
        while(x<=lim){
            tr[x]=(tr[x]+c)%mod;
            x+=x&-x;
        }
    }
    int Ask(int x){
        int ans=0;
        while(x){
            ans=(ans+tr[x])%mod;
            x&=x-1;
        }
        return ans;
    }
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    for(int i=1;i<=n;i++){
        f[i]=Fen1::Ask(a[i]-1)+1;
        Fen1::Add(a[i],f[i]);
        p[f[i]].push_back(i);
    }
    for(int i=1;i<=lim;i++) Fen1::tr[i]=0;
    for(int i=n;i>=1;i--){
        g[i]=Fen1::Ask(lim-a[i])+1;
        Fen1::Add(lim-a[i]+1, g[i]);
        q[g[i]].push_back(i);
    }
    for(int i=1;i<=lim;i++) Fen1::tr[i]=0;

    map<int,int> mp;
    int ans=f[n];
    for(int i=1;i<=n;i++) ans=max(ans,f[i]+g[i]-1);
    for(int i=1;i<=n;i++){
        if(f[i]+g[i]==ans+1) mp[f[i]]++;
    }

    for(int i=1;i<=n;i++){
        if(ans!=f[i]+g[i]-1) cout<<'1';
        else if(mp[f[i]]!=1) cout<<'2';
        else cout<<'3';
    }
    cout<<endl;

    return 0;
}