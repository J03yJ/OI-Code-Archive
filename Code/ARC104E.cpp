#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=6+9;
const int mod=1e9+7;
const int inf=1e9+7;
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
#define Inv(x) QPow(x,mod-2)

int rk[N],a[N],n;
inline bool Check(){
    vector<int> vis(n+1,0);
    vis[0]=1;
    for(int i=1;i<=n;i++) vis[rk[i]]=1;
    for(int i=1;i<=n;i++) if(vis[i]&&!vis[i-1]) return 0;
    return 1;
}
int lim[N],f[N][N],m,ans;
inline int C(int n,int m){
    if(m<0||n<m) return 0;
    if(!m) return 1;
    else return Mul(C(n-1,m-1),Mul(n,Inv(m)));
}
inline int LIS(){
    vector<int> f(n+1);
    f[0]=0;
    int res=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<i;j++) if(rk[j]<rk[i]) f[i]=max(f[i],f[j]+1);
        res=max(res,f[i]);
    }
    return res;
}
inline void Work(){
    if(!Check()) return ;
    m=0;
    for(int i=1;i<=n;i++) m=max(m,rk[i]);
    for(int i=1;i<=m;i++) lim[i]=inf;
    for(int i=1;i<=n;i++) lim[rk[i]]=min(lim[rk[i]],a[i]);
    
    vector<int> val({0});
    for(int i=1;i<=m;i++) val.push_back(lim[i]);
    sort(val.begin(),val.end());
    val.erase(unique(val.begin(),val.end()),val.end());
    int tot=val.size()-1;
    for(int i=1;i<=m;i++) lim[i]=lower_bound(val.begin(),val.end(),lim[i])-val.begin();
    
    memset(f,0,sizeof f);
    f[0][0]=1;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=tot;j++){
            for(int k=1;k<=i;k++){
                int tmp=C(val[j]-val[j-1],i-k+1);
                bool flag=0;
                for(int p=k;p<=i;p++) if(lim[p]<j) flag=1;
                if(flag) continue ;
                for(int p=0;p<j;p++) AddAs(f[i][j],Mul(f[k-1][p],tmp));
            }
        }
    }
    int tmp=0;
    for(int i=1;i<=lim[m];i++) AddAs(tmp,f[m][i]);
    AddAs(ans,Mul(tmp,LIS()));
}
inline void Solve(int i){
    if(i>n) return Work();
    for(int j=1;j<=n;j++){
        rk[i]=j;
        Solve(i+1);
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    Solve(1);
    int mul=1;
    for(int i=1;i<=n;i++) MulAs(mul,a[i]);
    cout<<Mul(ans,Inv(mul))<<endl;

    return 0;
}