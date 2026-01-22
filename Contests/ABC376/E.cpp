#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;

pair<int,int> a[N];
int n,k;

signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n>>k;
        for(int i=1;i<=n;i++) cin>>a[i].first;
        for(int i=1;i<=n;i++) cin>>a[i].second;
        sort(a+1,a+n+1);

        int ans=1e18,sum=0;
        priority_queue<int> q;
        for(int i=1;i<=n;i++){
            if(q.size()==k-1) ans=min(ans,a[i].first*(sum+a[i].second));
            // cout<<a[i].first<<' '<<sum+a[i].second<<endl;
            q.push(a[i].second),sum+=a[i].second;
            if(q.size()>k-1) sum-=q.top(),q.pop();
        }
        cout<<ans<<endl;
    }

    return 0;
}