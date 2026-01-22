#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=5e5+9;
const int inf=1e18;
using pii=pair<int,int>;

struct Data{
    pii x[2][2];
    pii* operator [](int pos){return x[pos];}
};
inline void ChMax(int &x,int y){if(y>x) x=y;}
inline void ChMin(int &x,int y){if(y<x) x=y;}
inline void AndAs(pii &x,pii y){ChMax(x.first,y.first),ChMin(x.second,y.second);}
inline pii And(pii x,pii y){return {max(x.first,y.first),min(x.second,y.second)};}
inline void OrAs(pii &x,pii y){ChMin(x.first,y.first),ChMax(x.second,y.second);}
inline pii Or(pii x,pii y){return {min(x.first,y.first),max(x.second,y.second)};}
inline void Reset(Data &x){x[0][0]=x[0][1]=x[1][0]=x[1][1]={inf,-inf};}
inline void Set(Data &x){x[0][0]=x[0][1]=x[1][0]=x[1][1]={-inf,inf};}
inline Data Merge(Data l,Data r,int p,int q){
    Data x;Reset(x);
    if(p<q){
        OrAs(x[0][0],And(l[0][0],r[0][0]));
        OrAs(x[1][0],And(l[1][0],r[0][0]));
        OrAs(x[0][1],And(l[0][0],r[0][1]));
        OrAs(x[1][1],And(l[1][0],r[0][1]));
    }else if(p>q){
        OrAs(x[0][0],And(l[0][1],r[1][0]));
        OrAs(x[1][0],And(l[1][1],r[1][0]));
        OrAs(x[0][1],And(l[0][1],r[1][1]));
        OrAs(x[1][1],And(l[1][1],r[1][1]));
    }
    OrAs(x[0][0],And(And(l[0][0],r[1][0]),make_pair(p+q,inf)));
    OrAs(x[1][0],And(And(l[1][0],r[1][0]),make_pair(p+q,inf)));
    OrAs(x[0][1],And(And(l[0][0],r[1][1]),make_pair(p+q,inf)));
    OrAs(x[1][1],And(And(l[1][0],r[1][1]),make_pair(p+q,inf)));
    OrAs(x[0][0],And(And(l[0][1],r[0][0]),make_pair(-inf,p+q)));
    OrAs(x[1][0],And(And(l[1][1],r[0][0]),make_pair(-inf,p+q)));
    OrAs(x[0][1],And(And(l[0][1],r[0][1]),make_pair(-inf,p+q)));
    OrAs(x[1][1],And(And(l[1][1],r[0][1]),make_pair(-inf,p+q)));
    return x;
}
inline bool Check(pii x){return x.first<x.second;}
inline bool Check(Data x){
    if(Check(x[0][0])) return 1;
    if(Check(x[1][0])) return 1;
    if(Check(x[0][1])) return 1;
    if(Check(x[1][1])) return 1;
    return 0;
}

struct Node{
    int l,r;
    Data dat;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat

int a[N],n;
void Build(int x,int l,int r){
    l(x)=l,r(x)=r;
    if(l(x)==r(x)){
        dat(x)[0][0]=dat(x)[1][1]={-inf,inf};
        dat(x)[1][0]=dat(x)[0][1]={inf,-inf};
        return ;
    }
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
    dat(x)=Merge(dat(x<<1),dat(x<<1|1),a[mid],a[mid+1]);
}
Data Query(int x,int l,int r){
    if(l<=l(x)&&r(x)<=r) return dat(x);
    int mid=l(x)+r(x)>>1;
    if(l<=mid&&r>mid) return Merge(Query(x<<1,l,r),Query(x<<1|1,l,r),a[mid],a[mid+1]);
    else if(l<=mid) return Query(x<<1,l,r);
    else return Query(x<<1|1,l,r);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    int ans=0;
    Build(1,1,n);
    for(int i=1,j=1;i<=n;i++){
        while(j<i&&!Check(Query(1,j,i))) ++j;
        ans+=i-j;
    }
    cout<<ans<<endl;

    return 0;
}