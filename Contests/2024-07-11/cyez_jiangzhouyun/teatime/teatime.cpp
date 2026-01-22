#include<bits/stdc++.h>
using namespace std;
#define int long long

ifstream fin("teatime.in");
ofstream fout("teatime.out");
#define cin fin
#define cout fout

const int N=5e3+9;
const int M=2e6+9;

int dis[N][N],vis[N][N],a[M];

signed main(){
    int p;
    cin>>p;
    for(int i=1;i<p;i++) cin>>a[i];
    
    int ans=0;
    // // if(p>5e3){
    //     queue<tuple<int,int,int>> q;
    //     for(int i=1;i<=(p-1)/2;i++) q.push(make_tuple(i,p-i,0));
    //     while(q.size()){
    //         int x=get<0>(q.front()),y=get<1>(q.front()),dis=get<2>(q.front());
    //         q.pop();
            
    //         int tmp=min(a[x],a[y]);
    //         ans+=dis*tmp;
    //         a[x]-=tmp;a[y]-=tmp;

    //         if(a[y]) q.push(make_tuple(x*2%p,y,dis+1));
    //         if(a[x]) q.push(make_tuple(x,y*2%p,dis+1));
    //     }
    // }else{
        queue<pair<int,int>> q;
        for(int i=1;i<=(p-1)/2;i++) q.push({i,p-i}),vis[i][p-i]=1;
        while(q.size()){
            int x=q.front().first,y=q.front().second;
            q.pop();
            
            int tmp=min(a[x],a[y]);
            ans+=dis[x][y]*tmp;
            a[x]-=tmp;a[y]-=tmp;

            if(!vis[x*2%p][y]){
                vis[x*2%p][y]=1;
                dis[x*2%p][y]=dis[x][y]+1;
                q.push({x*2%p,y});
            }
            if(!vis[x][y*2%p]){
                vis[x][y*2%p]=1;
                dis[x][y*2%p]=dis[x][y]+1;
                q.push({x,y*2%p});
            }
        }
    // }

    cout<<ans<<endl;

    return 0;
}