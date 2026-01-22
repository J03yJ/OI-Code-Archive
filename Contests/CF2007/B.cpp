#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

struct Node{
    int l,r,dat,tag;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
#define tag(x) tr[x].tag

void PushUp(int x){
    dat(x)=max(dat(x<<1),dat(x<<1|1));
}
void Push(int x,int k){
    tag(x)+=k;
    dat(x)+=k;
}
void PushDown(int x){
    Push(x<<1,tag(x));
    Push(x<<1|1,tag(x));
    tag(x)=0;
}

int a[N],val[N],id[N],cnt;
void Build(int x,int l,int r){
    l(x)=l;r(x)=r;
    tag(x)=dat(x)=0;
    if(l(x)==r(x)){
        dat(x)=val[l(x)];
        return ;
    }
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid);
    Build(x<<1|1,mid+1,r);
    PushUp(x);
}
void Modify(int x,int l,int r,int k){
    if(l<=l(x)&&r(x)<=r) return Push(x,k);
    PushDown(x);
    int mid=l(x)+r(x)>>1;
    if(l<=mid) Modify(x<<1,l,r,k);
    if(r>mid) Modify(x<<1|1,l,r,k);
    PushUp(x);
}
int Query(int x,int k){
    if(l(x)==r(x)){
        // cout<<l(x)<<' '<<r(x)<<' '<<k<<' '<<dat(x)<<endl;
        if(k<dat(x)) return l(x)-1;
        else return l(x);
    }
    PushDown(x);
    if(k<dat(x<<1)) return Query(x<<1,k);
    else return Query(x<<1|1,k);
}
int VQuery(int x,int pos){
    if(l(x)==r(x)) return dat(x);
    int mid=l(x)+r(x)>>1;
    PushDown(x);
    if(pos<=mid) return VQuery(x<<1,pos);
    else return VQuery(x<<1|1,pos);
}

int main(){
    int T;
    cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m;
        for(int i=1;i<=n;i++) cin>>a[i],val[i]=a[i];
        sort(val+1,val+n+1);
        cnt=unique(val+1,val+n+1)-val-1;
        val[0]=0,val[cnt+1]=2e9;
        Build(1,0,cnt+1);

        while(m--){
            char c;
            cin>>c;
            int l,r;
            cin>>l>>r;
            int posl=Query(1,l-1);
            int posr=Query(1,r);
            if(posl<posr){
                if(c=='-') Modify(1,posl+1,posr,-1);
                if(c=='+') Modify(1,posl+1,posr,1); 
            }
            // for(int i=1;i<=cnt;i++) cout<<VQuery(1,i)<<' ';cout<<endl;
            cout<<VQuery(1,cnt)<<' ';
        }
        cout<<endl;
    }

    return 0;
}