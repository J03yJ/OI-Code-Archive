#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e6+9;

int a[N],buc[N];

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        
        int ans=0;
        for(int i=1;i<=n;i++) ans+=a[i];
        vector<pair<pair<int,int>,int>> u,v;
        int mx=0,pos=0,res=0;
        for(int i=1;i<=n;i++){
            buc[a[i]]++;
            if(buc[a[i]]>1){
                if(a[i]>mx){
                    if(mx) u.push_back({make_pair(pos,i-1),mx});
                    mx=a[i];pos=i;
                }
            }
        }
        for(int i=1;i<=n;i++) buc[a[i]]--;
        if(mx) u.push_back({make_pair(pos,n),mx});
        for(pair<pair<int,int>,int> x:u) res+=(x.first.second-x.first.first+1)*x.second;
        ans+=res;
        for(pair<pair<int,int>,int> x:u){
            if(x.first.second==x.first.first){
                if(v.size()) v.back().first.second=x.first.second;
            }else v.push_back(x);
        }
        u=v;
        if(u.size()){
            u.back().first.second--;
            if(u.back().first.second<u.back().first.first) u.pop_back();
            res=0;
            for(pair<pair<int,int>,int> x:u) res+=(x.first.second-x.first.first+1)*x.second;
            ans+=res;
            while(u.size()){
                u.back().first.second--;
                res-=u.back().second;
                if(u.back().first.second<u.back().first.first) u.pop_back();
                ans+=res;
            }
        }

        cout<<ans<<endl;
    }
    return 0;
}