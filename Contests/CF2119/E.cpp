#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=2e5+9;
const int lgV=32;
const ll inf=1e18;

int p[N],q[N],n;
ll a[N],b[N],c[N],f[N][lgV],zro[N];

signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<n;i++) cin>>a[i];
        for(int i=1;i<=n;i++) cin>>b[i];

        ll ans=0;
        bool err=0;
        for(int i=1;i<=n;i++) c[i]=0;
        for(int i=1;i<n;i++) c[i]|=a[i],c[i+1]|=a[i];
        for(int i=1;i<n;i++) if((c[i]&c[i+1])!=a[i]) err=1;
        if(err){
            cout<<-1<<endl;
            continue ;
        }
        for(int i=1;i<=n;i++){
            p[i]=q[i]=0;
            while((1ll<<p[i])<=c[i]) p[i]++;
            ll mod=1ll<<p[i];
            ll tmp=(c[i]-(b[i]&mod-1)+mod)%mod;
            ans+=tmp;
            b[i]+=tmp;
            while((1ll<<q[i])<b[i]) q[i]++;
        }

        auto Status=[](int i,int j){
            return j?(j==q[i]?b[i]:((b[i]&(1<<p[i])-1)|(((b[i]>>j-1)|1)<<j-1))):b[i];
        };
        for(int i=0;i<=n;i++){
            for(int j=0;j<lgV;j++) f[i][j]=inf;
            zro[i]=inf;
        }
        zro[0]=0;
        for(int i=1;i<=n;i++){
            if(!b[i]){
                zro[i]=zro[i-1];
                for(int j=0;j<lgV;j++) zro[i]=min(zro[i],f[i-1][j]);
                for(int j=0;j<lgV;j++) f[i][j]=zro[i]+(1ll<<j);
            }else{
                for(int j=q[i];j<lgV;j++){
                    ll sta=Status(i,j),cst=sta-b[i];
                    for(int k=q[i-1];k<lgV;k++){
                        ll tta=Status(i-1,k);
                        // cout<<" -- "<<sta<<' '<<tta<<' '<<(sta&tta)<<endl;
                        if((sta&tta)!=a[i-1]) continue ;
                        f[i][j]=min(f[i][j],f[i-1][k]+cst);
                    }
                    f[i][j]=min(f[i][j],zro[i-1]+cst);
                }
            }
        }

        ll res=zro[n];
        for(int i=0;i<lgV;i++) res=min(res,f[n][i]);

        cout<<ans+res<<endl;
    }
    
    return 0;
}