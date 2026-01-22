#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=4e6+9;
const int V=4e6;

struct Node{
    int l,r,siz;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define siz(x) tr[x].siz

inline void PushUp(int x){siz(x)=siz(x<<1)+siz(x<<1|1);}
inline void Build(int x,int l,int r){
    l(x)=l,r(x)=r;
    if(l(x)==r(x)) return siz(x)=1,void();
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
    PushUp(x);
}
inline void Set(int x,int pos,int k){
    if(l(x)==r(x)) return siz(x)=k,void();
    int mid=l(x)+r(x)>>1;
    if(pos<=mid) Set(x<<1,pos,k);
    else Set(x<<1|1,pos,k);
    PushUp(x);
}
inline int Kth(int x,int k){
    if(k>siz(x)) return -1;
    if(l(x)==r(x)) return l(x);
    if(k<=siz(x<<1)) return Kth(x<<1,k);
    else return Kth(x<<1|1,k-siz(x<<1));
}

int vis[N],q;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    Build(1,1,V);
    cin>>q;
    while(q--){
        int x,y;
        cin>>x>>y;
        if(x<=V&&!vis[x]){
            for(int i=x;i<=V;i+=x) if(!vis[i]) Set(1,i,0),vis[i]=1;
        }
        cout<<Kth(1,y)<<endl;
    }

    return 0;
}