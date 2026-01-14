#include<bits/stdc++.h>

using namespace std;

#define int long long

signed main(){
    int T;
    cin>>T;
    while(T--){
        int x;
        cin>>x;
        vector<int> ans;
        int k=x;
        ans.push_back(x);
        while(k){
            int p=k&-k;
            ans.push_back(x^p);
            k-=p;
        }
        if(!ans.back()) ans.pop_back();
        reverse(ans.begin(),ans.end());
        cout<<ans.size()<<endl;
        for(int a:ans) cout<<a<<' ';cout<<endl;
    }
}