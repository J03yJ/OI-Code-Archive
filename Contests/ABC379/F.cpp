#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;
int a[N],ans[N],n,q;
vector<pair<int,int>> qy[N];


int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1,l,r;i<=q;i++){
        cin>>l>>r;
        qy[l].push_back({r,i});
    }

    vector<int> stk;
    for(int i=n;i>=1;i--){
        for(auto p:qy[i]){
            ans[p.second]=lower_bound(stk.begin(),stk.end(),p.first,greater<int>())-stk.begin();
        }
        while(stk.size()&&a[stk.back()]<a[i]) stk.pop_back();
        stk.push_back(i);
    }

    for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

    return 0;
}