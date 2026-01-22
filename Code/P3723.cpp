#include<bits/stdc++.h>

using namespace std;

#define ssiz(x) (signed)x.size()
#define Append(a,b) a.insert(a.end(),b.begin(),b.end())

#define int long long
const int mod=998244353;
int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}
#define Inv(x) QPow(x,mod-2)

const int gmod=3;
const int invg=Inv(gmod);
using Poly=vector<int>;

void NTT(Poly &f,Poly &r,int lim,int flag){
    for(int i=0;i<lim;i++) if(i<r[i]) swap(f[i],f[r[i]]);
    for(int k=1;k<lim;k<<=1){
        int len=k<<1,gn=QPow(flag>0?gmod:invg,(mod-1)/len);
        for(int i=0;i<lim;i+=len){
            for(int j=0,g=1;j<k;j++,g=g*gn%mod){
                int tmp=f[i+j+k]*g%mod;
                f[i+j+k]=(f[i+j]-tmp+mod)%mod;
                f[i+j]=(f[i+j]+tmp)%mod;
            }
        }
    }
    if(flag==1) return ;
    int inv=Inv(lim);
    for(int i=0;i<lim;i++) f[i]=f[i]*inv%mod;
}
Poly Conv(Poly f,Poly g){
    int len=ssiz(f)+ssiz(g)-1,lim=1;
    while(lim<len) lim<<=1;
    f.resize(lim,0),g.resize(lim,0);
    
    Poly rev(lim,0),h(lim,0);
    for(int i=0;i<lim;i++){
        rev[i]=rev[i>>1]>>1;
        if(i&1) rev[i]|=lim>>1;
    }
    NTT(f,rev,lim,1),NTT(g,rev,lim,1);
    for(int i=0;i<lim;i++) h[i]=f[i]*g[i]%mod;
    NTT(h,rev,lim,-1);

    h.resize(len,0);
    return h;
}

signed main(){
    int n,m;
    cin>>n>>m;

    vector<int> a(n),b(n);
    for(int &x:a) cin>>x;
    for(int &x:b) cin>>x;

    int ans=0,sum=0;
    for(int x:a) ans+=x*x,sum+=x;
    for(int x:b) ans+=x*x,sum-=x;
    int res=1e18;
    for(int i=-2*m;i<=2*m;i++) res=min(res,n*i*i+2*i*sum);

    int tmp=0;
    reverse(b.begin(),b.end());
    Append(a,a);
    auto c=Conv(a,b);
    for(int i=n-1;i<ssiz(c);i++) tmp=max(tmp,c[i]);
    
    cout<<res+ans-2*tmp<<endl;

    return 0;
}