#include<bits/stdc++.h>
using namespace std;
#define int long long
 
//ifstream fin("firefly.in");
//ofstream fout("firefly.out");
//#define cin fin
//#define cout fout
 
const int N=4e5+9;
 
int U[N],V[N],Deg[N];
vector<int> G[N];
bitset<N> Vis;

int u[N],v[N],deg[N];
vector<int> g[N];
bitset<N> vis;
 
signed main(){
    int n,m,t;
    cin>>n>>m>>t;
    if(t==1){
        cout<<n<<endl;
    }else if(t==2){
        int cnt=0;
        map<pair<int,int>,bool> mp;
        for(int i=1;i<=m;i++){
            int x,y;
            cin>>x>>y;
            if(mp[{x,y}]) continue ;
            mp[{x,y}]=1;
            cnt++;
        }
        cout<<cnt<<endl;
    }else if(t==3){
        for(int i=1;i<=m;i++) cin>>U[i]>>V[i],Deg[U[i]]++,Deg[V[i]]++;
        for(int i=1;i<=m;i++){
            if(Deg[U[i]]<Deg[V[i]]||Deg[U[i]]==Deg[V[i]]&&U[i]<V[i]) G[U[i]].push_back(V[i]);
            else G[V[i]].push_back(U[i]);
        }
        int cnt=0;
        for(int x=1;x<=n;x++){
            for(int y:G[x]) Vis[y]=1;
            for(int y:G[x]){
                for(int z:G[y]) if(Vis[z]) cnt++;
            }
            for(int y:G[x]) Vis[y]=0;
        }
        cout<<cnt<<endl;
    }else{
    	for(int i=1;i<=m;i++) cin>>U[i]>>V[i],Deg[U[i]]++,Deg[V[i]]++;
        for(int i=1;i<=m;i++){
            if(Deg[U[i]]<Deg[V[i]]||Deg[U[i]]==Deg[V[i]]&&U[i]<V[i]) G[U[i]].push_back(V[i]);
            else G[V[i]].push_back(U[i]);
        }
        int cnt=0;
        for(int x=1;x<=n;x++){
        	int tot=0;
            for(int y:G[x]) Vis[y]=1;
            for(int y:G[x]){
                for(int z:G[y]){
                	if(Vis[z]){
                		u[++tot]=y;v[tot]=z;
                		deg[y]++;deg[z]++;
					}
				}
            }
            for(int y:G[x]) Vis[y]=0;
            
            for(int i=1;i<=tot;i++){
//            	cout<<u[i]<<' '<<v[i]<<endl;
	            if(deg[u[i]]<deg[v[i]]||deg[u[i]]==deg[v[i]]&&u[i]<v[i]) g[u[i]].push_back(v[i]);
	            else g[v[i]].push_back(u[i]);
	        }
	        for(int y:G[x]){
	        	for(int z:g[y]) vis[z]=1;
	        	for(int z:g[y]){
	        		for(int w:g[z]) if(vis[w]) cnt++;
				}
	        	for(int z:g[y]) vis[z]=0;
			}
            
            for(int y:G[x]) g[y].clear(),deg[y]=0;
//            cout<<endl;
        }
        cout<<cnt<<endl;
	}
    return 0;
}
