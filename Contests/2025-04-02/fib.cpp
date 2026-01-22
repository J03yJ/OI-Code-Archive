#include<bits/stdc++.h>

using namespace std;

ifstream fin("fib.in");
ofstream fout("fib.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
using ull=unsigned long long;
const int N=5e5+9;

ull f[N],fm[N][2]; // f_n^2 f_{n-1}*f_n

int Tid,n,m;
ull a[N];

struct Node{
    int l,r;
    ull a,b; // f_1 f_0
    ull ssum,fsum[2]; // a_i^2 a_i*f_i a_i*f_{i-1}
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define a(x) tr[x].a
#define b(x) tr[x].b
#define ssum(x) tr[x].ssum
#define fsum(x,k) tr[x].fsum[k]
#define len(x) (r(x)-l(x)+1)

inline ull F(int n,ull p,ull q){return n?f[n]*p+f[n-1]*q:q;}
inline void Push(int x,ull p,ull q){
    if(!p&&!q) return ;
    a(x)+=p,b(x)+=q;
    ssum(x)+=F(len(x)+1,p,q)*F(len(x),p,q)-p*q;
    ssum(x)+=2*(p*fsum(x,0)+q*fsum(x,1));
    fsum(x,0)+=p*fm[len(x)][0]+q*fm[len(x)][1];
    fsum(x,1)+=p*fm[len(x)][1]+q*fm[len(x)-1][0];
}
inline void PushDown(int x){
    if(!a(x)&&!b(x)) return ;
    Push(x<<1,a(x),b(x));
    Push(x<<1|1,F(len(x<<1)+1,a(x),b(x)),F(len(x<<1),a(x),b(x)));
    a(x)=b(x)=0;
}
inline void PushUp(int x){
    ssum(x)=ssum(x<<1)+ssum(x<<1|1);
    fsum(x,0)=fsum(x<<1,0)+(f[len(x<<1)+1]*fsum(x<<1|1,0))+(f[len(x<<1)]*fsum(x<<1|1,1));
    fsum(x,1)=fsum(x<<1,1)+(f[len(x<<1)+1]*fsum(x<<1|1,1))+(f[len(x<<1)]*(fsum(x<<1|1,0)-fsum(x<<1|1,1)));
}

inline void Build(int x,int l,int r){
    l(x)=l,r(x)=r;
    if(l(x)==r(x)) return ;
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
}
inline void Modify(int x,int l,int r,ull p,ull q){
    if(l<=l(x)&&r(x)<=r) return Push(x,p,q);
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(l<=mid&&r>mid){
        Modify(x<<1,l,mid,p,q);
        Modify(x<<1|1,mid+1,r,F(mid-l+2,p,q),F(mid-l+1,p,q));
    }else if(l<=mid) Modify(x<<1,l,r,p,q);
    else Modify(x<<1|1,l,r,p,q);
    PushUp(x);
}
inline ull Query(int x,int l,int r){
    if(l<=l(x)&&r(x)<=r) return ssum(x);
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(l<=mid&&r>mid) return Query(x<<1,l,r)+Query(x<<1|1,l,r);
    else if(l<=mid) return Query(x<<1,l,r);
    else return Query(x<<1|1,l,r);
}

signed main(){
    cin>>Tid>>n>>m;

    f[1]=1;
    for(int i=2;i<=n;i++) f[i]=f[i-1]+f[i-2];
    for(int i=1;i<=n;i++) fm[i][0]=fm[i-1][0]+f[i]*f[i];
    for(int i=1;i<=n;i++) fm[i][1]=fm[i-1][1]+f[i]*f[i-1];

    Build(1,1,n);
    while(m--){
        int op,l,r;
        cin>>op>>l>>r;
        if(op==1) Modify(1,l,r,1,0);
        else cout<<Query(1,l,r)<<endl;
    }

    return 0;
}