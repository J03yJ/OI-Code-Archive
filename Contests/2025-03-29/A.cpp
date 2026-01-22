#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

#define fir(x) (x).first
#define sec(x) (x).second
using pii=pair<int,int>;
const int N=1e6+9;

const int dx[4]={1,0,-1,0};
const int dy[4]={0,1,0,-1};
int qx[N],qy[N],lim,q;
int x[N],y[N],act[N],st[N],n;
vector<array<int,4>> e;

int fa[N],mxx[N],mnx[N],mxy[N],mny[N],siz[N],ans,cnt;
inline int Check(int x){
    int lenx=mxx[x]-mnx[x]+1;
    int leny=mxy[x]-mny[x]+1;
    return siz[x]==1ll*lenx*leny;
}
inline int Find(int x){return x==fa[x]?x:Find(fa[x]);}
inline void Merge(int x,int y,vector<array<int,7>> &rb){
    x=Find(x),y=Find(y);
    if(x==y) return ;
    if(siz[x]<siz[y]) swap(x,y);
    rb.push_back({x,fa[x],siz[x],mxx[x],mnx[x],mxy[x],mny[x]});
    rb.push_back({y,fa[y],siz[y],mxx[y],mnx[y],mxy[y],mny[y]});
    ans-=Check(x);
    ans-=Check(y);
    fa[y]=x;
    siz[x]+=siz[y];
    mxx[x]=max(mxx[x],mxx[y]);
    mnx[x]=min(mnx[x],mnx[y]);
    mxy[x]=max(mxy[x],mxy[y]);
    mny[x]=min(mny[x],mny[y]);
    ans+=Check(x);
    cnt--;
}

map<pii,int> vmp,emp;
vector<int> ve[N<<2],vv[N<<2];
inline void PushE(int x,int L,int R,int l,int r,int k){
    if(l<=L&&R<=r) return ve[x].push_back(k);
    int mid=L+R>>1;
    if(l<=mid) PushE(x<<1,L,mid,l,r,k);
    if(r>mid) PushE(x<<1|1,mid+1,R,l,r,k);
}
inline void PushV(int x,int L,int R,int l,int r,int k){
    if(l<=L&&R<=r) return vv[x].push_back(k);
    int mid=L+R>>1;
    if(l<=mid) PushV(x<<1,L,mid,l,r,k);
    if(r>mid) PushV(x<<1|1,mid+1,R,l,r,k);
}
inline void Solve(int p,int L,int R){
    vector<array<int,7>> rb;
    int tans=ans,tcnt=cnt;

    for(int u:vv[p]){
        rb.push_back({u,fa[u],siz[u],mxx[u],mnx[u],mxy[u],mny[u]});
        mxx[u]=mnx[u]=x[u];
        mxy[u]=mny[u]=y[u];
        fa[u]=u,siz[u]=1;
        ans+=Check(u);
        cnt++;
    }
    for(int i:ve[p]) Merge(e[i][2],e[i][3],rb);
    
    if(L==R){
        cout<<ans<<' '<<(ans==cnt)<<endl;
    }else{
        int mid=L+R>>1;
        Solve(p<<1,L,mid);
        Solve(p<<1|1,mid+1,R);
    }
    
    ans=tans,cnt=tcnt;
    while(rb.size()){
        int u=rb.back()[0];
        fa[u]=rb.back()[1];
        siz[u]=rb.back()[2];
        mxx[u]=rb.back()[3];
        mnx[u]=rb.back()[4];
        mxy[u]=rb.back()[5];
        mny[u]=rb.back()[6];
        rb.pop_back();
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>lim>>q;
    for(int i=1;i<=q;i++) cin>>qx[i]>>qy[i];

    for(int i=1;i<=q;i++){
        if(!vmp[{qx[i],qy[i]}]){
            vmp[{qx[i],qy[i]}]=++n;
            x[n]=qx[i],y[n]=qy[i];
        }
    }
    for(int i=1;i<=q;i++){
        int u=vmp[{qx[i],qy[i]}];
        act[u]^=1;
        if(act[u]) st[u]=i;
        else PushV(1,1,q,st[u],i-1,u);
        for(int k:{0,1,2,3}){
            int v=vmp[{x[u]+dx[k],y[u]+dy[k]}];
            if(!v) continue ;
            if(act[u]&&act[v]) emp[{u,v}]=emp[{v,u}]=i;
            if(!act[u]&&act[v]){
                int j=emp[{u,v}];
                emp[{u,v}]=emp[{v,u}]=0;
                e.push_back({j,i-1,u,v});
            }
        }
    }
    for(int i=1;i<=n;i++) if(act[i]) PushV(1,1,q,st[i],q,i);
    for(auto t:emp){
        int u=fir(fir(t)),v=sec(fir(t)),st=sec(t);
        if(u>v) continue ;
        if(!st) continue ;
        e.push_back({st,q,u,v});
    }

    for(int i=1;i<=n;i++) act[i]=0;
    for(int i=0;i<e.size();i++) PushE(1,1,q,e[i][0],e[i][1],i);
    Solve(1,1,q);

    return 0;
}