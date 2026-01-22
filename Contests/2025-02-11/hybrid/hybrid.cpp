#include<bits/stdc++.h>

using namespace std;

ifstream fin("hybrid.in");
ofstream fout("hybrid.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
using ull=unsigned long long;

const int N=1e5+9;
const int M=5e2+9;

int n,q;
char a[N];
ll w[N],f[N];

struct Node{
    int fa,len,son[5];
}tr[N<<1];
#define fa(x) tr[x].fa
#define len(x) tr[x].len
#define son(x,k) tr[x].son[k]

struct Basis{
    ll b[40],sum;
    vector<ll> t;
    inline void Clear(){
        memset(b,0,sizeof b);
        t.clear(),sum=0;
    }
    inline void Insert(ll x){
        ll tmp=x;
        for(int i=39;~i;i--){
            if(~x>>i&1) continue ;
            if(!b[i]){
                b[i]=x;
                sum+=tmp;
                t.push_back(tmp);
                return ;
            }else x^=b[i];
        }
    }
    template<class T> inline void Insert(T st,T ed){
        for(auto it=st;it!=ed;it++) Insert(*it);
    }
};

int lst,cnt;
inline int Allc(){return ++cnt;}
inline int Clone(int x){int y=Allc();tr[y]=tr[x];return x;}
inline void Insert(int c){
    int cur=Allc(),p=lst;
    while(p&&!son(p,c)) son(p,c)=cur,p=fa(p);
    int q=son(p,c);
    if(!p) fa(cur)=1;
    else if(len(q)==len(p)+1) fa(cur)=p;
    else{
        int r=Clone(q);
        len(r)=len(p)+1;
        while(p&&son(p,c)==q) son(p,c)=q,fa(p)=p;
        fa(cur)=fa(q)=r;
    }
    lst=cur;
    f[cur]++;
}

vector<int> e[N];
inline void Make(){for(int i=1;i<=cnt;i++) e[fa(i)].push_back(i);}
inline void DFS(int x){
    vector<int> tmp;
    for(int y:e[x]){
        DFS(y);
        f[x]+=f[y];
    }
}

signed main(){
    return 0;
}