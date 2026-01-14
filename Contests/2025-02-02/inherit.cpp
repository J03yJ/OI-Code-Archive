#include<bits/stdc++.h>

using namespace std;

ifstream fin("inherit.in");
ofstream fout("inherit.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=5e5+9;

#define ssiz(x) (signed)x.size()
const int mod=998244353;
inline void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline void SubAs(int &x,int y){x-=y;if(x<0) x+=mod;}
inline int Add(int x,int y){x+=y;if(x>=mod) x-=mod;return x;}
inline int Sub(int x,int y){x-=y;if(x<0) x+=mod;return x;}
int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
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
            for(int j=0,g=1;j<k;j++,g=1ll*g*gn%mod){
                int tmp=1ll*f[i+j+k]*g%mod;
                f[i+j+k]=Sub(f[i+j],tmp);
                f[i+j]=Add(f[i+j],tmp);
            }
        }
    }
    if(!~flag){
        int inv=Inv(lim);
        for(int &x:f) x=1ll*x*inv%mod;
    }
}
Poly Conv(Poly &f,Poly &g){
    if(ssiz(f)+ssiz(g)<=64){
        Poly h(ssiz(f)+ssiz(g),0);
        for(int i=0;i<ssiz(f);i++){
            for(int j=0;j<ssiz(g);j++) AddAs(h[i+j],1ll*f[i]*g[j]%mod);
        }
        return h;
    }

    int len=ssiz(f)+ssiz(g)-1,lim=1;
    while(lim<len) lim<<=1;
    f.resize(lim,0),g.resize(lim,0);

    Poly rev(lim,0),h(lim,0);
    for(int i=0;i<lim;i++){
        rev[i]=rev[i>>1]>>1;
        if(i&1) rev[i]|=lim>>1;
    }
    NTT(f,rev,lim,1),NTT(g,rev,lim,1);
    for(int i=0;i<lim;i++) h[i]=1ll*f[i]*g[i]%mod;
    NTT(h,rev,lim,-1);

    h.resize(len,0);
    return h;
}

int n;char a[N];

void Work(Poly &f,Poly &g,int l,int r,string &s){
    if(l==r){
        if(l==0) f[l]=1;
        else if(s[l]=='<') f[l]=0;
        else f[l]=mod-f[l];
        return ;
    }
    int mid=l+r>>1;
    Work(f,g,l,mid,s);
    Poly f_(f.begin()+l,f.begin()+mid+1),g_(g.begin(),g.begin()+r-l+1);
    Poly h=Conv(f_,g_);
    for(int i=mid+1;i<=r;i++) AddAs(f[i],h[i-l]);
    Work(f,g,mid+1,r,s);
}

int Solve(string &s,Poly &ifac){
    int n=s.size();
    s.push_back('>');
    Poly f(ssiz(s),0);
    Work(f,ifac,0,n,s);
    int cnt=0;
    for(char c:s) if(c=='>') cnt++;
    return cnt&1?Sub(mod,f.back()):f.back();
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    Poly fac(n+2,0),ifac(n+2,0);
    fac[0]=1;for(int i=1;i<=n+1;i++) fac[i]=1ll*fac[i-1]*i%mod;
    ifac[n+1]=Inv(fac[n+1]);for(int i=n;~i;i--) ifac[i]=1ll*ifac[i+1]*(i+1)%mod;

    int ans=fac[n+1];
    for(int l=1,r;l<=n;l=r+1){
        r=l;
        while(r<=n&&a[r]!='?') r++;
        string s=" ";
        for(int i=l;i<r;i++) s.push_back(a[i]=='0'?'<':'>');
        ans=1ll*ans*Solve(s,ifac)%mod;
    }

    cout<<ans<<endl;

    return 0;
}