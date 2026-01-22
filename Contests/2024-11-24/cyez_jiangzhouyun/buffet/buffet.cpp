#include<bits/stdc++.h>

using namespace std;

ifstream fin("buffet.in");
ofstream fout("buffet.out");
#define cin fin
#define cout fout

#define int long long
const int N=2e2+9;
const int K=1e3+9;
const int mod=998244353;

int f[N][K],g[N][K],a[N],n,lim;
void Add(int &x,int y){x+=y;if(x>=mod) x-=mod;}

signed main(){
    cin>>n>>lim;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);

    f[0][0]=1;
    for(int i=1;i<=n;i++){
        memset(g,0,sizeof g);
        for(int j=0;j<=i;j++){
            for(int k=0;k<=lim;k++){
                if(k+j*(a[i]-a[i-1])>lim) continue ;
                Add(g[j][k+j*(a[i]-a[i-1])],f[j][k]*(j+1)%mod);
                Add(g[j+1][k+j*(a[i]-a[i-1])],f[j][k]);
                if(j) Add(g[j-1][k+j*(a[i]-a[i-1])],f[j][k]*j%mod);
            }
        }
        memcpy(f,g,sizeof f);
    }

    int ans=0;
    for(int k=0;k<=lim;k++) Add(ans,f[0][k]);
    cout<<ans<<endl;

    return 0;
}