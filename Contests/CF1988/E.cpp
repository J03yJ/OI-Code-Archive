#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e6+9;

namespace sgt1{
    struct node{
        int l,r,dat,tag;
    }tr[N<<2];
    #define l(x) tr[x].l
    #define r(x) tr[x].r
    #define dat(x) tr[x].dat
    #define tag(x) tr[x].tag
    #define len(x) (r(x)-l(x)+1)
    inline void pushup(int x){
        dat(x)=dat(x<<1)+dat(x<<1|1);
    }
    inline void pushdown(int x){
        dat(x<<1)+=tag(x)*len(x<<1);
        dat(x<<1|1)+=tag(x)*len(x<<1|1);
        tag(x<<1)+=tag(x);
        tag(x<<1|1)+=tag(x);
        tag(x)=0;
    }
    void build(int x,int l,int r){
        l(x)=l;r(x)=r;dat(x)=tag(x)=0;
        if(l(x)==r(x)) return ;
        int mid=l(x)+r(x)>>1;
        build(x<<1,l(x),mid);
        build(x<<1|1,mid+1,r(x));
        pushup(x);
    }
    void modify(int x,int l,int r,int k){
        if(l>r) return ;
        if(l<=l(x)&&r(x)<=r){
            dat(x)+=k*len(x);
            tag(x)+=k;
            return ;
        }
        pushdown(x);
        int mid=l(x)+r(x)>>1;
        if(l<=mid) modify(x<<1,l,r,k);
        if(r>mid) modify(x<<1|1,l,r,k);
        pushup(x);
    }
    int query(int x,int pos){
        if(l(x)==r(x)) return dat(x);
        pushdown(x);
        int mid=l(x)+r(x)>>1;
        if(pos<=mid) return query(x<<1,pos);
        else return query(x<<1|1,pos);
    }
}
namespace sgt2{
    // struct node{
    //     int l,r;
    //     pair<int,int> dat;
    // }tr[N<<2];
    // #define l(x) tr[x].l
    // #define r(x) tr[x].r
    // #define dat(x) tr[x].dat
    // void build(int x,int l,int r,int op){
    //     l(x)=l;r(x)=r;dat(x)={op,op};
    //     if(l(x)==r(x)) return ;
    //     int mid=l(x)+r(x)>>1;
    //     build(x<<1,l(x),mid,op);
    //     build(x<<1|1,mid+1,r(x),op);
    // }
    // pair<int,int> merge(pair<int,int> a,pair<int,int> b){
    //     if(a.first>b.first) return {a.first,max(a.second,b.first)};
    //     else return {b.first,max(a.first,b.second)};
    // }
    // void modify(int x,int pos,int k,int op){
    //     if(l(x)==r(x)){
    //         dat(x)={k,op};
    //         return ;
    //     }
    //     int mid=l(x)+r(x)>>1;
    //     if(pos<=mid) modify(x<<1,pos,k,op);
    //     else modify(x<<1|1,pos,k,op);
    //     dat(x)=merge(dat(x<<1),dat(x<<1|1));
    // }
    // pair<int,int> query(int x,int l,int r,int op){
    //     if(l<=l(x)&&r(x)<=r) return dat(x);
    //     pair<int,int> ans={op,op};
    //     int mid=l(x)+r(x)>>1;
    //     if(l<=mid) ans=merge(ans,query(x<<1,l,r,op));
    //     if(r>mid) ans=merge(ans,query(x<<1|1,l,r,op));
    //     return ans;
    // }

    pair<int,int> tr[N];
    void build(int n,int op){
        for(int i=1;i<=n;i++) tr[i]={op,op};
    }
    pair<int,int> merge(pair<int,int> a,pair<int,int> b){
        if(a.first>b.first) return {a.first,max(a.second,b.first)};
        else return {b.first,max(a.first,b.second)};
    }
    void modify(int pos,int n,int k,int op){
        pair<int,int> dat={k,op};
        while(pos<=n){
            tr[pos]=merge(tr[pos],dat);
            pos+=pos&-pos;
        }
    }
    pair<int,int> query(int pos,int op){
        pair<int,int> ans={op,op};
        while(pos){
            ans=merge(ans,tr[pos]);
            pos&=pos-1;
        }
        return ans;
    }
}

