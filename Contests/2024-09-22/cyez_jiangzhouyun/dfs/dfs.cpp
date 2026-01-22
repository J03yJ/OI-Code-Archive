#include<bits/stdc++.h>

using namespace std;

ifstream fin("dfs.in");
ofstream fout("dfs.out");
#define cin fin
#define cout fout

#define int long long
const int N=1e3+9;
const int mod=998244353;

int fi[N],to[N<<1],ne[N<<1],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int fac[N];
void Init(int lim){
    fac[0]=1;
    for(int i=1;i<=lim;i++) fac[i]=fac[i-1]*i%mod;
}
int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}

int fa[N],siz[N],p[N],w[N],n;
vector<int> f[N];
vector<vector<int>> dp,ldp,nll;
void DFS(int x){
    siz[x]=1;
    vector<int> son;
    p[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        son.push_back(y);
        fa[y]=x;
        DFS(y);
        siz[x]+=siz[y];
        p[x]=p[x]*p[y]%mod;
    }
    w[x]=p[x];
    p[x]=p[x]*fac[son.size()]%mod;

    nll=vector<vector<int>>(son.size()+1,vector<int>(n+1,0));
    dp=nll;
    dp[0][1]=1;
    for(int y:son){
        for(int i=son.size()-1;~i;i--){
            for(int j=n-siz[y];j>=0;j--){
                dp[i+1][j+siz[y]]=(dp[i+1][j+siz[y]]+dp[i][j])%mod;
            }
        }
    }
    for(int y:son){
        f[y]=vector<int>(n+1,0);
        ldp=nll;
        for(int i=0;i<=son.size();i++){
            for(int j=0;j<=n;j++){
                ldp[i][j]=dp[i][j];
                if(i>=1&&j>=siz[y]) ldp[i][j]=(ldp[i][j]-ldp[i-1][j-siz[y]]+mod)%mod;
                f[y][j]=(f[y][j]+ldp[i][j]*fac[i]%mod*fac[son.size()-i-1]%mod)%mod;
            }
        }
        ldp.clear();
    }
    dp.clear();
    nll.clear();
}
vector<int> Mul(vector<int> &a,vector<int> &b){
    vector<int> c=vector<int>(n+1,0);
    for(int i=0;i<=n;i++){
        for(int j=0;i+j<=n;j++){
            c[i+j]=(c[i+j]+a[i]*b[j]%mod)%mod;
        }
    }
    return c;
}
void Solve(int x,int k){
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        f[y]=Mul(f[x],f[y]);
        Solve(y,k*w[x]%mod*QPow(p[y],mod-2)%mod);
    }
    k=k*p[x]%mod;
    for(int i=0;i<=n;i++) f[x][i]=f[x][i]*k%mod;
}

signed main(){
    cin>>n;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        AdEg(u,v);
        AdEg(v,u);
    }

    Init(n);
    DFS(1);
    f[1]=vector<int>(n+1,0);
    f[1][1]=1;
    Solve(1,1);

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) cout<<f[i][j]<<' ';cout<<'\n';
    }

    return 0;
}