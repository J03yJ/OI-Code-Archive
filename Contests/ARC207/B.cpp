#include<bits/stdc++.h>

using namespace std;

const int N=2e2+9;

int n;
vector<int> e[N];

inline int Get(int u){
	vector<int> dep(n+1,0);
	dep[u]=1;
	queue<int> q;
	q.push(u);
	while(q.size()){
		int x=q.front();
		q.pop();
		for(int y:e[x]){
			if(dep[y]) continue ;
			dep[y]=dep[x]+1;
			if(dep[y]<=3) q.push(y);
		}
	}
	int sum=0;
	for(int i=1;i<=n;i++) if(dep[i]==2||dep[i]==3) sum+=i;
	return sum;
}
inline void Check(){
	vector<int> tmp;
	for(int i=1;i<=n;i++) tmp.push_back(Get(i)),cout<<i<<" : "<<tmp.back()<<endl;
	sort(tmp.begin(),tmp.end());
	if(tmp.front()!=tmp.back()) cout<<"dududu"<<endl;
}

signed main(){
	cin>>n;

	if(n<=5){
		cout<<-1<<endl;
		return 0;
	}

	vector<int> p;
	if(n%4==2){
		for(int i=1;i<=n/2;i++) p.push_back(i);
		for(int i=n;i>n/2;i--) p.push_back(i);
		for(int i=0;i<n;i++){
			for(int j=0;j<n/2;j++){
				int k=(i+1+j*2)%n;
				if(k==(i+n/2)%n) continue ;
				e[p[i]].push_back(p[k]);
				e[p[k]].push_back(p[i]);
			}
		}
	}else if(n%4==0){
		int m=n-2;
		for(int i=1;i<=n/2-1;i++) p.push_back(i);
		for(int i=n;i>n/2+1;i--) p.push_back(i);
		for(int i=0;i<m;i++){
			for(int j=0;j<m/2;j++){
				int k=(i+1+j*2)%m;
				if(k==(i+m/2)%m) continue ;
				e[p[i]].push_back(p[k]);
				e[p[k]].push_back(p[i]);
			}
		}
		for(int i=0;i<m;i+=2){
			e[p[i]].push_back(n/2);
			e[n/2].push_back(p[i]);
		}
		for(int i=1;i<m;i+=2){
			e[p[i]].push_back(n/2+1);
			e[n/2+1].push_back(p[i]);
		}
	}else if(n%4==3){
		int m=n-1;
		for(int i=1;i<=m/2;i++) p.push_back(i);
		for(int i=m;i>m/2;i--) p.push_back(i);
		for(int i=0;i<m;i++){
			for(int j=0;j<m/2;j++){
				int k=(i+1+j*2)%m;
				if(k==(i+m/2)%m) continue ;
				e[p[i]].push_back(p[k]);
				e[p[k]].push_back(p[i]);
			}
		}
		for(int i=0;i<m;i+=2){
			e[p[i]].push_back(n);
			e[n].push_back(p[i]);
		}
	}else if(n%4==1){
		int l=n-1,m=l-2;
		for(int i=1;i<=l/2-1;i++) p.push_back(i);
		for(int i=l;i>l/2+1;i--) p.push_back(i);
		for(int i=0;i<m;i++){
			for(int j=0;j<m/2;j++){
				int k=(i+1+j*2)%m;
				if(k==(i+m/2)%m) continue ;
				e[p[i]].push_back(p[k]);
				e[p[k]].push_back(p[i]);
			}
		}
		for(int i=0;i<m;i+=2){
			e[p[i]].push_back(l/2);
			e[l/2].push_back(p[i]);
		}
		for(int i=1;i<m;i+=2){
			e[p[i]].push_back(l/2+1);
			e[l/2+1].push_back(p[i]);
		}
		e[n].push_back(l/2);
		e[l/2].push_back(n);
		for(int i=1;i<m;i+=2){
			e[p[i]].push_back(n);
			e[n].push_back(p[i]);
		}
	}

	// Check();

	vector<array<int,2>> ans;
	for(int i=1;i<=n;i++){
		sort(e[i].begin(),e[i].end());
		e[i].erase(unique(e[i].begin(),e[i].end()),e[i].end());
		for(int j:e[i]) if(i<=j) ans.push_back({i,j});
	}

	cout<<ans.size()<<endl;
	for(auto t:ans) cout<<t[0]<<' '<<t[1]<<endl;

	return 0;
}