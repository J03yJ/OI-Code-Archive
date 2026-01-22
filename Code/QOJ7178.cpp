#include<bits/stdc++.h>

using namespace std;

int main(){
    int n,m;
    cin>>n>>m;

    int flag=0;
    if(n>m) swap(n,m),flag=1;
    vector<pair<int,int>> res;
    
    if(n==m){
        for(int i=1;i<=n;i++) res.push_back({i,1});
        for(int i=2;i<n;i++) res.push_back({i,n});
    }else{
        for(int i=1;i<=n;i++) res.push_back({i,1}),res.push_back({i,m});
        if(n%2){
            int k=n+1>>1;
            for(int i=1+k;i<=m-k;i++) res.push_back({k,i});
        }else{
            int k=(n>>1)+1;
            for(int i=1+k;i<=m-k;i+=2) res.push_back({k-1,i}),res.push_back({k,i});
        }
    }

    cout<<res.size()<<endl;
    for(pair<int,int> p:res){
        if(!flag) cout<<p.first<<' '<<p.second<<endl;
        else cout<<p.second<<' '<<p.first<<endl;
    }

    return 0;
}