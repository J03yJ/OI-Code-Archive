#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define all(x) x.begin(),x.end()
#define pb push_back
#define mkp make_pair
#define dbg cerr<<"LINE "<<__LINE__<<":"
using namespace std;
typedef long long ll; const ll linf=1e18;
constexpr int N=1000009,inf=1e9,mod=998244353;

inline ll H(int a,int b,int c,int d,int e,int f){
	return f*312500000ll+e*6250000ll+d*125000ll+c*2500ll+b*50ll+a;
}
int n,x,y,k,m;
__gnu_pbds::gp_hash_table<ll,int> mp;
int dfs(int u,int xa,int ya,int xb,int yb,int inv){
    if(u==n){
        if(xa==x&&xb==y&&inv==k) return 1;
        else return 0;
    }
    if(xa>x||xb>y||inv>k) return 0;
    if(inv+(u+n)*(n-u+1)<k) return 0;
    if(xa+xb+(n-u)<x+y) return 0;
    if(mp.find(H(u,xa,ya,xb,yb,inv))!=mp.end()) return mp[H(u,xa,ya,xb,yb,inv)];
    ll ans=0;
    ans+=dfs(u+1,xa+1,ya,xb,yb+1,inv+u-xa+u-xb-yb);
    ans+=dfs(u+1,xa+1,ya,xb,yb,inv+xa+xa+xb+ya+yb);
    ans+=dfs(u+1,xa,ya+1,xb+1,yb,inv+u-xa-ya+u-xb);
    ans+=dfs(u+1,xa,ya+1,xb,yb,inv+u-ya+xb);
    ans+=dfs(u+1,xa,ya,xb+1,yb,inv+xa+ya+yb);
    ans+=dfs(u+1,xa,ya,xb,yb+1,inv+u-yb+xa);
	ans%=mod;
    return mp[H(u,xa,ya,xb,yb,inv)]=ans;
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>n>>x>>y>>k>>m;
    cout<<dfs(0,0,0,0,0,0)<<"\n";
    return 0;
}