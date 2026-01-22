#include<bits/stdc++.h>

using namespace std;

ifstream fin("cupcake.in");
ofstream fout("cupcake.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e5+9;

int a[N],b[N],n,q,Tid;
int mu[N],ntp[N],pri[N],pcnt;
inline void InitMu(int lim){
    mu[1]=1;
    for(int i=2;i<=lim;i++){
        if(!ntp[i]) pri[++pcnt]=i,mu[i]=-1;
        for(int j=1;j<=pcnt&&i*pri[j]<=lim;j++){
            ntp[i*pri[j]]=1;
            if(i%pri[j]) mu[i*pri[j]]=-mu[i];
            else{
                mu[i*pri[j]]=0;
                break ;
            }
        }
    }
}
int f[N],g[N],p[N],tot;
ll pre[N],suf[N];

signed main(){
    cin>>Tid>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];

    ll sum=0;
    InitMu(n);
    for(int i=2;i<=n;i++){
        f[i]=a[i]-b[i],g[i]-=f[i];
        if(mu[i]) p[++tot]=g[i]*mu[i];
        else sum+=abs(g[i]);
        for(int j=i+i;j<=n;j+=i) g[j]-=mu[j/i]*f[i];
    }
    sort(p+1,p+tot+1);
    for(int i=1;i<=tot;i++) pre[i]=pre[i-1]+p[i];
    for(int i=tot;i>=1;i--) suf[i]=suf[i+1]+p[i];
    
    cin>>q;
    while(q--){
        cin>>b[1];
        f[1]=a[1]-b[1],g[1]=-f[1];
        ll res=sum+abs(g[1]);
        int pos=upper_bound(p+1,p+tot+1,f[1])-p-1;
        res+=1ll*pos*f[1]-pre[pos];
        res+=suf[pos+1]-1ll*(tot-pos)*f[1];
        cout<<res<<endl;
    }

    return 0;
}