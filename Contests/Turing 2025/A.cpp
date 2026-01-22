#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=5e3+9;
const int mod=1e9+7;
inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) MulAs(res,x);
        MulAs(x,x);
        y>>=1;
    }
    return res;
}
inline int Inv(int x){return QPow(x,mod-2);}
inline int Mod(ll x){return x%mod;}

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int fac[N],ifac[N];
inline void Init(int lim){
    fac[0]=1;
    for(int i=1;i<=lim;i++) fac[i]=Mul(fac[i-1],i);
    ifac[lim]=Inv(fac[lim]);
    for(int i=lim-1;~i;i--) ifac[i]=Mul(ifac[i+1],i+1);
}
inline int C(int n,int m){return m<0||m>n?0:Mul(fac[n],Mul(ifac[n-m],ifac[m]));}
inline int P(int n,int m){return Mul(fac[m],C(n,m));}

const int M=3e2+9;

int a[N],b[N],fa[N],n;
int f[N][N],g[N][N][2],h[N][N][2],siz[N];
bitset<N> hav[N];
inline void DFS(int x){
    int maxb=-1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        DFS(y);
        hav[x]|=hav[y];
        maxb=max(maxb,b[y]);
    }
    if(~a[x]) hav[x].set(a[x],1);
    
    // cout<<"# "<<x<<" : "<<endl;
    // cout<<"  MAXB = "<<maxb<<endl;
    
    siz[x]=1;
    if(~b[x]){
        if(maxb>b[x]) return ;
        if(hav[x][b[x]]) return ;
        // cout<<"  Bx neq -1."<<endl;
        if(!~a[x]){
            g[x][1][0]=1,g[x][0][0]=max(maxb,0);
            if(b[x]!=maxb) g[x][0][1]=1;
        }else if(a[x]==maxb) g[x][0][1]=1;
        else g[x][0][0]=1;
        // cout<<"  G : ";for(int j=0;j<=siz[x];j++) cout<<g[x][j][0]<<'/'<<g[x][j][1]<<' ';cout<<endl;
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            for(int j=0;j<=siz[x];j++){
                h[x][j][0]=exchange(g[x][j][0],0);
                h[x][j][1]=exchange(g[x][j][1],0);
            }
            // cout<<"  From "<<y<<' '<<b[y]<<endl;
            if((~maxb)&&b[y]!=maxb){
                for(int j=0;j<=siz[x];j++){
                    for(int k=0;k<=siz[y];k++){
                        for(int p=0;p<=k;p++){
                            int w0=Mul(QPow(maxb-b[y]-1,p),C(k,p));
                            int w1=Mul(QPow(maxb-b[y],p),C(k,p));
                            AddAs(g[x][j+k-p][0],Mul(w0,Mul(h[x][j][0],f[y][k])));
                            AddAs(g[x][j+k-p][1],Mul(Sub(w1,w0),Mul(h[x][j][0],f[y][k])));
                            AddAs(g[x][j+k-p][1],Mul(w1,Mul(h[x][j][1],f[y][k])));
                        }
                    }
                }
            }else{
                for(int j=0;j<=siz[x];j++){
                    for(int k=0;k<=siz[y];k++){
                        AddAs(g[x][j+k][0],Mul(h[x][j][0],f[y][k]));
                        AddAs(g[x][j+k][1],Mul(h[x][j][1],f[y][k]));
                    }
                }
            }
            siz[x]+=siz[y];
            // cout<<"  G : ";for(int j=0;j<=siz[x];j++) cout<<g[x][j][0]<<'/'<<g[x][j][1]<<' ';cout<<endl;
        }
        int cnt=0;
        bool flag=(~maxb)&&b[x]!=maxb;
        for(int i=max(maxb+1,0);i<b[x];i++) if(!hav[x][i]) cnt++;
        for(int i=0;i<=siz[x];i++){
            for(int j=cnt;j<=i;j++){
                int w=0,v=b[x]-max(maxb,0);
                for(int k=0;k<=cnt;k++){
                    AddAs(w,Mul(Mul(C(cnt,k),QPow(Sub(v,k),j)),QPow(mod-1,k)));
                    // cout<<"    W : "<<w<<' '<<v<<' '<<k<<endl;
                }
                // cout<<"  ToF : "<<i<<' '<<j<<' '<<cnt<<' '<<w<<' '<<g[x][i][flag]<<endl;
                AddAs(f[x][i-j],Mul(Mul(C(i,j),w),g[x][i][flag]));
            }
        }
    }else f[x][bool(!~a[x])]=1;
    // cout<<"  F : ";
    // for(int j=0;j<=siz[x];j++) cout<<f[x][j]<<' ';cout<<endl;
}
inline int Calc(int x){
    int ans=0;
    for(int i=0;i<=siz[x];i++) AddAs(ans,Mul(QPow(n-b[x],i),f[x][i]));
    return ans;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    for(int i=2;i<=n;i++){
        cin>>fa[i];
        if(fa[i]!=1&&b[fa[i]]==-1) fa[i]=fa[fa[i]];
        AddEdge(fa[i],i);
    }
    Init(n);

    int ans=1;
    if(~b[1]){
        DFS(1);
        MulAs(ans,Calc(1));
        cout<<ans<<endl;
    }else{
        MulAs(ans,~a[1]?1:n+1);
        for(int i=fi[1];i;i=ne[i]){
            int x=to[i];
            DFS(x);
            MulAs(ans,Calc(x));
        }
        cout<<ans<<endl;
    }

    return 0;
}