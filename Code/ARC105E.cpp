#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1e5+9;

int fa[N],siz[N],n,m;
inline int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
inline void Merge(int x,int y){
    x=Find(x),y=Find(y);
    if(x==y) return ;
    fa[y]=x,siz[x]+=siz[y];
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;i++) fa[i]=i,siz[i]=1;
        for(int i=1,u,v;i<=m;i++) cin>>u>>v,Merge(u,v);
        int tmp=1ll*n*(n-1)/2&1;

        if(n&1){
            if((tmp^m)&1) cout<<"First"<<endl;
            else cout<<"Second"<<endl;
        }else{
            int x=Find(1),y=Find(n);
            if((siz[x]^siz[y])&1) cout<<"First"<<endl;
            else{
                if((tmp^m^siz[x])&1) cout<<"First"<<endl;
                else cout<<"Second"<<endl;
            }
        }
    }
    
    return 0;
}