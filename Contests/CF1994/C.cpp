#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e6+9;

int a[N],sum[N],f[N],g[N];

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n,x;
        cin>>n>>x;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];

        int ans=0;
        for(int i=0;i<=n;i++) g[i]=1;
        for(int i=1;i<=n;i++){
            int l=i-1,r=n+1;
            while(l+1<r){
                int mid=l+r>>1;
                if(sum[mid]-sum[i-1]<=x) l=mid;
                else r=mid;
            }
            f[i]=(r-i)*g[i-1];
            g[r]+=g[i-1];
            ans+=f[i];
        }

        cout<<ans<<endl;

        for(int i=0;i<=n+1;i++) f[i]=g[i]=0;
    }
}