#include<bits/stdc++.h>

using namespace std;

ifstream fin("wennuan.in");
ofstream fout("wennuan.out");
#define cin fin
#define cout fout
#define endl '\n'

#define fir(x) x.first
#define sec(x) x.second
using pii=pair<int,int>;
const int N=1e3+9;

#define Next(x) ((x)%n+1)
#define Prev(x) ((x)==1?n:(x)-1)
int a[N][N],b[N][N],ad[N],bd[N],n;
inline bool Link(int a[N][N],int u,int v){
    if(u>v) swap(u,v);
    if(v-u==1||v==n&&u==1) return 1;
    return a[u][v];
}
inline pii Find(int a[N][N],int x,int y){
    pii res={0,0};
    for(int i=1;i<=n;i++){
        if(i==x||i==y) continue ;
        if(Link(a,i,x)&&Link(a,i,y)){
            if(fir(res)) sec(res)=i;
            else fir(res)=i;
        }
    }
    return res;
}
inline void Modify(int a[N][N],int *d,int x,int y,vector<array<int,4>> &ans){
    pii res=Find(a,x,y);
    int u=fir(res),v=sec(res);
    a[x][y]=a[y][x]=0,d[x]--,d[y]--;
    a[u][v]=a[v][u]=1,d[u]++,d[v]++;
    ans.push_back({x,y,u,v});
}

signed main(){
    cin>>n;
    for(int i=1,u,v;i<=n-3;i++){
        cin>>u>>v;
        a[u][v]=a[v][u]=1;
        ad[u]++,ad[v]++;
    }
    for(int i=1,u,v;i<=n-3;i++){
        cin>>u>>v;
        b[u][v]=b[v][u]=1;
        bd[u]++,bd[v]++;
    }

    vector<array<int,4>> ans;
    while(true){
        if(!ad[1]) Modify(a,ad,Prev(1),Next(1),ans);
        else{
            int u=0,v=0;
            for(int i=1;i<=n;i++){
                if(a[1][i]&&ad[i]>1){
                    u=i;
                    break ;
                }
            }
            if(!u) break ;
            for(int i=2;i<=n;i++){
                if(a[u][i]&&Link(a,1,i)){
                    v=i;
                    break ;
                }
            }
            Modify(a,ad,u,v,ans);
        }
    }
    vector<array<int,4>> bns;
    while(true){
        if(!bd[1]) Modify(b,bd,Prev(1),Next(1),bns);
        else{
            int u=0,v=0;
            for(int i=1;i<=n;i++){
                if(b[1][i]&&bd[i]>1){
                    u=i;
                    break ;
                }
            }
            if(!u) break ;
            for(int i=2;i<=n;i++){
                if(b[u][i]&&Link(b,1,i)){
                    v=i;
                    break ;
                }
            }
            Modify(b,bd,u,v,bns);
        }
    }
    reverse(bns.begin(),bns.end());
    cout<<ans.size()+bns.size()<<endl;
    for(auto t:ans) cout<<t[0]<<' '<<t[1]<<endl;
    for(auto t:bns) cout<<t[2]<<' '<<t[3]<<endl;

    return 0;
}