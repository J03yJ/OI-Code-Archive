#include<bits/stdc++.h>

using namespace std;

signed main(){
    int n;
    cin>>n;
    vector<string> s(n);
    for(string &t:s) cin>>t;

    sort(s.begin(),s.end(),[](auto x,auto y){return x.size()<y.size();});
    for(string &t:s) cout<<t;cout<<endl;

    return 0;
}