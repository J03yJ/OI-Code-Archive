#include<bits/stdc++.h>

using namespace std;

ifstream fin("forest.in");
ofstream fout("forest.out");
#define cin fin
#define cout fout

#define int long long
const int N=1e6+9;
const int inf=1e18;

int fa[N],n,ans=inf;
vector<int> a[N],b[N];
int Find(int x){
    if(fa[x]==x) return x;
    else return fa[x]=Find(fa[x]);
}
void Merge(int x,int y,int p,int q){
    x=Find(x),y=Find(y);
    if(x==y) return ;
    fa[y]=x;
    for(int i=0;i<a[x].size();i++){
        for(int j=0;j<a[y].size();j++){
            ans=min(ans,abs((b[x][i]+b[y][j]+q))/(a[x][i]+a[y][j]+p));
        }
    }
    for(int i=0;i<a[y].size();i++) a[x].push_back(a[y][i]+p),b[x].push_back(b[y][i]+q);
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) a[i].push_back(0),b[i].push_back(0);
    iota(fa+1,fa+n+1,1);
    
    for(int i=1,u,v,a,b;i<n;i++){
        cin>>u>>v>>a>>b;
        Merge(v,u,a,b);
        cout<<ans<<endl;
    }

    return 0;
}