#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;

vector<int> e[N];
int a[N],b[N],c[N],d[N],n,m;

int o[N];
inline bool Try(int p,int k){
	if(~o[p]) return o[p]==k;
	vector<int> node;
	queue<int> q;
	o[p]=k;
	q.push(p);
	node.push_back(p);
	while(q.size()){
		int x=q.front();
		q.pop();
		for(int i:e[x]){
			int y=a[i]^b[i]^x,w=o[x]^c[i];
			if(~o[y]){
				if(o[y]!=w){
					for(int z:node) o[z]=-1;
					return 0;
				}
			}else{
				o[y]=w;
				q.push(y);
				node.push_back(y);
			}
		}
	}
	return 1;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a[i]>>b[i]>>c[i];
		d[a[i]]++,d[b[i]]++;
	}

	for(int i=1;i<=n;i++) if(d[i]==3) o[i]=-1;
	for(int i=1;i<=m;i++){
		if(c[i]==1&&d[a[i]]<3&&d[b[i]]<3){
			cout<<-1<<endl;
			return 0;
		}
		if(d[a[i]]==3&&d[b[i]]==3){
			e[a[i]].push_back(i);
			e[b[i]].push_back(i);
		}
	}
	for(int i=1;i<=m;i++){
		if(d[a[i]]==3&&d[b[i]]<3){
			if(!Try(a[i],c[i])){
				cout<<-1<<endl;
				return 0;
			}
		}else if(d[a[i]]<3&&d[b[i]]==3){
			if(!Try(b[i],c[i])){
				cout<<-1<<endl;
				return 0;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(!~o[i]){
			if(!Try(i,0)&&!Try(i,1)){
				cout<<-1<<endl;
				return 0;
			}
		}
	}

	for(int i=1;i<=n;i++) e[i].clear();
	for(int i=1;i<=m;i++){
		c[i]^=o[a[i]]^o[b[i]];
		e[a[i]].push_back(i);
		e[b[i]].push_back(i);
	}

	vector<array<int,3>> ans;
	for(int i=1;i<=n;i++){
		if(o[i]){
			ans.push_back({e[i][0],e[i][1],e[i][2]});
		}
	}
	for(int i=1;i<=n;i++){
		if(d[i]<4) continue ;
		int r=e[i].size();
		for(int j=0;j<r;j++){
			if(c[e[i][j]]){
				for(int p:{1,2,3}){
					int q=p%3+1;
					ans.push_back({e[i][j],e[i][(j+p)%r],e[i][(j+q)%r]});
				}
				c[e[i][j]]=0;
			}
		}
	}

	cout<<ans.size()<<endl;
	for(auto p:ans) cout<<p[0]<<' '<<p[1]<<' '<<p[2]<<endl;

	return 0;
}