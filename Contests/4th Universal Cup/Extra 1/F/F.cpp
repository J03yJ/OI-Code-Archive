#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
#define int ll
using ll=long long;
const int N=5e5+9;

int a[N],to[N],in[N],vis[N],typ[N],t[N],n;
vector<int> son[N];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>to[i];
	for(int i=1;i<=n;i++) cin>>a[i];
	
	queue<int> q;
	for(int i=1;i<=n;i++) in[to[i]]++;
	for(int i=1;i<=n;i++) if(!in[i]) q.push(i);
	while(q.size()){
		int x=q.front();
		q.pop();
		if(!--in[to[x]]) q.push(to[x]);
	}
	
	for(int i=1;i<=n;i++) typ[i]=a[i]<a[to[i]]?1:-1;
	for(int u=1;u<=n;u++){
		if(!in[u]){
			son[to[u]].push_back(u);
		}
	}
	for(int u=1;u<=n;u++){
		if(!in[u]) continue ;
		if(vis[u]) continue ;
		int x=u;
		vector<int> v;
		while(!vis[x]){
			vis[x]=1;
			v.push_back(x);
			x=to[x];
		}
		
		int lt=0,rt=1e9+7;
		while(lt+1<rt){
			int mid=lt+rt>>1;
			
			bool flag=0;
			for(int i:v){
				if(typ[i]==typ[to[i]]) continue ;
				if(abs(a[i]-a[to[i]])<=mid) flag|=1;
			}

			if(flag) rt=mid;
			else lt=mid;
		}

		int p=-1,m=v.size();
		for(int i=0;i<v.size();i++){
			int x=v[i];
			if(typ[x]==typ[to[x]]) continue ;
			if(abs(a[x]-a[to[x]])==rt) t[x]=rt,p=i;
		}
		assert(~p);
		for(int i=(p-1+m)%m;i!=p;i=(i-1+m)%m){
			int x=v[i];
			if(t[x]) continue ;
			if(typ[x]==typ[to[x]]){
				t[x]=t[to[x]]+2*abs(a[x]-a[to[x]]);
			}else{
				t[x]=abs(a[x]-a[to[x]]);
				if(t[x]>t[to[x]]){
					t[x]=t[to[x]]+2*abs(a[x]-(a[to[x]]+typ[to[x]]*t[to[x]]));
				}
			}
		}
		for(int x:v){
			for(int y:son[x]) q.push(y);
		}
	}

	while(q.size()){
		int x=q.front();
		q.pop();
		
		if(typ[x]==typ[to[x]]){
			t[x]=t[to[x]]+2*abs(a[x]-a[to[x]]);
		}else{
			t[x]=abs(a[x]-a[to[x]]);
			if(t[x]>t[to[x]]){
				t[x]=t[to[x]]+2*abs(a[x]-(a[to[x]]+typ[to[x]]*t[to[x]]));
			}
		}
		
		for(int y:son[x]) q.push(y);
	}

	for(int i=1;i<=n;i++) cout<<t[i]<<' ';cout<<endl;

	return 0;
}