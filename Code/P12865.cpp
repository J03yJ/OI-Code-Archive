#include<bits/stdc++.h>

using namespace std;

<<<<<<< HEAD
#define fir(p) p.first
#define sec(p) p.second
using ll=long long;
const int N=5e5+9;

int a[N],srt[N],rk[N],n;
int ql[N],qr[N],t[N],op[N],q;
ll pre[N],ans[N];

namespace PSgT{
    struct Node{
        int lc,rc;
        ll sum,siz;
    }tr[N<<5];
    #define lc(x) tr[x].lc
    #define rc(x) tr[x].rc
    #define sum(x) tr[x].sum
    #define siz(x) tr[x].siz

    int root[N],cnt;
    inline int Allc(){return ++cnt;}
    inline int Clone(int x){int y=Allc();tr[y]=tr[x];return y;}
=======
#define endl '\n'
using ll=long long;
const int N=5e5+9;

int a[N],rk[N],n,q,tot;
vector<int> lft[N];

namespace SgT{
    struct Node{
        int l,r;
        ll sum,siz;
    }tr[N<<2];
    #define l(x) tr[x].l
    #define r(x) tr[x].r
    #define sum(x) tr[x].sum
    #define siz(x) tr[x].siz

>>>>>>> d8147174aa15e80698100c4d67760eaf3e5689db
    inline void PushUp(int x){
        sum(x)=sum(x<<1)+sum(x<<1|1);
        siz(x)=siz(x<<1)+siz(x<<1|1);
    }
<<<<<<< HEAD
    inline void Insert(int &x,int L,int R,int pos,int val){
        x=Clone(x);
        if(L==R) return sum(x)=val,siz(x)=1,void();
        int mid=L+R>>1;
        if(pos<=mid) Insert(lc(x),L,mid,pos,val);
        else Insert(rc(x),mid+1,R,pos,val);
        PushUp(x);
    }
    inline ll Query(int x,int k){
        if(!k||!x) return 0;
        if(k==siz(x)) return sum(x);
        if(k<=siz(rc(x))) return Query(rc(x),k);
        else return sum(rc(x))+Query(lc(x),k-siz(lc(x)));
=======
    inline void Build(int x,int l,int r){
        l(x)=l,r(x)=r;
        if(l(x)==r(x)) return ;
        int mid=l(x)+r(x)>>1;
        Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
        PushUp(x);
    }
    inline void Insert(int x,int pos,int k){
        if(l(x)==r(x)) return sum(x)+=k,siz(x)++,void();
        int mid=l(x)+r(x)>>1;
        if(pos<=mid) Insert(x<<1,pos,k);
        else Insert(x<<1|1,pos,k);
        PushUp(x);
    }
    inline ll Query(int x,int k){
        if(!k) return 0;
        if(k>=siz(x)) return sum(x);
        if(l(x)==r(x)) return k*(sum(x)/siz(x));
        if(k<=siz(x<<1)) return Query(x<<1,k);
        else return sum(x<<1)+Query(x<<1|1,k-siz(x<<1));
>>>>>>> d8147174aa15e80698100c4d67760eaf3e5689db
    }
}
namespace Fenw{
    struct Fenw{
        ll tr[N];
<<<<<<< HEAD
        inline void Add(int x,int k){while(x<=n) tr[x]+=k,x+=x&-x;}
        inline ll Ask(int x){ll sum=0;while(x) sum+=tr[x],x&=x-1;return sum;}
        inline ll Ask(int l,int r){return Ask(r)-Ask(l-1);}
    }sum,cnt;
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    cin>>q;
    for(int i=1,cur=0;i<=q;i++){
        cin>>op[i];
        if(op[i]==1) cur++;
        else cin>>ql[i]>>qr[i],t[i]=cur;
    }

    int tmp=0;
    map<int,int> mp;
    for(int i=1;i<=n;i++) mp[a[i]]++;
    for(auto &p:mp) sec(p)=tmp+=sec(p);
    for(int i=n;i>=1;i--) rk[i]=mp[a[i]]--,srt[rk[i]]=i;

    for(int i=1;i<=n;i++) pre[i]=pre[i-1]+a[i];
    for(int i=1;i<=n;i++){
        PSgT::root[i]=PSgT::root[i-1];
        PSgT::Insert(PSgT::root[i],1,n,rk[i],a[i]);
    }

    vector<array<int,4>> qry;
    for(int i=1;i<=q;i++){
        if(op[i]==1) continue ;
        if(ql[i]-1) qry.push_back({ql[i]-1,ql[i]-1+t[i],i,-1});
        if(qr[i]) qry.push_back({qr[i],qr[i]+t[i],i,1});
    }
    sort(qry.begin(),qry.end(),greater<array<int,4>>());
    for(int i=1;i<=n;i++){
        Fenw::cnt.Add(srt[i],1);
        Fenw::sum.Add(srt[i],a[srt[i]]);
        while(qry.size()&&qry.back()[0]<=i){
            array<int,4> t(qry.back());
            t[1]=min(t[1],n);
            qry.pop_back();
            cout<<i<<' '<<t[0]<<' '<<t[1]<<' '<<t[2]<<' '<<t[3]<<" : "<<endl;
            cout<<"    "<<Fenw::sum.Ask(t[0]+1,t[1])<<' '<<Fenw::cnt.Ask(t[0]+1,t[1])<<' '<<PSgT::Query(PSgT::root[t[0]],Fenw::cnt.Ask(t[0]+1,t[1]))*t[3]<<endl;
            ans[t[2]]+=Fenw::sum.Ask(t[0]+1,t[1])*t[3];
            ans[t[2]]-=PSgT::Query(PSgT::root[t[0]],Fenw::cnt.Ask(t[0]+1,t[1]))*t[3];
            ans[t[2]]+=pre[t[0]]*t[3];
        }
    }

    for(int i=1;i<=q;i++) if(op[i]!=1) cout<<ans[i]<<endl;

=======
        inline void Add(int x,int k){while(x<=n){tr[x]+=k,x+=x&-x;}}
        inline ll Ask(int x){ll sum=0;while(x){sum+=tr[x],x&=x-1;}return sum;}
        inline ll Ask(int l,int r){return Ask(r)-Ask(l-1);}
    }val,cnt,sum;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    vector<int> val(a+1,a+n+1);
    val.push_back(0);
    sort(val.begin(),val.end());
    val.erase(unique(val.begin(),val.end()),val.end());
    for(int i=1;i<=n;i++) rk[i]=lower_bound(val.begin(),val.end(),a[i])-val.begin();
    tot=val.size()-1;

    for(int i=1;i<=n;i++){
        Fenw::val.Add(rk[i],1);
        Fenw::cnt.Add(i,1);
        Fenw::sum.Add(i,a[i]);
        lft[Fenw::val.Ask(rk[i]+1,n)+1].push_back(i);
    }

    int t=0;
    auto PreQ=[&t](int pos){
        int qos=min(pos+t,n);
        return Fenw::sum.Ask(qos)+SgT::Query(1,pos-Fenw::cnt.Ask(qos));
    };
    SgT::Build(1,1,tot);
    cin>>q;
    while(q--){
        int op;
        cin>>op;
        if(op==1){
            t++;
            for(int i:lft[t]){
                Fenw::cnt.Add(i,-1);
                Fenw::sum.Add(i,-a[i]);
                SgT::Insert(1,rk[i],a[i]);
            }
        }else{
            int l,r;
            cin>>l>>r;
            cout<<PreQ(r)-PreQ(l-1)<<endl;
        }
    }

>>>>>>> d8147174aa15e80698100c4d67760eaf3e5689db
    return 0;
}