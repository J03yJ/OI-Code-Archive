#include<bits/stdc++.h>

using namespace std;

#define int long long

signed main(){
    int n,m,r,k;
    cin>>n>>m>>r>>k;
    
    vector<int> p,q;
    for(int i=1;i<=n;i++) p.push_back(min(i,n-r+1)-max(1ll,i-r+1)+1);
    for(int i=1;i<=m;i++) q.push_back(min(i,m-r+1)-max(1ll,i-r+1)+1);
    sort(p.begin(),p.end());
    sort(q.begin(),q.end());

    long double ans=0;
    priority_queue<array<int,3>> pq;
    pq.push({p.back()*q.back(),n-1,m-1});
    map<pair<int,int>,int> mp;
    mp[{n-1,m-1}]=1;
    while(pq.size()&&k--){
        auto t=pq.top();
        pq.pop();
        ans+=t[0];
        int i=t[1],j=t[2];
        // cout<<i<<' '<<j<<' '<<p[i]<<' '<<q[j]<<' '<<t[0]<<endl;
        if(i&&!mp[{i-1,j}]) pq.push({p[i-1]*q[j],i-1,j}),mp[{i-1,j}]=1;
        if(j&&!mp[{i,j-1}]) pq.push({p[i]*q[j-1],i,j-1}),mp[{i,j-1}]=1;
    }
    ans/=(n-r+1);
    ans/=(m-r+1);
    // cout<<(n-r+1)<<' '<<(m-r+1)<<endl;
    
    cout<<fixed<<setprecision(10)<<ans<<endl;

    return 0;
}