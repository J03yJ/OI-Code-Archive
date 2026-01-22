#include<bits/stdc++.h>

using namespace std;

const int N=3e3+9;

ifstream fin("ya.in");
ofstream fout("ya.out");
#define cin fin
#define cout fout

int a[N][N],c[N],n,m;
vector<int> g[N];
void DFS(int x){
    if(~c[x]){
        vector<int> tmp;
        for(int y:g[x]){
            if(c[y]) continue ;
            c[y]=-1;
            tmp.push_back(y);
        }
        for(int y:tmp) DFS(y);
    }else{
        for(int y:g[x]){
            if(c[y]) continue ;
            c[y]=1;
            DFS(y);
        }
    }
}

int main(){
    cin>>n>>m;
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        a[u][v]=a[v][u]=1;
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j) continue ;
            a[i][j]^=1;
            if(a[i][j]) g[i].push_back(j);
        }
    }

    srand(2333);
    while(true){
        int st=rand()%n+1;
        for(int i=st;i<=n;i++) if(!c[i]) c[i]=1,DFS(i);
        for(int i=1;i<st;i++) if(!c[i]) c[i]=1,DFS(i);
        
        int cnt=0;
        vector<int> ans;
        for(int i=1;i<=n;i++) if(c[i]==1) cnt++,ans.push_back(i);
        
        if(cnt>n/3){
            while(ans.size()>n/3) ans.pop_back();
            for(int x:ans) cout<<x<<' ';cout<<endl;
            break ;
        }else for(int i=1;i<=n;i++) c[i]=0;
    }

    return 0;
}