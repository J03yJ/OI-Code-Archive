#include<bits/stdc++.h>

using namespace std;

ifstream fin("rand.in");
ofstream fout("rand.out");
#define cin fin
#define cout fout

#define int long long
const int N=5e2+9;
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

int a[N][N],f[N],g[N],n,m,inv;
vector<pair<int,int>> q[N];

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
        }
        sort(a[i]+1,a[i]+m+1);
    }
    inv=Inv(m);

    vector<int> val;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            val.push_back(a[i][j]);
        }
    }
    val.push_back(0);
    sort(val.begin(),val.end());
    val.erase(unique(val.begin(),val.end()),val.end());
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int pos=lower_bound(val.begin(),val.end(),a[i][j])-val.begin();
            q[pos].push_back({j-1,0});
            q[pos].push_back({j,1});
        }
    }
    
    f[n]=QPow(m,n);
    int lst=0,ans=0;
    for(int t=1;t<val.size();t++){
        int x=val[t];
        for(pair<int,int> o:q[t]){
            int p=o.first,q=m-p;
            if(o.second==0){
                if(!p){}
                g[0]=f[0]*Inv(p);
                for(int i=1;i<=n;i++){
                    g[i]=(f[i]-g[i-1]*q%mod+mod)%mod*Inv(p)%mod;
                    cout<<f[i]<<' '<<g[i-1]<<' '<<g[i]<<endl;
                }
                for(int i=0;i<=n;i++) f[i]=g[i];
            }else{
                for(int j=n-1;j>=0;j--) f[j+1]=(f[j+1]*p+f[j]*q)%mod;
                f[0]=f[0]*p%mod;
            }
            cout<<o.first<<' '<<o.second<<endl;
            for(int i=0;i<=n;i++) cout<<f[i]<<' ';cout<<endl;
        }
        for(int i=(n+1)/2;i<=n;i++) ans=(ans+f[i]*(x-lst)%mod)%mod;
        lst=x;
    }
    cout<<ans<<endl;

    return 0;
}