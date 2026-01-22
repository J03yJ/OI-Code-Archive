#include<bits/stdc++.h>

using namespace std;

const int N=5e4+9;
const int inf=1e9+7;
using lint=long long;

int a[N],n,lim;
int p[N],ip[N];
struct BIT{
    lint tr[N];
    void Add(int x,lint val){
        while(x<=n){
            tr[x]+=val;
            x+=x&-x;
        }
    }
    lint Ask(int x){
        lint sum=0;
        while(x){
            sum+=tr[x];
            x&=x-1;
        }
        return sum;
    }
}su,cc;

namespace In{
    struct Node{
        int lc,rc,cnt;
        lint sum;
    }tr[N<<8];
    #define lc(x) tr[x].lc
    #define rc(x) tr[x].rc
    #define cnt(x) tr[x].cnt
    #define sum(x) tr[x].sum
    int cnt;
    void Modify(int &x,int L,int R,int pos,int k,lint p){
        if(!x) x=++cnt;
        if(L==R) return cnt(x)+=k,sum(x)+=p,void();
        int mid=L+R>>1;
        if(pos<=mid) Modify(lc(x),L,mid,pos,k,p);
        else Modify(rc(x),mid+1,R,pos,k,p);
        cnt(x)=cnt(lc(x))+cnt(rc(x));
        sum(x)=sum(lc(x))+sum(rc(x));
    }
}

int tr[N];
void Modify(int x,int pos,int k,lint p){
    while(x<=n){
        In::Modify(tr[x],1,inf,pos,k,p);
        x+=x&-x;
    }
}
lint Work(vector<int> &lr,vector<int> &rr,int L,int R,int k){
    // if(debug) cout<<L<<' '<<R<<" : "<<k<<endl;
    // cout<<" : ";for(int x:lr) cout<<x<<' ';cout<<endl;
    // cout<<" : ";for(int x:rr) cout<<x<<' ';cout<<endl;
    if(L==R){
        int cnt=0;
        for(int x:rr) cnt+=In::cnt(x);
        for(int x:lr) cnt-=In::cnt(x);
        return 1ll*min(cnt,k)*L;
    }
    int mid=L+R>>1,lcnt=0;
    for(int x:rr) lcnt+=In::cnt(In::lc(x));
    for(int x:lr) lcnt-=In::cnt(In::lc(x));
    if(k<=lcnt){
        for(int &x:rr) x=In::lc(x);
        for(int &x:lr) x=In::lc(x);
        return Work(lr,rr,L,mid,k); 
    }else{
        lint lans=0;
        for(int x:rr) lans+=In::sum(In::lc(x));
        for(int x:lr) lans-=In::sum(In::lc(x));
        for(int &x:rr) x=In::rc(x);
        for(int &x:lr) x=In::rc(x);
        return Work(lr,rr,mid+1,R,k-lcnt)+lans;
    }
}
lint Query(int l,int r,int k){
    l=l-1;
    vector<int> lr,rr;
    while(l) lr.push_back(tr[l]),l&=l-1;
    while(r) rr.push_back(tr[r]),r&=r-1;
    return Work(lr,rr,1,inf,k);
}

int fa[N];
int Find(int x){
    if(fa[x]==x) return x;
    else return fa[x]=Find(fa[x]);
}
#define Merge(x,y) fa[Find(y)]=Find(x)

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'
    
    cin>>n>>lim;
    for(int i=1;i<=n;i++) cin>>a[i];

    iota(p+1,p+n+1,1);
    sort(p+1,p+n+1,[](int x,int y){return a[x]<a[y];});
    for(int i=1;i<=n;i++) ip[p[i]]=i;
    for(int i=1;i<=n;i++) su.Add(ip[i],a[i]),cc.Add(ip[i],1),Modify(i,a[i],1,a[i]);

    int dtot=0,trn=0;
    iota(fa+1,fa+n+1,1);
    while(dtot<n){
        int l=0,r=n+1;
        while(l+1<r){
            int mid=l+r>>1;
            if(su.Ask(mid)<=lim) l=mid;
            else r=mid;
        }
        int tot=cc.Ask(l),lft=lim;
        dtot+=tot;
        // for(int i=1;i<=n;i++) cout<<su.Ask(ip[i])-su.Ask(ip[i]-1)<<' ';cout<<endl;
        // for(int i=1;i<=n;i++) cout<<cc.Ask(ip[i])-cc.Ask(ip[i]-1)<<' ';cout<<endl;
        // cout<<tot<<" : ";
        while(tot){
            int l=0,r=n-tot+1+1;
            while(l+1<r){
                int mid=l+r>>1;
                if(Query(mid,n,tot)<=lft) l=mid;
                else r=mid;
            }
            // cout<<" % "<<l<<' '<<Find(l)<<endl;
            l=Find(l);
            // for(int i=1;i<=n;i++) cout<<fa[i]<<' ';cout<<endl;
            // cout<<l<<' '<<Find(l)<<' '<<Query(l,n,tot)<<' '<<tot<<' '<<lft<<endl;
            assert(l);
            tot--,lft-=a[l];
            Modify(l,a[l],-1,-a[l]),su.Add(ip[l],-a[l]),cc.Add(ip[l],-1);
            Modify(l,inf,1,inf);
            Merge(l-1,l);
            // cout<<l<<' ';
        }
        // cout<<endl;
        trn++;
    }

    cout<<trn<<endl;

    return 0;
}