#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;
const int lgN=2e1;

int a[N],s[N],pre[N][lgN],b[N],n,m;
int ql[N],qr[N],ans[N];
vector<int> q[N];

struct Node{
    int l,r,dat,tag;
}tr[N<<1];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
#define tag(x) tr[x].tag

void Push(int x,int k){dat(x)+=k,tag(x)+=k;}
void PushDown(int x){
    Push(x<<1,tag(x));
    Push(x<<1|1,tag(x));
    tag(x)=0;
}
void PushUp(int x){dat(x)=min(dat(x<<1),dat(x<<1|1));}
void Build(int x,int l,int r){
    l(x)=l,r(x)=r;
    if(l(x)==r(x)){
        dat(x)=s[l(x)];
        return ;
    }
    int mid=(l(x)+r(x))>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
    PushUp(x);
}
void Modify(int x,int l,int r,int k){
    if(l<=l(x)&&r(x)<=r) return Push(x,k);
    int mid=(l(x)+r(x))>>1;
    PushDown(x);
    if(l<=mid) Modify(x<<1,l,r,k);
    if(r>mid) Modify(x<<1|1,l,r,k);
    PushUp(x);
}
int Query(int x,int l,int r){
    if(l<=l(x)&&r(x)<=r) return dat(x);
    int mid=l(x)+r(x)>>1,ans=1e9;
    PushDown(x);
    if(l<=mid) ans=min(ans,Query(x<<1,l,r));
    if(r>mid) ans=min(ans,Query(x<<1|1,l,r));
    return ans;
}

int main(){
    cin>>n;
    for(int i=1,lst=0;i<=n;i++){
        char c;
        cin>>c;
        pre[i][0]=lst;
        if(c=='(') a[i]=1;
        else if(c==')') a[i]=-1;
        else a[i]=0,b[i]=1,lst=i;
        s[i]=s[i-1]+(a[i]?a[i]:1);
        b[i]+=b[i-1];
    }
    
    for(int k=1;k<lgN;k++){
        for(int i=1;i<=n;i++){
            pre[i][k]=pre[pre[i][k-1]][k-1];
        }
    }

    cin>>m;
    Build(1,0,n);
    for(int i=1;i<=m;i++){
        cin>>ql[i]>>qr[i];
        int tmp=s[qr[i]]-s[ql[i]-1],pos=qr[i];
        if(tmp&1) continue ;
        tmp>>=1;
        if(b[qr[i]]-b[ql[i]-1]<tmp) continue ;
        if(!a[pos]) tmp--;
        for(int k=lgN-1;~k;k--) if(tmp>>k&1) pos=pre[pos][k];
        if(!pos) continue ;
        q[pos].push_back(i);
    }

    for(int i=n;i>=1;i--){
        if(!a[i]) Modify(1,i,n,-2);
        for(int j:q[i]) ans[j]=Query(1,ql[j],qr[j])>=Query(1,ql[j]-1,ql[j]-1);
    }
    for(int i=1;i<=m;i++) cout<<(ans[i]?"Yes":"No")<<endl;

    return 0;
}