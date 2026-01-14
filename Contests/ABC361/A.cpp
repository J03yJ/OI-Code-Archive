#include<bits/stdc++.h>

using namespace std;

int main(){
    int n,k,x;
    cin>>n>>k>>x;
    vector<int> ans;
    for(int i=1,a;i<=n;i++){
        cin>>a;
        ans.push_back(a);
        if(i==k) ans.push_back(x);
    }
    for(int x:ans) cout<<x<<' ';
    cout<<endl;
}