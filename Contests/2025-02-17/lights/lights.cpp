#include<bits/stdc++.h>

using namespace std;

ifstream fin("lights.in");
ofstream fout("lights.out");
#define cin fin
#define cout fout
#define endl '\n'

#define fir(x) x.first
#define sec(x) x.second
using pii=pair<int,int>;
const int N=3e5+9;
const int mod=998244353;
const int V=3e5;
inline void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline int Add(int x,int y){x+=y;if(x>=mod) x-=mod;return x;}
inline int Sub(int x,int y){x-=y;if(x<0) x+=mod;return x;}

int pri[N],ntp[N],mu[N],pcnt;
inline void Init(int lim){
    ntp[1]=1,mu[1]=1;
    for(int i=2;i<=lim;i++){
        if(!ntp[i]) pri[++pcnt]=i,mu[i]=mod-1;
        for(int j=1;j<=pcnt&&i*pri[j]<=lim;j++){
            ntp[i*pri[j]]=1;
            if(i%pri[j]) mu[i*pri[j]]=mod-mu[i];
            else{
                mu[i*pri[j]]=0;
                break ;
            }
        }
    }
}
inline int S(int x){return 1ll*x*(x+1)/2%mod;}

int qn[N],qm[N],qk[N],ans[N],q;
vector<int> qry[N];

int blk[N],L[N],R[N],a[N],pre[N],bpre[N],B;
inline void Build(){
    B=sqrt(V);
    for(int i=1;i<=V;i++) blk[i]=(i-1)/B+1;
    for(int i=1;i<=V;i++) R[blk[i]]=i;
    for(int i=V;i>=1;i--) L[blk[i]]=i;
}
inline void Modify(int pos,int k){
    AddAs(a[pos],k);
    for(int i=pos;i<=R[blk[pos]];i++) AddAs(pre[i],k);
    for(int i=blk[pos];i<=blk[V];i++) AddAs(bpre[i],k);
}
inline int Query(int pos){return pos?Add(pre[pos],bpre[blk[pos]-1]):0;}
inline int Query(int l,int r){return Sub(Query(r),Query(l-1));}

inline int F(int n,int m){
    int sum=0;
    if(n>m) swap(n,m);
    for(int l=1,r;l<=n;l=r+1){
        r=min(n/(n/l),m/(m/l));
        AddAs(sum,1ll*S(n/l)*S(m/l)%mod*Query(l,r)%mod);
    }
    return sum;
}

signed main(){
    Init(V);

    cin>>q;
    for(int i=1;i<=q;i++) cin>>qn[i]>>qm[i]>>qk[i],qry[qk[i]].push_back(i);

    Build();
    for(int d=1;d<=V;d++){
        for(int c=d;c<=V;c+=d) Modify(c,1ll*c*c%mod*mu[c/d]%mod);
        for(int i:qry[d]) ans[i]=F(qn[i],qm[i]);
    }

    for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

    return 0;
}