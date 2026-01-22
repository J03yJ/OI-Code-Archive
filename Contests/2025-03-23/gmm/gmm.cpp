#include<bits/stdc++.h>

using namespace std;

ifstream fin("gmm.in");
ofstream fout("gmm.out");
#define cin fin
#define cout fout

#define fir(x) (x).first
#define sec(x) (x).second
using ll=long long;
using pii=pair<int,int>;
const int N=5e5+9;
const int lgN=2e1;

int a[N],n,k;

int g[N][lgN],mx[N][lgN],lg[N];
inline void Init(){
    for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
    for(int i=1;i<=n;i++) g[i][0]=mx[i][0]=a[i];
    for(int k=1;k<=lg[n];k++){
        for(int i=1;i<=n-(1<<k)+1;i++){
            g[i][k]=__gcd(g[i][k-1],g[i+(1<<k-1)][k-1]);
            mx[i][k]=max(mx[i][k-1],mx[i+(1<<k-1)][k-1]);
        }
    }
}
inline int G(int l,int r){
    if(l>r) return -1;
    int k=lg[r-l+1];
    return __gcd(g[l][k],g[r-(1<<k)+1][k]);
}
inline int Max(int l,int r){
    if(l>r) return -1;
    int k=lg[r-l+1];
    return max(mx[l][k],mx[r-(1<<k)+1][k]);
}

namespace Part1{
    inline ll Work(){
        ll sum=0;
        for(int i=1,j=1;i<=n;i++){
            while(j<=i&&G(j,i)+k<Max(j,i)) j++;
            if(a[i]==1) j=i+1;
            sum+=i-j+1;
        }
        return sum;
    }
}
namespace Part2{
    namespace PSgT{
        struct Node{
            int lc,rc,dat;
        }tr[N<<5];
        #define lc(x) tr[x].lc
        #define rc(x) tr[x].rc
        #define dat(x) tr[x].dat

        int cnt;
        inline int Allc(){return ++cnt;}
        inline int Clone(int x){int y=Allc();tr[y]=tr[x];return y;}
        inline void PushUp(int x){dat(x)=min(dat(lc(x)),dat(rc(x)));}
        inline void Build(int &x,int L,int R){
            x=Allc();
            if(L==R) return ;
            int mid=L+R>>1;
            Build(lc(x),L,mid);
            Build(rc(x),mid+1,R);
            PushUp(x);
        }
        inline void Insert(int &x,int L,int R,int pos,int t){
            x=Clone(x);
            if(L==R) return dat(x)=t,void();
            int mid=L+R>>1;
            if(pos<=mid) Insert(lc(x),L,mid,pos,t);
            else Insert(rc(x),mid+1,R,pos,t);
            PushUp(x);
        }
        inline int Query(int x,int L,int R,int k){
            if(L==R) return L;
            int mid=L+R>>1;
            if(dat(lc(x))<=k) return Query(lc(x),L,mid,k);
            else return Query(rc(x),mid+1,R,k);
        }

        int root[N];
        inline void Init(){
            Build(root[0],1,n+1);
            for(int i=1;i<=n;i++){
                root[i]=root[i-1];
                Insert(root[i],1,n+1,a[i],i);
            }
        }
        inline int Mex(int l,int r){return Query(root[r],1,n+1,l-1);}
        inline int mex(int l,int r){
            vector<int> v(n+2,0);
            for(int i=l;i<=r;i++) v[a[i]]++;
            for(int i=1;i<=n+1;i++) if(!v[i]) return i;
            return n+1;
        }
    }
    namespace SgT{
        struct Node{
            int l,r;
            int cnt,sum;
        }tr[N<<2];
        #define l(x) tr[x].l
        #define r(x) tr[x].r
        #define cnt(x) tr[x].cnt
        #define sum(x) tr[x].sum
        #define len(x) (r(x)-l(x)+1)

        inline void PushUp(int x){
            if(cnt(x)) sum(x)=len(x);
            else if(l(x)!=r(x)) sum(x)=sum(x<<1)+sum(x<<1|1);
            else sum(x)=0;
        }
        inline void Push(int x,int k){cnt(x)+=k,PushUp(x);}
        inline void Build(int x,int l,int r){
            l(x)=l,r(x)=r;
            if(l(x)==r(x)) return ;
            int mid=l(x)+r(x)>>1;
            Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
        }
        inline void Modify(int x,int l,int r,int k){
            if(l<=l(x)&&r(x)<=r) return Push(x,k);
            int mid=l(x)+r(x)>>1;
            if(l<=mid) Modify(x<<1,l,r,k);
            if(r>mid) Modify(x<<1|1,l,r,k);
            PushUp(x);
        }
    }
    vector<pii> seg[N];
    inline vector<pii> Unique(vector<pii> v){
        sort(v.begin(),v.end(),[](pii x,pii y){
            if(fir(x)^fir(y)) return fir(x)>fir(y);
            else return sec(x)<sec(y);
        });
        vector<pii> tmp;
        int r=n+1;
        for(pii p:v){
            if(sec(p)>=r) continue ;
            else{
                r=sec(p);
                tmp.push_back(p);
            }
        }
        return tmp;
    }
    inline int FindLPos(int L,int R,int p,int k){
        int l=L,r=R+1;
        while(l+1<r){
            int mid=l+r>>1;
            if(Max(mid,p)<=k) r=mid;
            else l=mid;
        }
        return r;
    }
    inline int FindRPos(int L,int R,int p,int k){
        int l=L-1,r=R;
        while(l+1<r){
            int mid=l+r>>1;
            if(Max(p,mid)<=k) l=mid;
            else r=mid;
        }
        return l;
    }
    vector<array<int,3>> qry[N];
    inline void NewCarpet(int l,int r,int L,int R){
        if(l>r||L>R) return ;
        qry[l].push_back({L,R,1});
        qry[r+1].push_back({L,R,-1});
    }
    vector<int> c[N];
    inline void CalcSeg(){
        PSgT::Init();
        for(int i=1;i<=n;i++) if(a[i]==1) seg[2].push_back({i,i});
        for(int i=1;i<=n+1;i++) c[i].push_back(0);
        for(int i=1;i<=n;i++) c[a[i]].push_back(i);
        for(int i=1;i<=n+1;i++) c[i].push_back(n+1);
        for(int i=2;i<=n+1;i++){
            seg[i]=Unique(seg[i]);
            for(pii p:seg[i]){
                int l=fir(p),r=sec(p);
                int lp=*--upper_bound(c[i].begin(),c[i].end(),l);
                int rp=*upper_bound(c[i].begin(),c[i].end(),r);
                if(lp!=0) seg[PSgT::Mex(lp,r)].push_back({lp,r});
                if(rp!=n+1) seg[PSgT::Mex(l,rp)].push_back({l,rp});
                int lpos=FindLPos(lp,l,r,i+k),rpos=FindRPos(r,rp,l,i+k);
                NewCarpet(lpos,l,r,rpos);
            }
        }
    }
    inline ll Work(){
        ll sum=0;
        CalcSeg();
        SgT::Build(1,1,n);
        for(int i=1;i<=n;i++){
            for(auto t:qry[i]) SgT::Modify(1,t[0],t[1],t[2]);
            sum+=SgT::sum(1);
        }
        return sum;
    }
}

signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];

    Init();
    cout<<Part1::Work()+Part2::Work()<<endl;

    return 0;
}