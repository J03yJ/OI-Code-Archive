#include<bits/stdc++.h>

using namespace std;

ifstream fin("rain.in");
ofstream fout("rain.out");
#define cin fin
#define cout fout
#define endl '\n'

#define int long long
const int N=2e5+9;

int a[N],n,sum;
int pos[N],v[N],ans[N],q;

struct Node{
    int l,r,dat,mx,tag;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define len(x) (r(x)-l(x)+1)
#define dat(x) tr[x].dat
#define tag(x) tr[x].tag
#define mx(x) tr[x].mx

void Push(int x,int k){
    dat(x)=k*len(x);
    tag(x)=mx(x)=k;
}
void PushDown(int x){
    if(tag(x)==-1) return ;
    Push(x<<1,tag(x));
    Push(x<<1|1,tag(x));
    tag(x)=-1;
}
void PushUp(int x){
    dat(x)=dat(x<<1)+dat(x<<1|1);
    mx(x)=max(mx(x<<1),mx(x<<1|1));
}
void Build(int x,int l,int r){
    l(x)=l,r(x)=r,dat(x)=mx(x)=0,tag(x)=-1;
    if(l(x)==r(x)) return ;
    int mid=(l(x)+r(x))>>1;
    Build(x<<1,l,mid);
    Build(x<<1|1,mid+1,r);
}
void Assign(int x,int l,int r,int k){
    if(l>r) return ;
    if(l<=l(x)&&r(x)<=r) return Push(x,k);
    int mid=(l(x)+r(x))>>1;
    PushDown(x);
    if(l<=mid) Assign(x<<1,l,r,k);
    if(r>mid) Assign(x<<1|1,l,r,k);
    PushUp(x);
}
int Query(int x,int l,int r){
    if(l>r) return 0;
    if(l<=l(x)&&r(x)<=r) return dat(x);
    int mid=(l(x)+r(x))>>1,ans=0;
    PushDown(x);
    if(l<=mid) ans+=Query(x<<1,l,r);
    if(r>mid) ans+=Query(x<<1|1,l,r);
    return ans;
}
int Pre(int x,int k){
    if(l(x)==r(x)) return l(x);
    PushDown(x);
    if(mx(x<<1)>=k) return Pre(x<<1,k);
    else return Pre(x<<1|1,k);
}
int Suc(int x,int k){
    if(l(x)==r(x)) return l(x);
    PushDown(x);
    if(mx(x<<1|1)>=k) return Suc(x<<1|1,k);
    else return Suc(x<<1,k);
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        sum=0;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i],sum+=a[i];
        cin>>q;
        for(int i=1;i<=q;i++) cin>>pos[i]>>v[i],ans[i]=-(sum+=v[i]);

        int mxpos=0;
        Build(1,1,n);
        for(int i=1;i<=n;i++){
            if(a[i]>a[mxpos]) mxpos=i;
            Assign(1,i,Pre(1,a[i])-1,a[i]);
        }
        for(int i=1;i<=q;i++){
            a[pos[i]]+=v[i];
            if(a[pos[i]]>a[mxpos]) mxpos=pos[i];
            Assign(1,pos[i],Pre(1,a[pos[i]])-1,a[pos[i]]);
            ans[i]+=Query(1,1,mxpos-1);
            ans[i]+=a[mxpos];
        }
        for(int i=1;i<=q;i++) a[pos[i]]-=v[i];
        mxpos=0;
        Build(1,0,n+1);
        for(int i=1;i<=n;i++){
            if(a[i]>a[mxpos]) mxpos=i;
            Assign(1,Suc(1,a[i])+1,i,a[i]);
        }
        for(int i=1;i<=q;i++){
            a[pos[i]]+=v[i];
            if(a[pos[i]]>a[mxpos]) mxpos=pos[i];
            Assign(1,Suc(1,a[pos[i]])+1,pos[i],a[pos[i]]);
            ans[i]+=Query(1,mxpos+1,n);
        }

        for(int i=1;i<=q;i++) cout<<ans[i]<<endl;
    }

    return 0;
}