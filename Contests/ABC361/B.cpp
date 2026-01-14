#include<bits/stdc++.h>

using namespace std;

bool check(pair<int,int> x,pair<int,int> y){
    if(x.first>y.first) swap(x,y);
    if(x.first<=y.first&&y.first<x.second) return 1;
    else return 0;
}

int main(){
    pair<int,int> a[4],b[4];
    for(int i=1;i<=3;i++) cin>>a[i].first;
    for(int i=1;i<=3;i++) cin>>a[i].second;
    for(int i=1;i<=3;i++) cin>>b[i].first;
    for(int i=1;i<=3;i++) cin>>b[i].second;

    if(check(a[1],b[1])&&check(a[2],b[2])&&check(a[3],b[3])) cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
}