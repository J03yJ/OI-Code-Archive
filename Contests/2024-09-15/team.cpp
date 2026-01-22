#include<bits/stdc++.h>

using namespace std;

ifstream fin("team.in");
ofstream fout("team.out");
#define cin fin
#define cout fout

#define int long long
const int N=5e2+9;
const int mod=998244353;

int fa[N],vis[N],p[N],d[N],n;
bool Check(){
    for(int i=1;i<=n;i++) if(fa[i]!=i%n+1) return 0;
    return 1;
}
int QPow(int x,int y,int m=mod){
    int res=1;
    while(y){
        if(y&1) res=res*x%m;
        x=x*x%m;
        y>>=1;
    }
    return res;
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>fa[i];
    
    int fac=1;
    for(int i=1;i<=n;i++) fac=fac*QPow(i,mod-2)%mod;

    if(Check()){
        d[2]=1;
        for(int i=3;i<=n;i++){
            d[i]=(d[i-1]+d[i-2])*(i-1);
        }
        cout<<d[n]*fac%mod*n%mod<<endl;
        return 0;
    }

    int ans=0;
    for(int i=1;i<=n;i++) p[i]=i;
    do{
        int cnt=0;
        for(int i=1;i<=n;i++) vis[i]=0;
        for(int i=1;i<=n;i++){
            if(vis[p[i]]==1) continue ;
            if(vis[fa[p[i]]]==-1||fa[fa[p[i]]]==p[i]){
                vis[fa[p[i]]]=vis[p[i]]=1;
                cnt++;
            }else vis[p[i]]=-1;
        }
        ans+=cnt;
    }while(next_permutation(p+1,p+n+1));

    
    cout<<ans*fac%mod<<endl;

    return 0;
}