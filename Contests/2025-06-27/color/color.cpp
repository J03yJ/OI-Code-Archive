#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#include<bits/stdc++.h>

using namespace std;

ifstream fin("color.in");
ofstream fout("color.out");
#define cin fin
#define cout fout
#define endl '\n'

#define fir(x) (x).first
#define sec(x) (x).second
using pii=pair<int,int>;
using ll=long long;
const int inf=1e9+7;
const int N=5e5+9;
const int SR=7e2+9;
const int lgN=2e1;

int a[N],n,tid,B;
int ql[N],qr[N],q;
ll ans[N];

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}
int fa[N],siz[N],dep[N],hson[N];
inline void DFS1(int x){
    siz[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x;
        dep[y]=dep[x]+1;
        DFS1(y);
        siz[x]+=siz[y];
        if(!hson[x]||siz[y]>siz[hson[x]]) hson[x]=y;
    }
}
int dfn[N],top[N],dcnt;
inline void DFS2(int x,int t){
    top[x]=t;
    dfn[x]=++dcnt;
    if(hson[x]) DFS2(hson[x],t);
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        if(y==hson[x]) continue ;
        DFS2(y,y);
    }
}
int pmx[N][lgN],pmn[N][lgN],lg[N<<1];
inline void InitPathRMQ(){
    for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
    for(int i=1;i<=n;i++) pmx[dfn[i]][0]=pmn[dfn[i]][0]=i;
    for(int k=1;k<=lg[n];k++){
        for(int i=1;i<=n-(1<<k)+1;i++){
            pmx[i][k]=max(pmx[i][k-1],pmx[i+(1<<k-1)][k-1]);
            pmn[i][k]=min(pmn[i][k-1],pmn[i+(1<<k-1)][k-1]);
        }
    }
}
inline int _PathMax(int l,int r){int k=lg[r-l+1];return max(pmx[l][k],pmx[r-(1<<k)+1][k]);}
inline int _PathMin(int l,int r){int k=lg[r-l+1];return min(pmn[l][k],pmn[r-(1<<k)+1][k]);}
inline int PathMax(int x,int y){
    int ans=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<=dep[top[y]]) swap(x,y);
        ans=max(ans,_PathMax(dfn[top[x]],dfn[x]));
        x=fa[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    return max(ans,_PathMax(dfn[x],dfn[y]));
}
inline int PathMin(int x,int y){
    int ans=inf;
    while(top[x]!=top[y]){
        if(dep[top[x]]<=dep[top[y]]) swap(x,y);
        ans=min(ans,_PathMin(dfn[top[x]],dfn[x]));
        x=fa[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    return min(ans,_PathMin(dfn[x],dfn[y]));
}
int mx[N][lgN],mn[N][lgN];
inline void InitRMQ(){
    for(int i=1;i<n;i++) mx[i][0]=PathMax(i,i+1),mn[i][0]=PathMin(i,i+1);
    for(int k=1;k<=lg[n];k++){
        for(int i=1;i<=n-(1<<k);i++){
            mx[i][k]=max(mx[i][k-1],mx[i+(1<<k-1)][k-1]);
            mn[i][k]=min(mn[i][k-1],mn[i+(1<<k-1)][k-1]);
        }
    }
}
inline int Max(int l,int r){int k=lg[r-l];return l==r?l:max(mx[l][k],mx[r-(1<<k)][k]);}
inline int Min(int l,int r){int k=lg[r-l];return l==r?l:min(mn[l][k],mn[r-(1<<k)][k]);}

int cnt[N],vis[N];
vector<int> v[N];
vector<array<int,4>> seg[N];
inline void PushSeg(int x){
    for(int i:v[x]) vis[i]=1;
    for(int i=0;i+1<v[x].size();i++){
        int j=i+1;
        int l=i-1,r=j+1;
        if(!i||Max(v[x][i],v[x][j])>Max(v[x][i-1],v[x][i])) while(l>=0&&Max(v[x][l],v[x][j])==Max(v[x][i],v[x][j])) l--;
        while(r<v[x].size()&&Max(v[x][i],v[x][r])==Max(v[x][i],v[x][j])) r++;
        seg[Max(v[x][i],v[x][j])].push_back({x,l+1,i,r-1});
    }
}
namespace Block1{
    int blk[N],L[N],R[N],B;
    ll dat[N],sum[N];
    inline void Init(){
        B=sqrt(n);
        for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
        for(int i=n;i>=1;i--) L[blk[i]]=i;
        for(int i=1;i<=n;i++) R[blk[i]]=i;
    }
    inline void Add(int pos,ll k){dat[pos]+=k,sum[blk[pos]]+=k;}
    inline ll Sum(int pos){
        ll ans=0;
        for(int i=1;i<blk[pos];i++) ans+=sum[i];
        for(int i=L[blk[pos]];i<=pos;i++) ans+=dat[i];
        return ans;
    }
    inline ll Sum(int l,int r){return Sum(r)-Sum(l-1);}
}
vector<pii> qry[N];
inline void CalcSeg(){
    for(int i=1;i<=q;i++) qry[qr[i]].push_back({i,1});
    for(int i=1;i<=q;i++) qry[ql[i]-1].push_back({i,-1});
    Block1::Init();
    for(int i=1;i<=n;i++){
        if(vis[i]) Block1::Add(i,1);
        for(auto t:seg[i]){
            int x=t[0],l1=t[1],l2=t[2],r1=l2+1,r2=t[3];
            for(int l=l1;l<=l2;l++){
                for(int r=r1;r<=r2;r++){
                    if(Min(v[x][l],v[x][r])==v[x][l]&&Max(v[x][l],v[x][r])==v[x][r]){
                        Block1::Add(Min(v[x][l],v[x][r]),1);
                    }
                }
            }
        }
        for(pii p:qry[i]) ans[fir(p)]+=Block1::Sum(ql[fir(p)],qr[fir(p)])*sec(p);
    }
}

namespace Block2{
    int blk[N],L[N],R[N],B;
    ll hst[N],cur[N],hsum[N],sum[N],tag[N],pre[N],cpre[N],bpre[N];
    inline void Init(){
        B=sqrt(n)/2;
        for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
        for(int i=n;i>=1;i--) L[blk[i]]=i;
        for(int i=1;i<=n;i++) R[blk[i]]=i;
        for(int i=1;i<=n;i++) hst[i]=cur[i]=pre[i]=cpre[i]=0;
        for(int i=1;i<=blk[n];i++) hsum[i]=sum[i]=bpre[i]=tag[i]=0;
    }
    inline void PushUp(int x){
        for(int i=L[x];i<=R[x];i++){
            pre[i]=hst[i]+(i==L[x]?0:pre[i-1]);
            cpre[i]=cur[i]+(i==L[x]?0:cpre[i-1]);
        }
    }
    inline void PushUpAll(){for(int i=1;i<=blk[n];i++) bpre[i]=bpre[i-1]+hsum[i];}
    inline void PushDown(int x){for(int i=L[x];i<=R[x];i++) hst[i]+=cur[i]*tag[x];tag[x]=0;}
    inline void _Stamp(int l,int r){
        if(l==L[blk[l]]&&r==R[blk[r]]) tag[blk[l]]++,hsum[blk[l]]+=sum[blk[l]];
        else{
            PushDown(blk[l]);
            for(int i=l;i<=r;i++) hst[i]+=cur[i],hsum[blk[i]]+=cur[i];
            PushUp(blk[l]);
        }
    }
    inline void Stamp(int l,int r){
        if(blk[l]==blk[r]) return _Stamp(l,r),PushUpAll();
        _Stamp(l,R[blk[l]]),_Stamp(L[blk[r]],r);
        for(int i=blk[l]+1;i<blk[r];i++) tag[i]++,hsum[i]+=sum[i];
        PushUpAll();
    }
    inline void Modify(int pos,ll k){PushDown(blk[pos]),sum[blk[pos]]+=k-cur[pos],cur[pos]=k,PushUp(blk[pos]);}
    inline ll Query(int pos){return bpre[blk[pos]-1]+pre[pos]+cpre[pos]*tag[blk[pos]];}
    inline ll Query(int l,int r){return Query(r)-Query(l-1);}
}
vector<int> id;
inline void Solve(int x){
    vector<int> lp(v[x].size()),rp(v[x].size());
    vector<vector<int>> ers(v[x].size());
    for(int i=0;i<v[x].size();i++){
        int l=i,r=v[x].size();
        while(l+1<r){
            int mid=l+r>>1;
            if(Min(v[x][i],v[x][mid])<v[x][i]) r=mid;
            else l=mid;
        }
        lp[i]=l;
        ers[lp[i]].push_back(i);
    }
    for(int i=0;i<v[x].size();i++){
        int l=-1,r=i;
        while(l+1<r){
            int mid=l+r>>1;
            if(Max(v[x][mid],v[x][i])>v[x][i]) l=mid;
            else r=mid;
        }
        rp[i]=r;
    }
    Block2::Init();
    for(int i=0,p=0;i<v[x].size();i++){
        Block2::Modify(v[x][i],1);
        Block2::Stamp(v[x][rp[i]],v[x][i]);
        while(p<id.size()&&qr[id[p]]<v[x][i]) p++;
        while(p<id.size()&&qr[id[p]]<(i+1<v[x].size()?v[x][i+1]:n+1)){
            ans[id[p]]+=Block2::Query(ql[id[p]],qr[id[p]]);
            p++;
        }
        for(int j:ers[i]) Block2::Modify(v[x][j],0);
    }
}

signed main(){
    cin>>tid>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1,u,v;i<n;i++) cin>>u>>v,AddEdge(u,v),AddEdge(v,u);
    for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i];
    
    DFS1(1),DFS2(1,1);
    InitPathRMQ();
    InitRMQ();

    B=2*sqrt(n);
    
    for(int i=1;i<=n;i++) v[a[i]].push_back(i);
    for(int i=1;i<=q;i++) id.push_back(i);
    sort(id.begin(),id.end(),[](int i,int j){return qr[i]<qr[j];});
    for(int i=1;i<=n;i++) if(v[i].size()>B) Solve(i);
    for(int i=1;i<=n;i++) if(v[i].size()&&v[i].size()<=B) PushSeg(i);
    CalcSeg();
    
    for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

    return 0;
}