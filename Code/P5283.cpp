#include<bits/stdc++.h>

using namespace std;

#define int long long
#define fir(x) x.first
#define sec(x) x.second
using pii=pair<int,int>;
const int N=5e5+9;
const int lgV=32;

struct Node{
    int son[2],siz;
}tr[N<<6];
#define son(x,k) tr[x].son[k]
#define siz(x) tr[x].siz

int root[N],cnt;
inline int Allc(){return ++cnt;}
inline int Clone(int x){int y=Allc();tr[y]=tr[x];return y;}
inline void Insert(int &x,int dep,int k){
    x=Clone(x),siz(x)++;
    if(dep==-1) return ;
    Insert(son(x,k>>dep&1),dep-1,k);
}
inline int Query(int x,int dep,int k,int c){
    if(dep==-1) return 0;
    int flag=k>>dep&1;
    if(c<=siz(son(x,flag^1))) return Query(son(x,flag^1),dep-1,k,c)|(1ll<<dep);
    else return Query(son(x,flag),dep-1,k,c-siz(son(x,flag^1)));
}

int a[N],c[N],n,m;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];

    for(int i=1;i<=n;i++) a[i]^=a[i-1];
    for(int i=1;i<=n;i++) Insert(root[i]=root[i-1],lgV-1,a[i-1]);

    int ans=0;
    priority_queue<pii> q;
    for(int i=1;i<=n;i++) q.push({Query(root[i],lgV-1,a[i],++c[i]),i});
    while(m--){
        int x=sec(q.top());
        ans+=fir(q.top());
        q.pop();
        if(c[x]<n) q.push({Query(root[x],lgV-1,a[x],++c[x]),x});
    }

    cout<<ans<<endl;

    return 0;
}