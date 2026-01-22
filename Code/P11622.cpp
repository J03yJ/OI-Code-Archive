#include<bits/stdc++.h>

using namespace std;

<<<<<<< HEAD
#define fir(x) x.first
#define sec(x) x.second
const int N=2e5+9;
using ll=long long;
using pii=pair<int,int>;

mt19937 rng(4649);
inline bool Decide(int p,int q){return rng()%q<p;}

int lnk[N];
inline void Init(int lim){iota(lnk+1,lnk+lim+1,1);}
inline int Find(int x){
    if(x==lnk[x]) return x;
    else return lnk[x]=Find(lnk[x]);
}
inline void Union(int x,int y){lnk[Find(x)]=Find(y);}

struct Node{
    int lc,rc,fa,siz;
    ll dat,add,rev;
}tr[N<<4];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define fa(x) tr[x].fa
#define siz(x) tr[x].siz
#define dat(x) tr[x].dat
#define add(x) tr[x].add
#define rev(x) tr[x].rev

int cnt;
inline int Allc(){return ++cnt;}
inline int Allc(ll k){
    int x=Allc();
    dat(x)=k,siz(x)=1,add(x)=rev(x)=0,fa(x)=lc(x)=rc(x)=0;
    return x;
}

inline void PushAdd(int x,ll k){if(x) add(x)+=k,dat(x)+=k;}
inline void PushDownAdd(int x){PushAdd(lc(x),add(x)),PushAdd(rc(x),add(x)),add(x)=0;}
inline void PushRev(int x){if(x) rev(x)^=1,add(x)=-add(x),dat(x)=-dat(x),swap(lc(x),rc(x));}
inline void PushDownRev(int x){if(x&&rev(x)) PushRev(lc(x)),PushRev(rc(x)),rev(x)=0;}
inline void PushDown(int x){PushDownRev(x),PushDownAdd(x);}
inline void PushUp(int x){siz(x)=siz(lc(x))+siz(rc(x))+1,fa(lc(x))=lc(x)?x:0,fa(rc(x))=rc(x)?x:0;}

inline pii Split(int x,ll k){
    if(!x) return {0,0};
    PushDown(x);
    if(dat(x)<=k){
        pii tmp=Split(rc(x),k);
        rc(x)=fir(tmp);
        PushUp(x);
        return {x,sec(tmp)};
    }else{
        pii tmp=Split(lc(x),k);
        lc(x)=sec(tmp);
        PushUp(x);
        return {fir(tmp),x};
    } 
}

inline void Slap(int x,vector<int> &v){
    if(!x) return ;
    v.push_back(x);
    Slap(lc(x),v),Slap(rc(x),v);
}
inline int Join(int x,int y){
    if(!x||!y) return x|y;
    if(rng()&1) swap(x,y);
    PushDown(x);
    pii p=Split(y,dat(x));
    pii q=Split(fir(p),dat(x)-1);
    vector<int> tmp;
    Slap(sec(q),tmp);
    for(int u:tmp) Union(u,x);
    lc(x)=Join(lc(x),fir(q)),rc(x)=Join(rc(x),sec(p));
    PushUp(x);
    return x;
}

ll a[N];int n;
int ql[N],qr[N],q;ll qx[N],ans[N];
vector<int> st[N],ed[N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=q;i++) cin>>qx[i]>>ql[i]>>qr[i],Allc(qx[i]);

    Init(q);
    int root=0;
    for(int i=1;i<=q;i++) st[ql[i]].push_back(i),ed[qr[i]].push_back(i);
    for(int i=1;i<=n;i++){
        for(int j:st[i]) root=Join(root,j);
        pii tmp=Split(root,a[i]>>1);
        PushRev(fir(tmp));
        PushAdd(fir(tmp),a[i]);
        root=Join(fir(tmp),sec(tmp));
        fa(root)=0;
        for(int j:ed[i]){
            int x=Find(j);
            vector<int> anc;
            while(x) anc.push_back(x),x=fa(x);
            reverse(anc.begin(),anc.end());
            for(int u:anc) PushDown(u);
            ans[j]=dat(Find(j));
        }
    }

    for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

=======
const int N=2e5+9;

signed main(){
>>>>>>> d8147174aa15e80698100c4d67760eaf3e5689db
    return 0;
}