#include<bits/stdc++.h>

using namespace std;

#define For(i,l,r) for(int i=(l);i<=(r);i++)
#define Rof(i,r,l) for(int i=(r);i>=(l);i--)
#define Rep(i,n) for(int i=0;i<(n);i++)
#define ssiz(x) (signed)x.size()
#define allc(x) x.begin(),x.end()
#define fir(x) x.first
#define sec(x) x.second
using ll=long long;
using ull=unsigned long long;
using pii=pair<int,int>;
template<class T1,class T2>void ChMin(T1 &x,T2 y){if(y<x) x=y;}
template<class T1,class T2>void ChMax(T1 &x,T2 y){if(y>x) x=y;}
template<class T>using svector=vector<vector<T>>;
template<class T>using cvector=vector<vector<vector<T>>>;

#define int ll
const int mod1=998244353;
const int mod2=1e9+7;
const ll inf=1e18;
int Hash(vector<int> &a,int mod,int base){
    int res=0;
    for(int x:a){
        res=1ll*res*base%mod;
        res+=x;
        if(res>=mod) res-=mod;
    }
    return res;
}
const int base=13331;
pii Hash(vector<int> &a){return {Hash(a,mod1,base),Hash(a,mod2,base)};}
vector<int> D(vector<int> &a){
    vector<int> d;
    Rep(i,ssiz(a)-1) d.push_back(a[i+1]-a[i]);
    return d;
}

ll ans;
map<pii,bool> mp;
void DFS(vector<int> &a){
    auto x=Hash(a);
    if(mp[x]) return ;
    mp[x]=1;

    ll sum=0;
    for(int x:a) sum+=x;
    ans=max(ans,sum);
    
    if(ssiz(a)==1) return ;

    vector<int> d1=D(a);
    reverse(allc(a));
    vector<int> d2=D(a);

    DFS(d1),DFS(d2);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        vector<int> a(n);
        for(int &x:a) cin>>x;

        ans=-inf;
        DFS(a);
        cout<<ans<<endl;
        mp.clear();
    }

    return 0;
}