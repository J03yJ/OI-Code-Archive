#include<bits/stdc++.h>

using namespace std;

ifstream fin("ball.in");
ofstream fout("ball.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=6e3+9;
const int mod=1e9+7;
inline int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return res;
}
#define Inv(x) QPow(x,mod-2)
int fac[N],ifac[N];
inline void InitF(int lim){
    fac[0]=1;
    for(int i=1;i<=lim;i++) fac[i]=1ll*fac[i-1]*i%mod;
    ifac[lim]=Inv(fac[lim]);
    for(int i=lim-1;~i;i--) ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
}
inline int Cat(int x){return 1ll*fac[x<<1]*ifac[x]%mod*ifac[x+1]%mod;}

int l[N],r[N],siz[N],n,k;

vector<int> e[N];
int fa[N],tmp[N];

int f[N][N];
inline void DFS(int x){
    int lim=siz[x]-1;
    for(int y:e[x]) lim-=siz[y];
    f[x][lim]=1;
    for(int y:e[x]){
        DFS(y);
        for(int i=0;i<=lim;i++) tmp[i]=f[x][i],f[x][i]=0;
        for(int i=0;i<=siz[y];i++){
            for(int j=0;j<=lim;j++){
                f[x][i+j]=(f[x][i+j]+1ll*f[y][i]*tmp[j])%mod;
            }
        }
        lim+=siz[y];
    }
    for(int i=0;i<=lim;i++) tmp[i]=f[x][i],f[x][i]=0;
    for(int i=0;i<=lim;i++){
        f[x][i+1]=(f[x][i+1]+tmp[i])%mod;
        f[x][0]=(f[x][0]+1ll*tmp[i]*Cat(i))%mod;
    }
}

signed main(){
    cin>>n>>k;
    for(int i=1;i<=k;i++) cin>>l[i]>>r[i];

    n<<=1;
    InitF(n);
    l[0]=0,r[0]=n+1;

    vector<int> v({0});
    for(int i=1;i<=k;i++) if((l[i]^r[i])&1) v.push_back(i);
    for(int i:v) siz[i]=r[i]-l[i]+1>>1;
    sort(v.begin(),v.end(),[](int x,int y){return siz[x]>siz[y];});
    for(int i:v){
        fa[i]=tmp[l[i]];
        if(i) e[fa[i]].push_back(i);
        for(int j=l[i];j<=r[i];j++) tmp[j]=i;
    }

    DFS(0);
    cout<<f[0][0]<<endl;

    return 0;
}