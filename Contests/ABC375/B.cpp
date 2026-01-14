#include<bits/stdc++.h>

using namespace std;

int main(){
    vector<pair<int,int>> p(1,{0,0});
    int n;
    cin>>n;
    for(int i=1,x,y;i<=n;i++){
        cin>>x>>y;
        p.push_back({x,y});
    }
    p.push_back({0,0});

    double ans=0;
    #define dis(a,b,c,d) sqrt(1ll*(a-c)*(a-c)+1ll*(b-d)*(b-d))
    for(int i=0;i<=n;i++){
        ans+=dis(p[i].first,p[i].second,p[i+1].first,p[i+1].second);
    }
    cout<<fixed<<setprecision(8)<<ans<<endl;

    return 0;
}