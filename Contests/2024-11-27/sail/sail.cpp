#include<bits/stdc++.h>

using namespace std;

ifstream fin("sail.in");
ofstream fout("sail.out");
#define cin fin
#define cout fout

#define int long long
const int N=2e3+9;
const int M=1e6+9;
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

int p[N],q[N],f[N][N],g[N][N],out[N],n,m,tot;
int err[N],r[N][N],e[N];
void Solve(){
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            if(r[j][i]){
                swap(r[i],r[j]);
                break ;
            }
        }
        if(!r[i][i]){
            err[i]=1;
            continue ;
        }
        int inv=Inv(r[i][i]);
        for(int j=i;j<=n+1;j++) r[i][j]=r[i][j]*inv%mod;
        for(int j=i+1;j<=n;j++){
            int tmp=r[j][i];
            if(!r[j][i]) continue ;
            for(int k=i;k<=n+1;k++) r[j][k]=(r[j][k]-tmp*r[i][k]%mod+mod)%mod;
        }
    }
    for(int i=n;i>=1;i--){
        if(!err[i]) e[i]=r[i][n+1];
        else{
            e[i]=-1;
            continue ;
        }
        for(int j=1;j<=n;j++){
            if(i==j) continue ;
            if(r[i][j]&&e[j]==-1){
                e[i]=-1;
                break ;
            }
            e[i]=(e[i]-e[j]*r[i][j]%mod+mod)%mod;
        }
    }
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>p[i],p[i]=p[i]*Inv(100)%mod,q[i]=(1+mod-p[i])%mod;
    m=ceil(sqrt(2*n));
    
    for(int i=1;i<=n;i++){
        memset(f,0,sizeof f);
        memset(g,0,sizeof g);
        f[i][m]=0,g[i][m]=1;
        auto C=[&i](int j,int k,int t,int ps){
            // cout<<"[]"<<j<<' '<<k<<' '<<t<<' '<<ps<<' '<<p[j]<<' '<<q[j]<<endl;
            if(!g[j][k+m]||!ps) return ;
            if(j+(k+t)>n||j+(k+t)<1){
                out[i]=(out[i]+(f[j][k+m]+g[j][k+m])*ps%mod)%mod;
            }
            else{
                f[j+(k+t)][m+(k+t)]=(f[j+(k+t)][m+(k+t)]+(f[j][k+m]+g[j][k+m])*ps%mod)%mod;
                g[j+(k+t)][m+(k+t)]=(g[j+(k+t)][m+(k+t)]+g[j][k+m]*ps%mod)%mod;
            }
        };
        C(i,0,1,q[i]);
        for(int j=i;j<=n;j++){
            for(int k=m;k>=1;k--) C(j,k,1,q[j]),C(j,k,-1,p[j]);
        }
        C(i,0,-1,p[i]);
        for(int j=i;j>=1;j--){
            for(int k=-m;k<=-1;k++) C(j,k,1,q[j]),C(j,k,-1,p[j]);
        }
        // for(int j=1;j<=n;j++){
        //     for(int k=-m;k<=m;k++) cout<<f[j][k+m]<<'/'<<g[j][k+m]<<' ';
        //     cout<<endl;
        // }
        // cout<<" : "<<out[i]<<endl;
        for(int j=1;j<=n;j++){
            if(i==j) r[i][j]=1;
            else r[i][j]=(mod-f[j][m])%mod;
        }
        r[i][n+1]=out[i];
        for(int j=1;j<=n+1;j++) cout<<r[i][j]<<' ';cout<<endl;
    }

    Solve();
    for(int i=1;i<=n;i++) cout<<(e[i]?e[i]:-1)<<' ';
    cout<<endl;

    return 0;
}