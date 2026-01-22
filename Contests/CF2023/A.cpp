#include<bits/stdc++.h>

using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        vector<pair<int,int>> a(n);
        for(auto &p:a) cin>>p.first>>p.second;
        sort(a.begin(),a.end(),[](pair<int,int> x,pair<int,int> y){
            if(x.second<x.first) swap(x.second,x.first);
            if(y.second<y.first) swap(y.second,y.first);
            return x<y;
        });
        for(auto p:a) cout<<p.first<<' '<<p.second<<' ';cout<<endl;
    }
}