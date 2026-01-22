#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e5+9;
const int mod=1e9+7;

int a[N],f[N],g[N],pre[N],suc[N],p[N],n,ans;
void Work(int l,int r){
    if(l==r){
        ans=(ans+a[l])%mod;
        return ;
    }

    int mid=(l+r)>>1;
    Work(l,mid),Work(mid+1,r);

    f[mid]=a[mid],f[mid-1]=max(a[mid],a[mid-1]);
    g[mid]=0,g[mid-1]=a[mid-1];
    for(int i=mid-2;i>=l;i--){
        f[i]=max(f[i+1],f[i+2]+a[i]);
        g[i]=max(g[i+1],g[i+2]+a[i]);
    }
    f[mid+1]=a[mid+1],f[mid+2]=max(a[mid+1],a[mid+2]);
    g[mid+1]=0,g[mid+2]=a[mid+2];
    for(int i=mid+3;i<=r;i++){
        f[i]=max(f[i-1],f[i-2]+a[i]);
        g[i]=max(g[i-1],g[i-2]+a[i]);
    }

    iota(p+l,p+mid+1,l);
    sort(p+l,p+mid+1,[](int x,int y){return f[x]-g[x]<f[y]-g[y];});
    pre[l]=g[p[l]]%mod;for(int i=l+1;i<=mid;i++) pre[i]=(pre[i-1]+g[p[i]])%mod;
    suc[mid]=f[p[mid]]%mod;for(int i=mid-1;i>=l;i--) suc[i]=(suc[i+1]+f[p[i]])%mod;

    for(int i=mid+1;i<=r;i++){
        int pos=upper_bound(p+l,p+mid+1,i,[](int x,int y){return f[x]-g[x]<f[y]-g[y];})-p;
        if(pos<=mid){
            ans=(ans+suc[pos])%mod;
            ans=(ans+g[i]%mod*(mid-pos+1)%mod)%mod;
        }
        if(pos>l){
            ans=(ans+pre[pos-1])%mod;
            ans=(ans+f[i]%mod*(pos-l)%mod)%mod;
        }
    }
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    Work(1,n);
    cout<<ans<<endl;

    return 0;
}