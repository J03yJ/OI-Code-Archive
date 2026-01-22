#include<bits/stdc++.h>

using namespace std;

ifstream fin("square.in");
ofstream fout("square.out");
#define cin fin
#define cout fout
#define endl '\n'

#define fir(x) x.first
#define sec(x) x.second
using ll=long long;
using pii=pair<ll,int>;
const int N=1e5+9;
const int inf=1e9;

int x[N],y[N],c[N],n;
inline ll Ans(int i,int j,int k){
    ll xtmp=max({x[i],x[j],x[k]})-min({x[i],x[j],x[k]});
    ll ytmp=max({y[i],y[j],y[k]})-min({y[i],y[j],y[k]});
    return xtmp+ytmp<<1;
}
inline ll Brute(vector<int> pos){
    vector<int> p[3];
    ll ans=1e18;
    for(int i:pos) p[c[i]].push_back(i);
    for(int i:p[0]) for(int j:p[1]) for(int k:p[2]) ans=min(ans,Ans(i,j,k));
    return ans;
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>x[i]>>y[i]>>c[i];

    vector<int> tmp(n);
    iota(tmp.begin(),tmp.end(),1);
    sort(tmp.begin(),tmp.end(),[](int i,int j){return x[i]+y[i]<x[j]+y[j];});

    ll ans=1e18;
    for(int i=0;i<tmp.size();i++){
        if(i+200<tmp.size()) ans=min(ans,Brute(vector<int>(i+tmp.begin(),i+200+tmp.begin())));
        else ans=min(ans,Brute(vector<int>(i+tmp.begin(),tmp.end())));
    }

    cout<<ans<<endl;

    return 0;
}