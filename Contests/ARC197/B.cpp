#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;

int a[N],n;
ll sum[N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];

        sort(a+1,a+n+1);
        for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];

        int ans=0;
        for(int i=1;i<=n;i++){
            int pos=upper_bound(a+1,a+i+1,sum[i]/i)-a;
            ans=max(ans,i-pos+1);
        }

        cout<<ans<<endl;
    }

    return 0;
}