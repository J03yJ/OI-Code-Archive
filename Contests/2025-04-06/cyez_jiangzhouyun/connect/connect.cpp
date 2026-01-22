#include<bits/stdc++.h>

using namespace std;

ifstream fin("connect.in");
ofstream fout("connect.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=(1<<20)+9;
const int lgN=2e1+9;

vector<int> msk[lgN];
int a[N],fa[N],pos[N],n;
inline int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
inline void Merge(int x,int y){fa[Find(y)]=Find(x);}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    int mx=0,lim=1;
    for(int i=1;i<=n;i++) mx=max(mx,a[i]);
    while(lim<=mx) lim<<=1;
    for(int i=0;i<lim;i++) msk[__builtin_popcount(i)].push_back(i);
    
    int cnt=0,ans=0;
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=n;i++){
        if(pos[a[i]]) Merge(pos[a[i]],i),cnt++;
        pos[a[i]]=i;
    }
    for(int k=1;k<lgN;k++){
        for(int i=1;i<=n;i++){
            if(pos[a[i]]!=i) continue ;
            for(int v:msk[k]){
                int j=pos[a[i]^v];
                if(!j) continue ;
                if(Find(i)==Find(j)) continue ;
                ans+=k;
                cnt++;
                Merge(i,j);
                if(cnt==n-1) break ;
            }
            if(cnt==n-1) break ;
        }
        if(cnt==n-1) break ;
    }

    cout<<ans<<endl;

    return 0;
}