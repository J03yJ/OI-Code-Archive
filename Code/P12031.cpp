#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;
const int inf=1e9+7;

struct Node{
    int l,r,dat;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat

inline void PushUp(int x){dat(x)=min(dat(x<<1),dat(x<<1|1));}
inline void Build(int x,int l,int r){
    l(x)=l,r(x)=r,dat(x)=inf;
    if(l(x)==r(x)) return ;
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
    PushUp(x);
}
inline void Modify(int x,int pos,int k){
    if(l(x)==r(x)) return dat(x)=k,void();
    int mid=l(x)+r(x)>>1;
    if(pos<=mid) Modify(x<<1,pos,k);
    else Modify(x<<1|1,pos,k);
    PushUp(x);
}
inline int Query(int x,int l,int r){
    if(l>r) return inf;
    if(l<=l(x)&&r(x)<=r) return dat(x);
    int mid=l(x)+r(x)>>1;
    if(l<=mid&&r>mid) return min(Query(x<<1,l,mid),Query(x<<1|1,mid+1,r));
    else if(r<=mid) return Query(x<<1,l,r);
    else return Query(x<<1|1,l,r);
}

int lx[N],ly[N],rx[N],ry[N],n;
map<int,int> mp;
inline void Work(int x,vector<int> &v,vector<int> &vis){
    if(vis[x]) return ;
    while(true){
        int miny=min(Query(1,1,lx[x]-1),Query(1,lx[x]+1,rx[x]));
        if(miny>ry[x]) break ;
        Work(mp[miny],v,vis);
    }
    Modify(1,lx[x],inf);
    v.push_back(x);
    vis[x]=1;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    int T,m;
    cin>>T>>m;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>lx[i]>>ly[i]>>rx[i]>>ry[i];
        
        Build(1,1,n<<1);
        for(int i=1;i<=n;i++) Modify(1,lx[i],ly[i]);
        for(int i=1;i<=n;i++) mp[ly[i]]=i;
        if(m==1){
            vector<int> ans,vis(n+1,0);
            ans.reserve(n);
            for(int i=1;i<=n;i++) if(!vis[i]) Work(i,ans,vis);
            for(int x:ans) cout<<x<<' ';cout<<endl;
        }else{
            for(int i=1;i<=n;i++){
                int miny=min(Query(1,1,lx[i]-1),Query(1,lx[i]+1,rx[i]));
                cout<<(miny>ry[i]);
                Modify(1,lx[i],inf);
            }
            cout<<endl;
        }
        mp.clear();
    }

    return 0;
}