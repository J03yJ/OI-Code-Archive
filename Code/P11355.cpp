#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;
const int lgN=2e1;
const int inf=INT_MAX;

int c[N],f[N],d[N],p[N],val[N],n;
int s[N],t[N],diff[N],ql[N],qr[N],ans[N],q;

struct Node{
    int l,r,dat;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat

inline void PushUp(int x){dat(x)=__gcd(dat(x<<1),dat(x<<1|1));}
inline void Build(int x,int l,int r){
    l(x)=l,r(x)=r,dat(x)=0;
    if(l(x)==r(x)) return ;
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
}
inline void Modify(int x,int pos,int k){
    if(l(x)==r(x)) return dat(x)=k,void();
    int mid=l(x)+r(x)>>1;
    if(pos<=mid) Modify(x<<1,pos,k);
    else Modify(x<<1|1,pos,k);
    PushUp(x);
}
inline int Query(int x,int l,int r){
    if(l>r) return 0;
    if(l<=l(x)&&r(x)<=r) return dat(x);
    int mid=l(x)+r(x)>>1;
    if(l<=mid&&r>mid) return __gcd(Query(x<<1,l,mid),Query(x<<1|1,mid+1,r));
    else if(l<=mid) return Query(x<<1,l,r);
    else return Query(x<<1|1,l,r);
}

int dval[N],tot;
vector<int> dpos[N];
inline void Solve(vector<int> &v,int l,int r){
    if(!v.size()) return ;
    if(l==r){
        for(int i:v) ans[i]=dval[l];
        return ;
    }
    int mid=ll(l)+ll(r)>>1;
    vector<int> lv,rv;
    for(int i=l;i<=mid;i++) for(int j:dpos[i]) Modify(1,j,d[j]);
    for(int i:v){
        int tmp=Query(1,ql[i],qr[i]-1);
        if(tmp&&diff[i]%tmp==0) lv.push_back(i);
        else rv.push_back(i);
    }
    for(int i=l;i<=mid;i++) for(int j:dpos[i]) Modify(1,j,0);
    Solve(lv,l,mid);
    for(int i=l;i<=mid;i++) for(int j:dpos[i]) Modify(1,j,d[j]);
    Solve(rv,mid+1,r);
    for(int i=l;i<=mid;i++) for(int j:dpos[i]) Modify(1,j,0);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>c[i];
    for(int i=1;i<=n;i++) cin>>f[i];
    for(int i=1;i<=q;i++) cin>>s[i]>>t[i]>>ql[i]>>qr[i];

    iota(p+1,p+n+1,1);
    sort(p+1,p+n+1,[](int i,int j){return f[i]<f[j];});
    for(int i=1;i<=n;i++) val[i]=f[p[i]];
    for(int i=1;i<n;i++) d[i]=abs(c[p[i+1]]-c[p[i]]);

    vector<int> tmp;
    for(int i=1;i<=q;i++){
        ql[i]=lower_bound(val+1,val+n+1,ql[i])-val;
        qr[i]=upper_bound(val+1,val+n+1,qr[i])-val-1;
        diff[i]=abs(s[i]-t[i]);
        if(diff[i]&1) ans[i]=-1;
        else if(!diff[i]) ans[i]=0;
        else{
            diff[i]>>=1;
            tmp.push_back(i);
        }
    }

    for(int i=1;i<n;i++) dval[++tot]=val[i+1]-val[i];
    dval[++tot]=inf;
    sort(dval+1,dval+tot+1);
    tot=unique(dval+1,dval+tot+1)-dval-1;
    for(int i=1;i<n;i++){
        dpos[lower_bound(dval+1,dval+tot+1,val[i+1]-val[i])-dval].push_back(i);
    }

    Build(1,1,n-1);
    Solve(tmp,1,tot);
    for(int i=1;i<=q;i++){
        if(ans[i]==inf) cout<<-1<<' ';
        else cout<<ans[i]<<' ';
    }
    cout<<endl;

    return 0;
}