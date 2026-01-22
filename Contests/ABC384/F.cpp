#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>

using namespace std;

#define int long long
const int N=2e5+9;
const int lgV=25;

int a[N],n,ans;
__gnu_pbds::gp_hash_table<int,int> sum[lgV],cnt[lgV];
#define mask(k) ((1<<k+1)-1)

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    for(int i=1;i<=n;i++){
        for(int k=0;k<lgV;k++){
            int tmp=a[i]&mask(k);
            sum[k][tmp]+=a[i];
            cnt[k][tmp]++;
            int tmq=((1<<k)-tmp)&mask(k);
            ans+=(sum[k][tmq]+cnt[k][tmq]*a[i])>>k;
        }
    }
    cout<<ans<<endl;

    return 0;
}