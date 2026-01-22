#include<bits/stdc++.h>

using namespace std;

ifstream fin("inv.in");
ofstream fout("inv.out");
#define cin fin
#define cout fout

const int N=3e5+9;
const int lgN=40;
bool bg;

struct Node{
    int lc,rc,dat;
}tr[N*lgN];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define dat(x) tr[x].dat

int root[N],a[N],buc[N],n,c,cnt;
int Insert(int x,int L,int R,int k){
    int y=++cnt;
    tr[y]=tr[x];
    if(L==R){
        dat(y)++;
        return y;
    }
    int mid=(L+R)>>1;
    if(k<=mid) lc(y)=Insert(lc(x),L,mid,k);
    else rc(y)=Insert(rc(x),mid+1,R,k);
    dat(y)=dat(lc(y))+dat(rc(y));
    return y;
}
int Query(int x,int y,int L,int R,int l,int r){
    if(L>R) return 0;
    if(l<=L&&R<=r) return dat(y)-dat(x);
    int mid=(L+R)>>1,ans=0;
    if(l<=mid) ans+=Query(lc(x),lc(y),L,mid,l,r);
    if(r>mid) ans+=Query(rc(x),rc(y),mid+1,R,l,r);
    return ans;
}
#define Ask(l,r,L,R) Query(root[l-1],root[r],1,n,L,R)

struct DelHeap{
    priority_queue<long long> p,q;
    void Insert(long long x){p.push(x);}
    void Delete(long long x){q.push(x);}
    long long Top(){
        while(q.size()&&p.top()==q.top()) p.pop(),q.pop();
        return p.top();
    }
}ans;

struct Seg{
    int l,r;
    long long w;
    Seg(){}
    Seg(int _l,int _r,long long  _w){l=_l,r=_r,w=_w;}
    bool operator <(const Seg s)const{return l<s.l;}
};
set<Seg> s;
void Init(){
    long long cnt=0;
    for(int i=1;i<=n;i++) cnt+=Ask(1,i-1,a[i],n);
    s.insert(Seg(1,n,cnt));
    ans.Insert(cnt);
}
void Split(int pos){
    auto it=--s.upper_bound(Seg(pos+1,0,0));
    int l=it->l,r=it->r;
    long long tot=it->w,cntl=0,cntr=0;
    s.erase(it);
    ans.Delete(tot);

    tot-=Ask(l,pos-1,a[pos],n);
    tot-=Ask(pos+1,r,1,a[pos]);
    if(pos-l<r-pos){
        for(int i=l;i<pos;i++) tot-=Ask(pos+1,r,1,a[i]);
        for(int i=l;i<pos;i++) cntl+=Ask(l,i-1,a[i],n);
        cntr=tot-cntl;
    }else{
        for(int i=r;i>pos;i--) tot-=Ask(l,pos-1,a[i],n);
        for(int i=r;i>pos;i--) cntr+=Ask(i+1,r,1,a[i]);
        cntl=tot-cntr;
    }

    if(l<pos) s.insert(Seg(l,pos-1,cntl)),ans.Insert(cntl);
    if(r>pos) s.insert(Seg(pos+1,r,cntr)),ans.Insert(cntr);
}

bool ed;
int main(){
    cin>>n>>c;
    for(int i=1;i<=n;i++) cin>>a[i],buc[a[i]]++;
    for(int i=1;i<=n;i++) buc[i]+=buc[i-1];
    for(int i=n;i>=1;i--) a[i]=buc[a[i]]--;

    root[0]=++cnt;
    for(int i=1;i<=n;i++) root[i]=Insert(root[i-1],1,n,a[i]);
    Init();

    long long lst=0;
    for(int t=1,x;t<=n;t++){
        cout<<(lst=ans.Top())<<' ';
        cin>>x;
        x=(x+c*lst)%n+1;
        Split(x);
    }
    cout<<endl;

    return 0;
}