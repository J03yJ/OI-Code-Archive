#include<bits/stdc++.h>

using namespace std;

#define int long long

signed main(){
    pair<int,int> s,t;
    cin>>s.first>>s.second>>t.first>>t.second;
    if((s.first+s.second)%2) s.first--;
    s.first+=s.second;
    s.first/=2;
    if((t.first+t.second)%2) t.first--;
    t.first+=t.second;
    t.first/=2;

    if(s.first>t.first) swap(s,t);
    int dx=t.first-s.first,dy=t.second-s.second;
    int k=max(0ll,min(dx,dy));
    cout<<abs(dx-k)+abs(dy-k)+k<<endl;
}