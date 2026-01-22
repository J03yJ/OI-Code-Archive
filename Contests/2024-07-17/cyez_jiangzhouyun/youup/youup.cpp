#include<bits/stdc++.h>

using namespace std;

ifstream fin("youup.in");
ofstream fout("youup.out");
#define cin fin
#define cout fout

#define int long long
const int N=3e5+9;
const int p=998244353;

int fi[N],ne[N<<2],to[N<<2],adj;
void adeg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}
const int K=3e3+9;
int dis[K][K],vis[N],ans[N];
void dfs(int root,int x){
    vis[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(vis[y]) continue ;
        dis[root][y]=dis[root][x]+1;
        dfs(root,y);
    }
}

int fac[N],inv[N];
int qpow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%p;
        x=x*x%p;
        y>>=1;
    }
    return res;
}
void init(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%p;
    inv[n]=qpow(fac[n],p-2);
    for(int i=n-1;~i;i--) inv[i]=inv[i+1]*(i+1)%p;
}
int c(int n,int m){
    if(m>n) return 0;
    return fac[n]*inv[m]%p*inv[n-m]%p;
}

signed main(){
    int C,n,k;
    cin>>C>>n>>k;
    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        adeg(x,y);
        adeg(y,x);
    }
    if(k==0||n==1){
        cout<<n<<' ';for(int i=2;i<=n;i++) cout<<0<<' ';
        cout<<endl;
        return 0;
    }
    if(k==1||n==2){
        cout<<n<<' '<<n-1<<' ';for(int i=3;i<=n;i++) cout<<0<<' ';
        cout<<endl;
        return 0;
    }
    if(C<=2){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++) vis[j]=0;
            dfs(i,i);

        }
        for(int sta=1;sta<(1<<n);sta++){
            vector<int> v;
            for(int i=0;i<n;i++) if(sta>>i&1) v.push_back(i+1);
            bool err=0;
            for(int x:v){
                for(int y:v){
                    if(dis[x][y]>k){
                        err=1;
                        break ;
                    }
                }
                if(err) break ;
            }
            if(!err) ans[v.size()]++;
        }
        for(int i=1;i<=n;i++) cout<<ans[i]%p<<' ';cout<<endl;
    }else if(C==4){
        init(n);
        for(int i=1;i<=n;i++) ans[i]=c(n,i);
        for(int i=1;i<=n;i++) cout<<ans[i]<<' ';cout<<endl;
    }else if(C==5){
        init(n);
        for(int i=1;i<=n;i++) ans[i]=c(k+1,i);
        for(int i=1;i<=n;i++) ans[i]=(ans[i]+c(k,i-1)*(n-k-1)%p)%p;
        for(int i=1;i<=n;i++) cout<<ans[i]<<' ';cout<<endl;
    }

    return 0;
}