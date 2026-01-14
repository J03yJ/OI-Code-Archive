#include<bits/stdc++.h>

using namespace std;

#define int long long

int dis(pair<int,int> a,pair<int,int> b){
    return (a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second);
}

signed main(){
    pair<int,int> a[3];
    for(int i:{0,1,2}) cin>>a[i].first>>a[i].second;
    int d[3];
    for(int i:{0,1,2}) d[i]=dis(a[i],a[(i+1)%3]);
    sort(d+0,d+3);
    if(d[0]+d[1]==d[2]) cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
}