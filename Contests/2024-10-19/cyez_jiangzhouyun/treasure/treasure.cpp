#include<bits/stdc++.h>

using namespace std;

ifstream fin("treasure.in");
ofstream fout("treasure.out");
#define cin fin
#define cout fout

const int N=1e2+9;
const int mod=998244353;

int p[N],q[N],vis[N],n;

int f[N],g[N],r[N];
int Solve(){
    for(int i=1;i<=n;i++) r[p[i]]=q[i];
    for(int i=0;i<=n+1;i++) f[i]=g[i]=0;
    f[0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=n+1;j++) g[j]=f[j],f[j]=0;
        for(int j=0;j<=n+1;j++){
            if(!g[j]) continue ;
            f[j]=(f[j]+g[j])%mod;
            if(r[i]>j) f[r[i]]=(f[r[i]]+g[j])%mod;
        }
    }
    int ans=0;
    for(int i=0;i<=n+1;i++) ans=(ans+f[i])%mod;
    return ans;
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>p[i];
    for(int i=1;i<=n;i++) cin>>q[i];

    vector<int> pos,tmp;
    for(int i=1;i<=n;i++){
        if(!q[i]) pos.push_back(i);
        else vis[q[i]]=1;
    }
    for(int i=1;i<=n;i++) if(!vis[i]) tmp.push_back(i);
    if(!pos.size()){
        cout<<Solve()<<endl;
        return 0;
    }
    int ans=0;
    do{
        for(int i=0;i<pos.size();i++) q[pos[i]]=tmp[i];
        ans=(ans+Solve())%mod;
    }while(next_permutation(pos.begin(),pos.end()));
    cout<<ans<<endl;

    return 0;
}