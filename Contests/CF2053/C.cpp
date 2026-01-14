#include<bits/stdc++.h>

using namespace std;

#define int long long

pair<int,int> F(int n,int k){
    if(n<k) return {0,0};
    int mid=n+1>>1;
    auto ans=F(n>>1,k);
    if(n&1) return {ans.first*2+(ans.second+1)*mid,ans.second*2+1};
    else return {ans.first*2+ans.second*mid,ans.second*2};
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n,k;
        cin>>n>>k;
        cout<<F(n,k).first<<endl;
    }

    return 0;
}