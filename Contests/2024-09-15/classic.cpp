#include<bits/stdc++.h>

using namespace std;

ifstream fin("classic.in");
ofstream fout("classic.out");
#define cin fin
#define cout fout

#define int long long
const int N=1e7+9;
const int mod=998244353;

int pri[N],ntp[N],cnt;
void InitP(int lim){
    for(int i=2;i<=lim;i++){
        if(!ntp[i]) pri[++cnt]=i;
        for(int j=1;j<=cnt&&i*pri[j]<=lim;j++){
            ntp[i*pri[j]]=1;
            if(i%pri[j]==0) break ;
        }
    }
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

int n,k1,k2,lim1,lim2;
int Log(int n,int k){
    int cnt=0;
    while(n>=k) n/=k,cnt++;
    return cnt;
}
vector<pair<int,int>> v[64];
void InitAB(int mxlim){
    for(int lim=1;lim<=mxlim;lim++){
        vector<int> vis(lim*(k1+k2),0);
        for(int i=0;i<=lim;i++){
            for(int j=0;i+j<=lim;j++){
                int t=i*k1+j*k2;
                if(vis[t]) continue ;
                vis[t]=1;
                v[lim].push_back({i,j});
            }
        }
        sort(v[lim].begin(),v[lim].end(),
            [](pair<int,int> a,pair<int,int> b){return a.first+a.second<b.first+b.second;});
    }
}
int F(int n,int cur){
    int p=pri[cur];
    if(cur>cnt||n<p) return 1;
    int lim=Log(n,p),ans=0,pn=1,e=0;
    for(pair<int,int> pr:v[lim]){
        int i=pr.first,j=pr.second,t=i*k1+j*k2;
        while(e<i+j) pn*=p,e++;
        ans=(ans+F(n/pn,cur+1)*QPow(p,t)%mod)%mod;
    }
    return ans;
}

signed main(){
    cin>>n>>k1>>k2;
    
    InitP(n);
    if(k1>k2) swap(k1,k2);
    if(k1==2&&k2==3){
        int ans=0;
        vector<int> res(n+1,1);
        for(int i=1;i<=cnt;i++){
            for(int j=pri[i];j<=n;j+=pri[i]) res[i]=res[i]*(pri[i]+1)%mod;
        }
        for(int x:res) ans=(ans+x)%mod;
        cout<<mod<<endl;
        return 0;
    }

    InitAB(Log(n,2));
    cout<<F(n,1)<<endl;

    return 0;
}