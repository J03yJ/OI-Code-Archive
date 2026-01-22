#include<bits/stdc++.h>

using namespace std;

ifstream fin("kangaroo.in");
ofstream fout("kangaroo.out");
#define cin fin
#define cout fout

#define vpii vector<pair<int,int>>
#define ssiz(x) (signed)x.size()
const int N=5e3+9;

int a[N][N],n,m;
int x[N],y[N],vis[N][N],tot;
vpii ok[N],ng[N],pre[N],suf[N];
void Find(int i,int dx,int dy){
    int xx=x[i]+dx,yy=y[i]+dy;
    if(xx<1||yy<1||xx>n||yy>m) return ;
    else if(vis[xx][yy]) return ;
    vis[xx][yy]=1;
    if(a[xx][yy]) return ;
    else ok[i].push_back({dx,dy});
    Find(i,dx-1,dy);
    Find(i,dx+1,dy);
    Find(i,dx,dy-1);
    Find(i,dx,dy+1);
}
void Not(vpii &p,vpii &q){
    map<pair<int,int>,int> mp;
    for(auto t:p) mp[t]=1;
    for(int i=-n;i<=n;i++){
        for(int j=-m;j<=m;j++){
            if(!mp[{i,j}]) q.push_back({i,j});
        }
    }
}
void Merge(vpii &a,vpii &b,vpii &c){
    for(int i=0,j=0;i<ssiz(a);i++){
        while(j<ssiz(b)&&b[j]<a[i]) j++;
        if(j<ssiz(b)&&b[j]==a[i]) c.push_back(b[j]);
    }
}
int main(){
    int T;
    cin>>T;
    while(T--){
        int ans=0;
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                char c;
                cin>>c;
                if(c=='.') a[i][j]=0,x[++tot]=i,y[tot]=j;
                else a[i][j]=1;
            }
        }
        for(int i=1;i<=tot;i++){
            Find(i,0,0);
            sort(ok[i].begin(),ok[i].end());
            Not(ok[i],ng[i]);
            for(int j=1;j<=n;j++){
                for(int k=1;k<=m;k++) vis[j][k]=0;
            }
        }
        for(int i=-n;i<=n;i++){
            for(int j=-m;j<=m;j++){
                if(a[i][j]) continue ;
                pre[0].push_back({i,j});
                suf[tot+1].push_back({i,j});
            }
        }
        for(int i=1;i<=tot;i++) Merge(pre[i-1],ng[i],pre[i]);
        for(int i=tot;i>=1;i--) Merge(suf[i+1],ng[i],suf[i]);
        for(int i=1;i<=tot;i++){
            vpii tmp1,tmp2;
            Merge(pre[i-1],suf[i+1],tmp1);
            Merge(tmp1,ok[i],tmp2);
            if(ssiz(tmp2)) ans++;
        }
        cout<<ans<<endl;

        for(int i=0;i<=tot+1;i++){
            pre[i].clear();
            suf[i].clear();
            ok[i].clear();
            ng[i].clear();
        }
        tot=0;
    }

    return 0;
}