#include<bits/stdc++.h>

using namespace std;

ifstream fin("bridge.in");
ofstream fout("bridge.out");
#define cin fin
#define cout fout

using ll=long long;
const ll inf=0x3f3f3f3f3f3f3f3f;
template<class T1,class T2> inline void ChMin(T1 &x,T2 y){if(y<x) x=y;}

const int N=1e4+9;

int a[N],n,c;
ll _f[N][N],*f[N],g[N],sum[N];

signed main(){
    cin>>n>>c;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    ChMin(c,n);

    if(c==n){
        cout<<a[n]<<endl;
        return 0;
    }

    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
    int b=n/c+1;
    for(int i=0;i<=n;i++) f[i]=_f[i]+b;
    
    memset(_f,0x3f,sizeof _f);
    f[0][0]=0;
    for(int i=0;i<=n;i++){
        for(int j=-b;j<=b;j++){
            if(f[i][j]==inf) continue ;
            for(int k=i+1;k<=min(n,i+c);k++){
                int len=min(n,i+c)-k;
                ChMin(f[k][j+len-1],f[i][j]+sum[len]+a[n-i]);
            }
        }
    }
    memset(g,0x3f,sizeof g);
    g[0]=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=min(i+1,c);j++) ChMin(g[i],g[i-j+1]+sum[j]+a[j]);
    }
    
    ll ans=inf;
    for(int i=0;i<b;i++) ChMin(ans,f[n][-i-1]+g[i]);
    cout<<ans<<endl;

    return 0;
}