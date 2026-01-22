#include<bits/stdc++.h>

using namespace std;

ifstream fin("pre.in");
ofstream fout("pre.out");
#define cin fin
#define cout fout

#define fir(x) (x).first
#define sec(x) (x).second
using ll=long long;
using pll=pair<ll,ll>;
const int N=3e5+9;
const int SQ=1e3+9;
const int mod=998244353;

struct Seg{
    int l,r,op,pre,suc;
}s[N];
#define l(x) s[x].l
#define r(x) s[x].r
#define op(x) s[x].op
#define pre(x) s[x].pre
#define suc(x) s[x].suc

int scnt;
inline int Allc(){return ++scnt;}
inline int Allc(int l,int r,int op){
    int x=Allc();
    l(x)=l,r(x)=r,op(x)=op;
    return x;
}
inline void Clear(){while(scnt) l(scnt)=r(scnt)=op(scnt)=pre(scnt)=suc(scnt)=0,scnt--;}

int a[N],b[N],n,q,c;
int blk[N],L[N],R[N],B;
ll v[SQ][SQ<<3],w[SQ][SQ<<3],cnt[SQ];

inline ll BruteQuery(int l,int r,ll k){
    for(int i=l;i<=r;i++) if(k>=a[i]) k+=b[i];
    return k;
}
inline ll Query(int l,int r,ll k){
    if(blk[l]==blk[r]) return BruteQuery(l,r,k);
    int lf=l!=L[blk[l]],rf=r!=R[blk[r]];
    if(lf) k=BruteQuery(l,R[blk[l]],k);
    for(int i=blk[l]+lf;i<=blk[r]-rf;i++){
        int pos=lower_bound(v[i]+1,v[i]+cnt[i]+1,k+1)-v[i]-1;
        k+=w[i][pos];
    }
    if(rf) k=BruteQuery(L[blk[r]],r,k);
    return k;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>q>>c;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];

    B=min(n,(int)sqrt(n*15));
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    for(int i=n;i>=1;i--) L[blk[i]]=i;
    for(int i=1;i<=n;i++) R[blk[i]]=i;

    for(int i=1;i<=blk[n];i++){
        int head=Allc(0,1e9+1,1);
        for(int j=L[i];j<=R[i];j++){
            int cur=head,sum=-1;
            while(cur){
                int len=op(cur)?r(cur)-l(cur)+1:l(cur);
                if(sum+len<a[j]) sum+=len;
                else{
                    int len=a[j]-sum-1;
                    int p=Allc(l(cur),r(cur),op(cur));
                    if(op(cur)){
                        r(cur)=l(cur)+len-1;
                        l(p)=l(cur)+len;
                    }else{
                        l(cur)=len;
                        l(p)-=len;
                    }
                    pre(p)=cur,suc(p)=suc(cur);
                    pre(suc(p))=p,suc(cur)=p;
                    int q=Allc(b[j],0,0);
                    pre(q)=cur,suc(q)=suc(cur);
                    pre(suc(q))=q,suc(cur)=q;
                    break ;
                }
                cur=suc(cur);
            }
        }
        ll sum=0;
        int cur=head;
        while(cur){
            if(op(cur)) v[i][++cnt[i]]=l(cur),w[i][cnt[i]]=sum;
            else sum+=l(cur);
            cur=suc(cur);
        }
        Clear();
    }

    ll lst=0;
    while(q--){
        int l,r,k;
        cin>>l>>r>>k;
        if(c) k^=lst%mod;
        cout<<(lst=Query(l,r,k))<<endl;
    }

    return 0;
}