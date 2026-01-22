#include<bits/stdc++.h>

using namespace std;

ifstream fin("math.in");
ofstream fout("math.out");
#define cin fin
#define cout fout

#define int long long
const int N=1e3+9;
const int P=10;
const int p[P]={2,3,5,7,11,13,17,19,23,29};

int pri[N],ntp[N],mfp[N],mpow[N],pcnt;
int f[N][1<<P],g[N][1<<P],sum[N],T,m,mod;
vector<int> t[N];
void Init(int lim){
    for(int i=2;i<=lim;i++){
        if(!ntp[i]) pri[++pcnt]=i,mfp[i]=pcnt;
        for(int j=1;j<=pcnt&&pri[j]*i<=lim;j++){
            ntp[i*pri[j]]=1;
            mfp[i*pri[j]]=mfp[i];
            if(i%pri[j]==0) break ;
        }
    }
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

signed main(){
    cin>>T>>m>>mod;

    Init(m);
    for(int i=2;i<=m;i++) t[mfp[i]].push_back(i);
    f[0][0]=1;
    for(int i=1;i<=pcnt;i++){
        memcpy(g,f,sizeof f);
        for(int x:t[i]){
            int tta=0;
            for(int j=0;j<P;j++) if(x%p[j]==0) tta|=1<<j;
            for(int j=0;j<=pcnt;j++){
                for(int sta=0;sta<(1<<P);sta++){
                    if(sta&tta) continue ;
                    g[j+1][sta|tta]=(g[j+1][sta|tta]+f[j][sta]*(m/x)%mod)%mod;
                }
            }
        }
        memcpy(f,g,sizeof f);
    }
    for(int i=0;i<=pcnt;i++){
        for(int sta=0;sta<(1<<P);sta++){
            sum[i]=(sum[i]+f[i][sta])%mod;
        }
    }

    while(T--){
        int n;
        cin>>n;
        
        int ans=0,lim=min(pcnt,n);
        mpow[lim]=QPow(m,n-lim);
        for(int i=lim-1;~i;i--) mpow[i]=mpow[i+1]*m%mod;
        for(int i=0,tmp=1;i<=lim;i++,tmp=(n-i+1)%mod*tmp%mod){
            ans=(ans+sum[i]*tmp%mod*mpow[i]%mod)%mod;
        }
        cout<<ans<<endl;
    }

    return 0;
}