#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=2e5+9;
const int K=60;

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n;ll lim;
        cin>>n>>lim;
        vector<ll> v[K+1];
        for(int i=1;i<=n;i++){
            int k,val;
            cin>>k>>val;
            v[k].push_back(val);
        }

        ll ans=0;
        for(int i=0;i<K;i++){
            v[i].push_back(0);
            sort(v[i].begin(),v[i].end());
            if((lim>>i&1)&&v[i].size()) ans+=v[i].back(),v[i].pop_back();
            while(v[i].size()>1){
                ll sum=v[i].back();
                v[i].pop_back();
                sum+=v[i].back();
                v[i].pop_back();
                v[i+1].push_back(sum);
            }
        }

        cout<<ans<<endl;
    }

    return 0;
}