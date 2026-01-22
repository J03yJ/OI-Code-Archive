#include<bits/stdc++.h>

using namespace std;

ifstream fin("storage.in");
ofstream fout("storage.out");
#define cin fin
#define cout fout
#define endl '\n'

using uint=unsigned int;
const int N=5e5+9;
const int T=32;

struct Node{
    int lc,rc;
    uint dat,tag;
}tr[N<<2];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define dat(x) tr[x].dat
#define tag(x) tr[x].tag

int cnt;
inline void Clear(){while(cnt) lc(cnt)=rc(cnt)=dat(cnt)=tag(cnt)=0,cnt--;}
inline int Allc(){return ++cnt;}
inline int Clone(int x){int y=Allc();tr[y]=tr[x];return y;}
inline void PushUp(int x){dat(x)=dat(lc(x))+dat(rc(x));}
inline void Push(int &x,int L,int R,int k){
    x=Clone(x);
    dat(x)+=k*uint(R-L+1);
    tag(x)+=k;
}
inline void PushDown(int x,int L,int R){
    if(!tag(x)) return ;
    int mid=L+R>>1;
    Push(lc(x),L,mid,tag(x)),Push(rc(x),mid+1,R,tag(x));
    tag(x)=0;
}
inline void Modify(int &x,int L,int R,int l,int r,int k){
    if(l<=L&&R<=r) return Push(x,L,R,k);
    x=Clone(x);
    int mid=L+R>>1;
    PushDown(x,L,R);
    if(l<=mid) Modify(lc(x),L,mid,l,r,k);
    if(r>mid) Modify(rc(x),mid+1,R,l,r,k);
    PushUp(x);
}
inline void Copy(int &x,int y,int L,int R,int l,int r){
    x=Clone(x);
    if(l<=L&&R<=r) return tr[x]=tr[y],void();
    int mid=L+R>>1;
    PushDown(x,L,R),PushDown(y,L,R);
    if(l<=mid) Copy(lc(x),lc(y),L,mid,l,r);
    if(r>mid) Copy(rc(x),rc(y),mid+1,R,l,r);
    PushUp(x);
}
inline uint Query(int x,int L,int R,int l,int r){
    if(l<=L&&R<=r) return dat(x);
    int mid=L+R>>1;
    PushDown(x,L,R);
    if(l<=mid&&r>mid) return Query(lc(x),L,mid,l,r)+Query(rc(x),mid+1,R,l,r);
    else if(l<=mid) return Query(lc(x),L,mid,l,r);
    else return Query(rc(x),mid+1,R,l,r);
}
int root[N];
int op[N],ql[N],qr[N],qk[N],n,m;
uint ans[N];

signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>op[i];
        if(op[i]==1) cin>>ql[i]>>qr[i]>>qk[i];
        else if(op[i]==2) cin>>ql[i]>>qr[i];
        else if(op[i]==3) cin>>ql[i]>>qr[i]>>qk[i];
    }
    
    int B=ceil(double(n)/T);
    for(int l=1,r;l<=n;l=r+1){
        r=min(l+B-1,n);
        for(int i=1;i<=m;i++){
            root[i]=root[i-1];
            int ll=max(ql[i],l),rr=min(qr[i],r);
            if(ll>rr) continue ;
            if(op[i]==1) Modify(root[i],l,r,ll,rr,qk[i]);
            else if(op[i]==2) ans[i]+=Query(root[i],l,r,ll,rr);
            else if(op[i]==3) Copy(root[i],root[qk[i]],l,r,ll,rr);
        }
        Clear();
    }

    for(int i=1;i<=m;i++) if(op[i]==2) cout<<ans[i]<<endl;

    return 0;
}