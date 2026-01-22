#include<bits/stdc++.h>

using namespace std;

#define fir(x) x.first
#define sec(x) x.second
using ll=long long;

signed main(){
    int n,t;
    cin>>n>>t;

    vector<int> a(n);
    for(int &x:a) cin>>x,x%=t;
    sort(a.begin(),a.end());

    ll ans=1e18;
    deque<ll> q(a.begin(),a.end());
    for(int o=0;o<a.size();o++){
        ans=min(ans,q.back()-q.front()+1>>1);
        q.push_back(q.front()+t);
        q.pop_front();
    }

    cout<<ans<<endl;

    return 0;
}