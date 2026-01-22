#include<bits/stdc++.h>

using namespace std;

const int N=2e6+9;

struct Node{
    int mx,mn;
}tr[N<<2];
#define mx(x) tr[x].mx
#define mn(x) tr[x].mn

inline void PushUp(int x){
    mx(x)=max(mx(x<<1),mx(x<<1|1));
    mn(x)=min(mn(x<<1),mn(x<<1|1));
}
inline void Build(int x,int L,int R){
    mx(x)=0,mn(x)=1e9;
    if(L==R) return ;
    int mid=L+R>>1;
    Build(x<<1,L,mid),Build(x<<1|1,mid+1,R);
}
inline void Modify(int x,int L,int R,int pos,int k){
    if(L==R) return mx(x)=mn(x)=k,void();
    int mid=L+R>>1;
    if(pos<=mid) Modify(x<<1,L,mid,pos,k);
    else Modify(x<<1|1,mid+1,R,pos,k);
    PushUp(x);
}
inline int Max(int x,int L,int R,int l,int r){
    if(l<=L&&R<=r) return mx(x);
    int mid=L+R>>1;
    if(l<=mid&&r>mid) return max(Max(x<<1,L,mid,l,r),Max(x<<1|1,mid+1,R,l,r));
    else if(l<=mid) return Max(x<<1,L,mid,l,r);
    else return Max(x<<1|1,mid+1,R,l,r);
}
inline int Min(int x,int L,int R,int l,int r){
    if(l<=L&&R<=r) return mn(x);
    int mid=L+R>>1;
    if(l<=mid&&r>mid) return min(Min(x<<1,L,mid,l,r),Min(x<<1|1,mid+1,R,l,r));
    else if(l<=mid) return Min(x<<1,L,mid,l,r);
    else return Min(x<<1|1,mid+1,R,l,r);
}

int a[N],pre[N],suc[N],buc[N],n;
int ql[N],qr[N],ans[N],p[N],q;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i];

    for(int i=1;i<=2e6;i++) buc[a[i]]=0;
    for(int i=1;i<=n;i++){
        pre[i]=buc[a[i]];
        buc[a[i]]=i;
    }
    for(int i=1;i<=2e6;i++) buc[a[i]]=n+1;
    for(int i=n;i>=1;i--){
        suc[i]=buc[a[i]];
        buc[a[i]]=i;
    }
    for(int i=1;i<=q;i++) p[i]=i;
    
    Build(1,0,n+1);
    sort(p+1,p+q+1,[](int i,int j){return qr[i]<qr[j];});
    for(int i=1,j=1;i<=n;i++){
        Modify(1,0,n+1,pre[i],i-pre[i]-1);
        while(j<=q&&qr[p[j]]==i){
            ans[p[j]]=max(ans[p[j]],Max(1,0,n+1,ql[p[j]],qr[p[j]]));
            j++;
        }
    }
    Build(1,0,n+1);
    sort(p+1,p+q+1,[](int i,int j){return qr[i]<qr[j];});
    for(int i=1,j=1;i<=n;i++){
        Modify(1,0,n+1,pre[i],i);
        while(j<=q&&qr[p[j]]==i){
            ans[p[j]]=max(ans[p[j]],Max(1,0,n+1,0,ql[p[j]]-1)-ql[p[j]]);
            j++;
        }
    }
    Build(1,0,n+1);
    sort(p+1,p+q+1,[](int i,int j){return ql[i]>ql[j];});
    for(int i=n,j=1;i>=1;i--){
        Modify(1,0,n+1,suc[i],i);
        while(j<=q&&ql[p[j]]==i){
            ans[p[j]]=max(ans[p[j]],qr[p[j]]-Min(1,0,n+1,qr[p[j]]+1,n+1));
            j++;
        }
    }

    for(int i=1;i<=q;i++) cout<<ans[i]<<endl;
    
    return 0;
}