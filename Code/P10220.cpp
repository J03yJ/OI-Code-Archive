#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=2e5+9;
const ll inf=1e18;

int a[N],n,lim;
ll w[N],m;
vector<ll> val[N],f[N];
inline vector<ll> Merge(vector<ll> &a,vector<ll> &b){
    vector<ll> res;
    for(auto it=a.begin(),jt=b.begin();it!=a.end();it++){
        while(jt!=b.end()&&*jt<*it) res.push_back(*jt),jt++;
        res.push_back(*it);
        if(it==prev(a.end())) while(jt!=b.end()) res.push_back(*jt),jt++;
    }
    return res;
}
inline void Work(int x,int l,int r){
    if(l==r){
        val[x]={a[l]},f[x]={0,inf};
        return ;
    }
    int mid=l+r>>1;
    Work(x<<1,l,mid),Work(x<<1|1,mid+1,r);
    val[x]=Merge(val[x<<1],val[x<<1|1]);
    f[x]=vector<ll>(val[x].size()+1,inf);
    for(int i=0;i<val[x].size();i++){
        int lp=lower_bound(val[x<<1].begin(),val[x<<1].end(),val[x][i])-val[x<<1].begin();
        int rp=lower_bound(val[x<<1|1].begin(),val[x<<1|1].end(),val[x][i])-val[x<<1|1].begin();
        f[x][i]=min(f[x][i],f[x<<1][lp]+min(w[x],f[x<<1|1][rp]));
    }
}
int ans[N],tot;
inline ll Solve(int x,int l,int r,ll k){
    if(l==r){
        ans[++tot]=a[l];
        return 0;
    }
    int mid=l+r>>1;
    ll v=0,res=0;
    for(int i=val[x].size()-1;~i;i--){
        if(f[x][i]<=k){
            v=val[x][i];
            break ;
        }
    }
    int lp=lower_bound(val[x<<1].begin(),val[x<<1].end(),v)-val[x<<1].begin();
    int rp=lower_bound(val[x<<1|1].begin(),val[x<<1|1].end(),v)-val[x<<1|1].begin();
    bool flag=0;
    for(ll p:val[x<<1|1]) if(p==v) flag=1;
    if(!flag){
        res+=Solve(x<<1,l,mid,k-min(w[x],f[x<<1|1][rp]));
        if(res+f[x<<1|1][rp]>k) res+=w[x];
        res+=Solve(x<<1|1,mid+1,r,k-res);
    }else{
        res+=Solve(x<<1|1,mid+1,r,k-f[x<<1][lp]);
        res+=Solve(x<<1,l,mid,k-res);
    }
    return res;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=(1<<n)-1;i++) cin>>w[i];
        for(int i=1;i<=(1<<n);i++) cin>>a[i];
        Work(1,1,(1<<n));
        Solve(1,1,(1<<n),m);
        for(int i=1;i<=tot;i++) cout<<ans[i]<<' ';cout<<endl;
        tot=0;
    }

    return 0;
}