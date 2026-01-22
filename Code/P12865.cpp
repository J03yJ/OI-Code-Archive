#include<bits/stdc++.h>

using namespace std;

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
    inline void PushUp(int x){
        sum(x)=sum(x<<1)+sum(x<<1|1);
        siz(x)=siz(x<<1)+siz(x<<1|1);
    }
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
    }
}
namespace Fenw{
    struct Fenw{
        ll tr[N];
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

    return 0;
}