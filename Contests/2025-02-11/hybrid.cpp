#include<bits/stdc++.h>

using namespace std;

ifstream fin("hybrid.in");
ofstream fout("hybrid.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
using ull=unsigned long long;

const int N=2e5+9;
const int lgN=2e1;

int n,q;
char a[N];
ll w[N],f[N];

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
}b[N];

struct Node{
    int fa,len,son[5];
}tr[N];
#define fa(x) tr[x].fa
#define len(x) tr[x].len
#define son(x,k) tr[x].son[k]

int lst,cnt;
inline int Allc(){return ++cnt;}
inline int Clone(int x){int y=Allc();tr[y]=tr[x];return y;}
inline void Insert(int c){
    int cur=Allc(),p=lst;
    len(cur)=len(lst)+1;
    while(p&&!son(p,c)) son(p,c)=cur,p=fa(p);
    int q=son(p,c);
    if(!p) fa(cur)=1;
    else if(len(q)==len(p)+1) fa(cur)=q;
    else{
        int r=Clone(q);
        len(r)=len(p)+1;
        while(p&&son(p,c)==q) son(p,c)=r,p=fa(p);
        fa(cur)=fa(q)=r;
    }
    lst=cur;
    f[cur]++;
}

vector<int> e[N];
vector<int> pre;
inline void Make(){for(int i=1;i<=cnt;i++) e[fa(i)].push_back(i);}
inline void GetPrefix(){
    int p=1;
    pre.push_back(p);
    for(int i=1;i<=n;i++){
        p=son(p,a[i]-'a');
        pre.push_back(p);
    }
}
int anc[N][lgN];
inline void InitAnc(){
    for(int i=1;i<=cnt;i++) anc[i][0]=fa(i);
    for(int k=1;k<lgN;k++){
        for(int i=1;i<=cnt;i++) anc[i][k]=anc[anc[i][k-1]][k-1];
    }
}
inline void DFS(int x){
    vector<ll> tmp;
    for(int y:e[x]){
        DFS(y);
        f[x]+=f[y];
        for(ll val:b[y].t) tmp.push_back(val);
    }
    tmp.push_back(w[f[x]]);
    sort(tmp.begin(),tmp.end(),greater<ll>());
    b[x].Insert(tmp.begin(),tmp.end());
}
inline void Clear(){
    for(int i=1;i<=cnt;i++){
        b[i].Clear();
        e[i].clear();
        for(int c=0;c<5;c++) son(i,c)=0;
        fa(i)=len(i)=0;
        f[i]=0;
    }
    pre.clear();
    lst=cnt=0;
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        lst=Allc();
        for(int i=1;i<=n;i++) cin>>a[i],Insert(a[i]-'a');
        for(int i=1;i<=n;i++) cin>>w[i];
        Make();
        DFS(1);
        GetPrefix();
        InitAnc();

        cin>>q;
        while(q--){
            int l,r;
            cin>>l>>r;
            
            int p=pre[r];
            for(int k=lgN-1;~k;k--) if(len(anc[p][k])>=r-l+1) p=anc[p][k];
            cout<<b[p].sum<<endl;
        }

        Clear();
    }

    return 0;
}