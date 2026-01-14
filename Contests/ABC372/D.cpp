#include<bits/stdc++.h>

using namespace std;

int main(){
    int n;
    cin>>n;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    
    vector<int> ans,stk;
    for(int i=n;i>=1;i--){
        ans.push_back(stk.size());
        while(stk.size()&&a[i]>stk.back()) stk.pop_back();
        stk.push_back(a[i]);
    }
    reverse(ans.begin(),ans.end());
    for(int x:ans) cout<<x<<' ';cout<<endl;

    return 0;
}