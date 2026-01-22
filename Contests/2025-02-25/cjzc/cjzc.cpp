#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>

using namespace std;

ifstream fin("cjzc.in");
ofstream fout("cjzc.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
using ull=unsigned long long;
const int N=1e6+9;
const int lgN=2e1;
const ll MemLim=1e8;
template<class T1,class T2> inline void ChMax(T1 &x,T2 y){if(y>x) x=y;}

using umap=__gnu_pbds::gp_hash_table<ll,int>;
int ql[N],qr[N],n,m,B;
ll ans[N];
string s[N];
vector<int> rq[N];
vector<int> lng,sht;

struct Trie{
    struct Node{
        int son[26];
    }tr[N<<1];
    #define son(x,k) tr[x].son[k]
    int dep[N],fa[N][lgN],cnt,root;
    inline void Init(){
        cnt=root=1;
        dep[root]=0,dep[0]=-1;
    }
    inline int Insert(string s){
        int x=root;
        for(char c:s){
            if(!son(x,c-'a')){
                son(x,c-'a')=++cnt;
                dep[cnt]=dep[x]+1;
                fa[cnt][0]=x;
            }
            x=son(x,c-'a');
        }
        return x;
    }
    inline void Calc(){
        for(int k=1;k<lgN;k++){
            for(int i=1;i<=cnt;i++) fa[i][k]=fa[fa[i][k-1]][k-1];
        }
    }
    inline int LCA(int x,int y){
        if(dep[x]<dep[y]) swap(x,y);
        for(int k=lgN-1;~k;k--) if(dep[fa[x][k]]>=dep[y]) x=fa[x][k];
        if(x==y) return x;
        for(int k=lgN-1;~k;k--) if(fa[x][k]!=fa[y][k]) x=fa[x][k],y=fa[y][k];
        return fa[x][0];
    }
}pref,suff;

int pid[N],sid[N];
inline void InitLng(){
    pref.Init();
    suff.Init();
    for(int i:lng){
        pid[i]=pref.Insert(string(s[i].begin(),s[i].end()));
        sid[i]=suff.Insert(string(s[i].rbegin(),s[i].rend()));
    }
    pref.Calc();
    suff.Calc();
}
inline ll FastQuery(int i,int j){
    int lcp=pref.dep[pref.LCA(pid[i],pid[j])];
    int lcs=suff.dep[suff.LCA(sid[i],sid[j])];
    return 1ll*lcp*lcs;
}
inline ll BruteQuery(int i,int j){
    if(s[i].size()>s[j].size()) swap(i,j);
    int lcp=0;
    while(lcp<s[i].size()&&s[i].begin()[lcp]==s[j].begin()[lcp]) lcp++;
    int lcs=0;
    while(lcs<s[i].size()&&s[i].rbegin()[lcs]==s[j].rbegin()[lcs]) lcs++;
    return 1ll*lcp*lcs;
}

umap h;
ull prio[N],srio[N];
inline void Append(ull &x,char c){x=x*131+c;}

namespace Block{
    int L[N],R[N],blk[N],B;
    ll a[N],b[N];
    inline void Init(){
        B=sqrt(n);
        for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
        for(int i=1;i<=n;i++) R[blk[i]]=i;
        for(int i=n;i>=1;i--) L[blk[i]]=i;
    }
    inline void Modify(int x,ll k){ChMax(a[x],k),ChMax(b[blk[x]],k);}
    inline ll Max(int pos){
        ll ans=0;
        int cnt=0;
        for(int i=pos;i<=R[blk[pos]];i++) ChMax(ans,a[i]);
        for(int i=blk[pos]+1;i<=blk[n];i++) ChMax(ans,b[i]);
        return ans;
    }
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>s[i];
    for(int i=1;i<=m;i++) cin>>ql[i]>>qr[i],rq[qr[i]].push_back(i);
    B=100;

    mt19937 rng(4649);
    for(int i=1;i<=5e5;i++) prio[i]=rng();
    for(int i=1;i<=5e5;i++) srio[i]=rng();

    for(int i=1;i<=n;i++){
        if(s[i].size()>B) lng.push_back(i);
        else sht.push_back(i);
    }

    ll cnt=0;
    for(int i:sht) cnt+=1ll*s[i].size()*s[i].size();

    InitLng();
    Block::Init();
    for(int i=1;i<=n;i++){
        if(s[i].size()>B){
            for(int j:lng){
                if(j>=i) break ;
                Block::Modify(j,FastQuery(i,j));
            }
            for(int j:sht){
                if(j>=i) break ;
                Block::Modify(j,BruteQuery(i,j));
            }
        }else{
            for(int j:lng){
                if(j>=i) break ;
                Block::Modify(j,BruteQuery(i,j));
            }
            for(int j:sht){
                if(j>=i) break ;
                Block::Modify(j,BruteQuery(i,j));
            }
        }
        for(int j:rq[i]) ChMax(ans[j],Block::Max(ql[j]));
    }

    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;

    return 0;
}