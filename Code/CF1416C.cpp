#include<bits/stdc++.h>

using namespace std;

#define int long long
#define ssiz(x) (signed)x.size()
const int N=3e5+9;
const int lgN=30;

int a[N],f[lgN][2],n;
void Solve(int k,vector<pair<int,int>> &v){
    if(ssiz(v)<2) return ;
    if(k<0) return ;

    vector<pair<int,int>> p,q;
    // cout<<"# "<<k<<" : "<<endl;
    for(auto t:v){
        if(t.second>>k&1) p.push_back(t);
        else q.push_back(t);
    }
    // for(auto t:p) cout<<t.first<<'/'<<t.second<<' ';cout<<endl;
    // for(auto t:q) cout<<t.first<<'/'<<t.second<<' ';cout<<endl;

    int res0=0,res1=0;
    for(int i=0,j=0;i<ssiz(p);i++){
        while(j<ssiz(q)&&p[i].first>=q[j].first) j++;
        res0+=ssiz(q)-j;
        // cout<<i<<' '<<j<<endl;
    }
    for(int i=0,j=0;i<ssiz(q);i++){
        while(j<ssiz(p)&&q[i].first>=p[j].first) j++;
        res1+=ssiz(p)-j;
        // cout<<i<<' '<<j<<endl;
    }
    // cout<<res0<<' '<<res1<<endl;
    f[k][0]+=res0;
    f[k][1]+=res1;

    Solve(k-1,p),Solve(k-1,q);
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    vector<pair<int,int>> tmp;
    for(int i=1;i<=n;i++) tmp.push_back({i,a[i]});
    Solve(lgN-1,tmp);

    int x=0,ans=0;
    for(int i=0;i<lgN;i++){
        if(f[i][1]<f[i][0]) x|=1<<i,ans+=f[i][1];
        else ans+=f[i][0];
    }
    cout<<ans<<' '<<x<<endl;

    return 0;
}