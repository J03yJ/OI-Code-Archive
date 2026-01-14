#include<bits/stdc++.h>

using namespace std;

ifstream fin("entrench.in");
ofstream fout("entrench.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=4e5+9;
const int SQ=7e2+9;

int fa[N],lc[N],rc[N],lv[N],rv[N],n,m,q,typ,qB;

int xp[N],yp[N],rx[N],ry[N],L[N],R[N],mB,lim;
short xblk[N],yblk[N];
vector<int> tmp[N];
inline void BuildBlock(){
    int xcnt=0;
    for(int i=1;i<=m;i++) rx[i]=n-lv[i]+1,ry[i]=rv[i];
    for(int i=1;i<=m;i++) tmp[rx[i]].push_back(i);
    for(int i=1;i<=n;i++){
        for(int j:tmp[i]) xp[++xcnt]=j;
        tmp[i].clear();
    }
    for(int i=1;i<=m;i++) xblk[xp[i]]=(i-1)/mB+1;
    int ycnt=0;
    for(int i=1;i<=m;i++) tmp[ry[i]].push_back(i);
    for(int i=1;i<=n;i++){
        for(int j:tmp[i]) yp[++ycnt]=j;
        tmp[i].clear();
    }
    for(int i=1;i<=m;i++) yblk[yp[i]]=(i-1)/mB+1;
    for(int i=1;i<=m;i++) R[xblk[xp[i]]]=i;
    for(int i=m;i>=1;i--) L[xblk[xp[i]]]=i;
    lim=xblk[xp[m]];
}
int sum[SQ][SQ],xmx[SQ],ymx[SQ],w[N];
inline void CalcSum(){
    for(int i=1;i<=m;i++) w[i]=lc[i]?-1:1;
    for(int i=1;i<=lim;i++){
        for(int j=1;j<=lim;j++) sum[i][j]=sum[i-1][j];
        for(int j=L[i];j<=R[i];j++) sum[i][yblk[xp[j]]]+=w[xp[j]];
        xmx[i]=rx[xp[R[i]]];
        ymx[i]=ry[yp[R[i]]];
    }
    for(int i=1;i<=lim;i++){
        for(int j=1;j<=lim;j++) sum[i][j]+=sum[i][j-1];
    }
}
inline int Query(int x,int y){
    int xi=1,yi=1,ans=0;
    while(xi<=lim&&x>=xmx[xi]) xi++;
    while(yi<=lim&&y>=ymx[yi]) yi++;
    ans+=sum[xi-1][yi-1];
    if(xi<=lim){
        for(int j=L[xi];j<=R[xi];j++){
            if(rx[xp[j]]<=x&&ry[xp[j]]<=y) ans+=w[xp[j]];
        }
    }
    if(yi<=lim){
        for(int j=L[yi];j<=R[yi];j++){
            if(rx[yp[j]]<=x&&ry[yp[j]]<=y){
                if(xblk[yp[j]]!=xi) ans+=w[yp[j]];
            }
        }
    }
    return ans;
}
inline void PushUp(int x){
    if(!lc[x]) return ;
    else lv[x]=lv[lc[x]],rv[x]=rv[rc[x]];
    assert(rv[lc[x]]+1==lv[rc[x]]);
    assert(lv[x]<=rv[x]);
}

signed main(){
    cin>>n>>q>>typ;
    m=(n<<1)-1;
    for(int i=1;i<=m;i++){
        cin>>lv[i]>>rv[i]>>lc[i]>>rc[i];
        if(lc[i]) fa[lc[i]]=fa[rc[i]]=i;
    }

    mB=sqrt(m),qB=ceil(sqrt(q)*4);
    vector<array<int,3>> buf;
    BuildBlock(),CalcSum();
    for(int i=1,op,x,l,r,ans=0;i<=q;i++){
        if(buf.size()>=qB){
            buf.clear();
            BuildBlock(),CalcSum();
        }
        cin>>op;
        if(op==1){
            cin>>x;
            x=(x+typ*ans)%(n-1)+1;
            if(!fa[x]) continue ;
            int y=fa[x],z=fa[y];
            assert(lc[y]==x||rc[y]==x);
            buf.push_back({lv[x],rv[x],1});
            if(x==lc[y]){
                lc[y]=rc[x],fa[rc[x]]=y;
                rc[x]=y,fa[y]=x;
                fa[x]=z;
            }else{
                rc[y]=lc[x],fa[lc[x]]=y;
                lc[x]=y,fa[y]=x;
                fa[x]=z;
            }
            if(lc[z]==y) lc[z]=x;
            else if(rc[z]==y) rc[z]=x;
            PushUp(y),PushUp(x);
            buf.push_back({lv[y],rv[y],-1});
        }else{
            cin>>l>>r;
            l=(l+typ*ans)%n+1,r=(r+typ*ans)%n+1;
            if(l>r) swap(l,r);
            ans=Query(n-l+1,r);
            for(auto t:buf) if(l<=t[0]&&t[1]<=r) ans+=t[2];
            cout<<ans<<endl;
        }
    }

    return 0;
}