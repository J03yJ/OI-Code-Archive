#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;

int fi[N<<1],ne[N<<2],to[N<<2],adj;
inline void AddEdge(int x,int y){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
}

int a[N],v[N],n,m,s;
vector<vector<int>> cyc;
inline void DFS(int x){
	for(int &i=fi[x];i;){
		int y=to[i];
		i=ne[i];
		DFS(y);
	}
	if(x<=n) cyc.back().push_back(x);
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>s;
	for(int i=1;i<=n;i++) cin>>a[i];

	vector<int> val(a,a+n+1);
	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()),val.end());
	vector<int> cnt(val.size(),0);
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(val.begin(),val.end(),a[i])-val.begin();
		cnt[a[i]]++;
	}
	partial_sum(cnt.begin(),cnt.end(),cnt.begin());
	m=val.size()-1;
	for(int i=1;i<=n;i++){
		if(cnt[a[i]-1]<i&&i<=cnt[a[i]]) v[i]=1;
		else AddEdge(i,n+a[i]);
	}
	for(int i=1;i<=m;i++){
		for(int j=cnt[i-1]+1;j<=cnt[i];j++) if(!v[j]) AddEdge(n+i,j);
	}

	int t=0;
	for(int i=1;i<=n;i++){
		if(!fi[i]) continue ;
		cyc.push_back(vector<int>());
		DFS(i);
		reverse(cyc.back().begin(),cyc.back().end());
		cyc.back().pop_back();
		t+=cyc.back().size();
	}

	if(t>s){
		cout<<-1<<endl;
		return 0;
	}

	if(s<=t+1||cyc.size()<=2){
		cout<<cyc.size()<<endl;
		for(auto &v:cyc){
			cout<<v.size()<<endl;
			for(int x:v) cout<<x<<' ';cout<<endl;
		}
	}else{
		int k=min(s-t,(signed)cyc.size());
		cout<<cyc.size()-k+2<<endl;
		int sum=0;
		for(int i=0;i<k;i++) sum+=cyc[i].size();
		cout<<sum<<endl;
		for(int i=0;i<k;i++) for(int x:cyc[i]) cout<<x<<' ';cout<<endl;
		cout<<k<<endl;
		for(int i=k-1;~i;i--) cout<<cyc[i].front()<<' ';cout<<endl;
		for(int i=k;i<cyc.size();i++){
			cout<<cyc[i].size()<<endl;
			for(int x:cyc[i]) cout<<x<<' ';cout<<endl;
		}
	}

	return 0;
}