#include<bits/stdc++.h>

using namespace std;

const int N=1e3+9;

int a[N],ra[N];

int main(){
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i],ra[a[i]]=i;
    vector<pair<int,int>> ans;
    map<pair<int,int>,bool> mp;
    while(true){
        int l=0,r=0,c=n+1;
        // for(int i=1;i<=n;i++){
        //     for(int j=i+k;j<=n;j++){
        //         if(a[i]<a[j]) continue ;
        //         if(a[i]-a[j]<c||a[i]<a[l]&&a[i]-a[j]==c) l=i,r=j,c=a[i]-a[j];
        //     }
        // }
        for(int val=1;val<=n;val++){
            for(int i=1;i<=n;i++){
                if(a[i]<=val) continue ;
                int j=ra[a[i]-val];
                if(j<i+k) continue ;
                if(a[i]-a[j]<c||a[i]<a[l]&&a[i]-a[j]==c) l=i,r=j,c=a[i]-a[j];
            }
            if(l) break ;
        }
        if(!l) break ;
        ans.push_back({l,r});
        swap(a[l],a[r]);
        ra[a[l]]=l;ra[a[r]]=r;
    }
    cout<<ans.size()<<endl;
    for(pair<int,int> x:ans) cout<<x.first<<' '<<x.second<<endl;
    return 0;
}