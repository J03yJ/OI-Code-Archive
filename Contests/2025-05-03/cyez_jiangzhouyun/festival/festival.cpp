#include<bits/stdc++.h>

using namespace std;

ifstream fin("festival.in");
ofstream fout("festival.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=1e6+9;

struct Node{
    int l,r,dat;
    multiset<int> s;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
#define s(x) tr[x].s

inline void PushUp(int x){
    dat(x)=*s(x).rbegin();
    if(l(x)!=r(x)) dat(x)=max(dat(x),min(dat(x<<1),dat(x<<1|1)));
}
inline void Build(int x,int l,int r){
    l(x)=l,r(x)=r,s(x).insert(0);
    if(l(x)==r(x)) return PushUp(x);
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
    PushUp(x);
}
inline void Insert(int x,int l,int r,int k){
    if(l<=l(x)&&r(x)<=r) return s(x).insert(k),PushUp(x);
    int mid=l(x)+r(x)>>1;
    if(l<=mid) Insert(x<<1,l,r,k);
    if(r>mid) Insert(x<<1|1,l,r,k);
    PushUp(x);
}
inline void Erase(int x,int l,int r,int k){
    if(l<=l(x)&&r(x)<=r) return s(x).erase(k),PushUp(x);
    int mid=l(x)+r(x)>>1;
    if(l<=mid) Erase(x<<1,l,r,k);
    if(r>mid) Erase(x<<1|1,l,r,k);
    PushUp(x);
}
inline int Query(int x,int l,int r,int k=0){
    if(l<=l(x)&&r(x)<=r) return max(dat(x),k);
    int mid=l(x)+r(x)>>1;
    k=max(k,*s(x).rbegin());
    if(l<=mid&&mid<r) return min(Query(x<<1,l,r,k),Query(x<<1|1,l,r,k));
    else if(l<=mid) return Query(x<<1,l,r,k);
    else return Query(x<<1|1,l,r,k);
}

char op[N];
int a[N],b[N],k[N],id[N],q,tot;
vector<int> val;

signed main(){
    cin>>q;
    for(int i=1;i<=q;i++){
        cin>>op[i];
        if(op[i]=='+') cin>>a[i]>>b[i]>>k[i];
        else if(op[i]=='-') cin>>k[i];
        else if(op[i]=='?') cin>>a[i]>>b[i];
    }

    val.push_back(0);
    for(int i=1;i<=q;i++){
        if(op[i]=='+'||op[i]=='?'){
            assert(a[i]<b[i]);
            val.push_back(a[i]-1);
            val.push_back(a[i]);
            val.push_back(b[i]-1);
            val.push_back(b[i]);
        }
    }
    sort(val.begin(),val.end());
    val.erase(unique(val.begin(),val.end()),val.end());
    tot=val.size()-1;
    for(int i=1;i<=q;i++){
        if(op[i]=='+'||op[i]=='?'){
            a[i]=lower_bound(val.begin(),val.end(),a[i])-val.begin();
            b[i]=lower_bound(val.begin(),val.end(),b[i]-1)-val.begin();
        }
    }

    Build(1,1,tot);
    for(int i=1,cnt=0;i<=q;i++){
        if(op[i]=='+'){
            id[++cnt]=i;
            Insert(1,a[i],b[i],k[i]);
        }else if(op[i]=='-'){
            int j=id[k[i]];
            Erase(1,a[j],b[j],k[j]);
        }else if(op[i]=='?') cout<<Query(1,a[i],b[i])<<endl;
    }

    return 0;
}