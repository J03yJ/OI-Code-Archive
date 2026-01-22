#include<bits/stdc++.h>

using namespace std;

#define fir(x) x.first
#define sec(x) x.second
using pii=pair<int,int>;
const int N=1e5+9;
using ll=long long;

int n,m1,m2;
vector<pii> b;

vector<pii> Break(int x){
    vector<pii> v;
    for(int i=2;i*i<=x;i++){
        if(x%i) continue ;
        v.push_back({i,0});
        while(x%i==0) x/=i,sec(v.back())++;
    }
    if(x!=1) v.push_back({x,1});
    sort(v.begin(),v.end());
    return v;
}

ll ans,cnt;
unordered_map<ll,ll> vis;
inline void Calc(int p,ll x,ll y,ll lst){
    if(p==b.size()){
        ll& z=vis[x*y];
        if(!z) cnt++,z=y,ans^=y;
        else if(y<z) ans^=y^z,z=y;
        cout<<y<<" : "<<x*y<<endl;
        return ;
    }
    for(int i=0;i<=sec(b[p]);i++,x*=fir(b[p])){
        if(x>n) break ;
        if(x!=1&&x*lst<=n){
            cout<<y<<" : "<<x<<'/'<<lst<<' '<<fir(b[p])<<endl;
            continue ;
        }
        Calc(p+1,x,y,lst);
    }
}
inline void DFS(int p,ll x,ll lst){
    if(p==b.size()){
        cout<<x<<" : "<<endl;
        return Calc(0,1,x,lst),cout<<endl,void();
    }
    for(int i=0;i<=sec(b[p]);i++,x*=fir(b[p])){
        if(x>n) break ;
        sec(b[p])-=i;
        DFS(p+1,x,i?fir(b[p]):lst);
        sec(b[p])+=i;
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    int T;
    cin>>T;
    while(T--){
        cin>>n>>m1>>m2;
        
        auto b1=Break(m1);
        auto b2=Break(m2);
        
        b.clear();
        while(b1.size()&&b2.size()){
            if(fir(b1.back())==fir(b2.back())){
                b.push_back({fir(b1.back()),sec(b1.back())+sec(b2.back())});
                b1.pop_back(),b2.pop_back();
            }else if(fir(b1.back())>fir(b2.back())){
                b.push_back(b1.back());
                b1.pop_back();
            }else{
                b.push_back(b2.back());
                b2.pop_back();
            }
        }
        b.insert(b.end(),b1.begin(),b1.end());
        b.insert(b.end(),b2.begin(),b2.end());
        sort(b.begin(),b.end(),greater<pii>());
        
        vis.clear();
        DFS(0,1,1);
        cout<<cnt<<' '<<ans<<endl;
        cnt=ans=0;
    }

    return 0;
}