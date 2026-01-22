#include<bits/stdc++.h>

using namespace std;

ifstream fin("polka.in");
ofstream fout("polka.out");
#define cin fin
#define cout fout
#define int long long

const int N=2e5+9;
const int mod=998244353;
const int inf=1e9+7;

int a[N],mx[N],mx2[N],pre[N],pre2[N],n,ans;
void Solve(int l,int r){
    if(l==r) return ;
    int mid=(l+r)>>1;
    Solve(l,mid),Solve(mid+1,r);

    for(int i=l;i<=r;i++) mx[i]=mx2[i]=-inf;
    mx[mid]=a[mid];
    for(int i=mid-1;i>=l;i--){
        mx[i]=mx[i+1],mx2[i]=mx2[i+1];
        if(a[i]>mx[i]) mx2[i]=mx[i],mx[i]=a[i];
        else if(a[i]>mx2[i]) mx2[i]=a[i];
    }
    mx[mid+1]=a[mid+1];
    for(int i=mid+2;i<=r;i++){
        mx[i]=mx[i-1],mx2[i]=mx2[i-1];
        if(a[i]>mx[i]) mx2[i]=mx[i],mx[i]=a[i];
        else if(a[i]>mx2[i]) mx2[i]=a[i];
    }

    pre[mid]=pre2[mid]=0;
    for(int i=mid+1;i<=r;i++) pre[i]=(pre[i-1]+mx[i]%mod+mod)%mod;
    for(int i=mid+1;i<=r;i++) pre2[i]=(pre2[i-1]+mx2[i]%mod+mod)%mod;
    
    for(int i=mid,j=mid+1,il=mid+1,ir=mid+1;i>=l;i--){
        while(il<=r&&mx2[i]>mx[il]) il++;
        while(j<=r&&mx[i]>mx[j]) j++;
        while(ir<=r&&mx[i]>mx2[ir]) ir++;
        ans=(ans+(il-mid-1)*mx2[i]%mod)%mod;
        ans=(ans+(pre[j-1]-pre[il-1]+mod)%mod)%mod;
        ans=(ans+(ir-j)*mx[i]%mod)%mod;
        ans=(ans+(pre2[r]-pre2[ir-1]+mod)%mod)%mod;
    }
}

signed main(){
    int c,T;
    cin>>c>>T;
    while(T--){
        ans=0;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        Solve(1,n);
        cout<<ans<<endl;
    }
    return 0;
}