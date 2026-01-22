#include<bits/stdc++.h>

using namespace std;

int main(){
    int n,q;
    cin>>n;
    vector<pair<int,int>> a(n);
    for(int i=0;i<n;i++){
        cin>>a[i].first>>a[i].second;
    }
    cin>>q;
    for(int i=0;i<q;i++){
        int x,y;
        cin>>x>>y;
        x--;
        y-=a[x].second;
        y=(y+a[x].first-1)/a[x].first*a[x].first;
        y+=a[x].second;
        cout<<y<<endl;
    }

    return 0;
}