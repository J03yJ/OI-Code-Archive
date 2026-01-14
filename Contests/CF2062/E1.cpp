#include<bits/stdc++.h>

using namespace std;

#define For(i,l,r) for(int i=(l);i<=(r);i++)
#define Rof(i,r,l) for(int i=(r);i>=(l);i--)
#define Rep(i,n) for(int i=0;i<(n);i++)
#define ssiz(x) (signed)x.size()
#define allc(x) x.begin(),x.end()
#define fir(x) x.first
#define sec(x) x.second
using ll=long long;
using ull=unsigned long long;
using pii=pair<int,int>;
template<class T1,class T2>void ChMin(T1 &x,T2 y){if(y<x) x=y;}
template<class T1,class T2>void ChMax(T1 &x,T2 y){if(y>x) x=y;}
template<class T>using svector=vector<vector<T>>;
template<class T>using cvector=vector<vector<vector<T>>>;

const int N=4e5+9;

int a[N],cnt[N],n;
vector<int> e[N],w[N];
int dfn[N],idfn[N],dcnt,fa[N],ed[N];
void DFS(int x){
    dfn[x]=++dcnt;
    idfn[dcnt]=x;
    for(int y:e[x]){
        if(y==fa[x]) continue ;
        fa[y]=x;
        DFS(y);
    }
    ed[x]=dcnt;
}

const int lgN=2e1;
void Insert(pii &x,int y){
    if(y>fir(x)) sec(x)=fir(x),fir(x)=y;
    else if(y>sec(x)&&y!=fir(x)) sec(x)=y;
}
pii Merge(pii x,pii y){
    Insert(x,fir(y)),Insert(x,sec(y));
    return x;
}
pii st[N][lgN];
int lg[N];
void Init(){
    For(i,2,n) lg[i]=lg[i>>1]+1;
    For(i,1,n) st[i][0]={a[idfn[i]],0};
    For(k,1,lg[n]){
        For(i,1,n) st[i][k]=Merge(st[i][k-1],st[i+(1<<k)][k-1]);
    }
}
pii Query(int l,int r){
    if(l>r) return {0,0};
    int k=lg[r-l+1];
    return Merge(st[l][k],st[r-(1<<k)+1][k]);
}
void Clear(){
    For(k,0,lg[n]) For(i,1,n) st[i][k]={0,0};
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    int T;
    cin>>T;
    while(T--){
        cin>>n;
        For(i,1,n) cin>>a[i],w[a[i]].push_back(i),cnt[a[i]]++;
        For(i,1,n-1){
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        DFS(1);

        Init();
        int ans=0;
        Rof(i,n,1){
            for(int x:w[i]){
                auto p=Merge(Query(1,dfn[x]-1),Query(ed[x]+1,n));
                // cout<<x<<" : "<<fir(p)<<' '<<sec(p)<<endl;
                if(fir(p)>i&&sec(p)<=i){
                    ans=x;
                    break ;
                }
            }
            if(ans) break ;
        }
        cout<<ans<<endl;

        dcnt=0;
        Clear();
        For(i,1,n){
            e[i].clear(),fa[i]=0,cnt[i]=0,w[i].clear();
        }
    }

    return 0;
}