int a[N],lpre[N],rpre[N],l[N],r[N],lp[N],rp[N],A[N];
bool In(int l,int r,int pos){
    if(l>r) return 0;
    return l<=pos&&pos<=r;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        // for(int i=1;i<=n;i++) a[i]=i;
        // random_shuffle(a+1,a+n+1);

        // sgt2::build(1,1,n,0);
        sgt2::build(n,0);
        for(int i=1;i<=n;i++){
            // pair<int,int> p=sgt2::query(1,1,a[i],0);
            pair<int,int> p=sgt2::query(a[i],0);
            l[i]=p.first+1;
            lp[i]=p.second+1;
            lpre[i]=p.first;
            // sgt2::modify(1,a[i],i,0);
            sgt2::modify(a[i],n,i,0);
            // for(int j=1;j<=n;j++) cout<<sgt2::tr[j].first<<' ';cout<<endl;
        }
        // sgt2::build(1,1,n,-n-1);
        sgt2::build(n,-n-1);
        for(int i=n;i>=1;i--){
            // pair<int,int> p=sgt2::query(1,1,a[i],-n-1);
            pair<int,int> p=sgt2::query(a[i],-n-1);
            r[i]=-p.first-1;
            rp[i]=-p.second-1;
            rpre[i]=-p.first;
            // sgt2::modify(1,a[i],-i,-n-1);
            sgt2::modify(a[i],n,-i,-n-1);
        }

        // for(int i=1;i<=n;i++) cout<<l[i]<<' '<<r[i]<<' '<<lp[i]<<' '<<rp[i]<<endl;

        sgt1::build(1,1,n);
        for(int i=1;i<=n;i++) A[i]=0;
        for(int i=1;i<=n;i++){
            sgt1::modify(1,1,l[i]-1,(i-l[i]+1)*(r[i]-i+1)*a[i]);
            sgt1::modify(1,r[i]+1,n,(i-l[i]+1)*(r[i]-i+1)*a[i]);
            sgt1::modify(1,l[i],i-1,(i-l[i])*(r[i]-i+1)*a[i]);
            sgt1::modify(1,i+1,r[i],(i-l[i]+1)*(r[i]-i)*a[i]);
            if(In(1,n,lpre[i])){
                if(lp[i]!=l[i]){
                    int res=0;
                    if(In(1,l[i]-1,lpre[i])||In(r[i]+1,n,lpre[i])){
                        res+=-(i-l[i]+1)*(r[i]-i+1)*a[i];
                    }else if(In(l[i],i-1,lpre[i])){
                        res+=-(i-l[i])*(r[i]-i+1)*a[i];
                    }else if(In(i+1,r[i],lpre[i])){
                        res+=-(i-l[i]+1)*(r[i]-i)*a[i];
                    }
                    if(In(1,lp[i]-1,lpre[i])||In(r[i]+1,n,lpre[i])){
                        res+=(i-lp[i]+1)*(r[i]-i+1)*a[i];
                    }else if(In(lp[i],i-1,lpre[i])){
                        res+=(i-lp[i])*(r[i]-i+1)*a[i];
                    }else if(In(i+1,r[i],lpre[i])){
                        res+=(i-lp[i]+1)*(r[i]-i)*a[i];
                    }
                    A[lpre[i]]+=res;
                }
            }
            if(In(1,n,rpre[i])){
                if(rp[i]!=r[i]){
                    int res=0;
                    if(In(1,l[i]-1,rpre[i])||In(r[i]+1,n,rpre[i])){
                        res+=-(i-l[i]+1)*(r[i]-i+1)*a[i];
                    }else if(In(l[i],i-1,rpre[i])){
                        res+=-(i-l[i])*(r[i]-i+1)*a[i];
                    }else if(In(i+1,r[i],rpre[i])){
                        res+=-(i-l[i]+1)*(r[i]-i)*a[i];
                    }
                    if(In(1,l[i]-1,rpre[i])||In(rp[i]+1,n,rpre[i])){
                        res+=(i-l[i]+1)*(rp[i]-i+1)*a[i];
                    }else if(In(l[i],i-1,rpre[i])){
                        res+=(i-l[i])*(rp[i]-i+1)*a[i];
                    }else if(In(i+1,rp[i],rpre[i])){
                        res+=(i-l[i]+1)*(rp[i]-i)*a[i];
                    }
                    A[rpre[i]]+=res;
                }
            }
        }

        for(int i=1;i<=n;i++) cout<<sgt1::query(1,i)+A[i]<<' ';cout<<endl;
    }
    return 0;
}