#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;
const int mod=998244353;

int a[N],n,k;
int zpre[N],kpre[N],f[N],g[N];

signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];

    map<int,int> buc;
    buc[0]=1;
    for(int i=1;i<=n;i++){
        a[i]+=a[i-1];
        zpre[i]=buc[a[i]]-1;
        kpre[i]=buc[a[i]-k]-1;
        buc[a[i]]=i+1;
    }
    f[0]=g[0]=1;
    int sum=1;
    for(int i=1;i<=n;i++){
        if(kpre[i]>=0) f[i]=(sum-g[kpre[i]]+mod)%mod;
        else f[i]=sum;
        // cout<<kpre[i]<<' '<<sum<<' '<<sum-g[kpre[i]]<<endl;
        if(zpre[i]>=0) g[i]=(f[i]+g[zpre[i]])%mod;
        else g[i]=f[i];
        sum=(sum+f[i])%mod;
        // cout<<f[i]<<' '<<g[i]<<' '<<kpre[i]<<' '<<zpre[i]<<' '<<sum<<endl;
    }
    cout<<f[n]<<endl;

    return 0;
}