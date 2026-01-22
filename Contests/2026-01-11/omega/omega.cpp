#include<bits/stdc++.h>

using namespace std;

ifstream fin("omega.in");
ofstream fout("omega.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
using Data=pair<ll,vector<int>>;
const int M=3e4+9;
const int K=10;
const ll inf=1e18;

ll l[M];
int m,n,k;
vector<int> s;
priority_queue<Data,vector<Data>,greater<Data>> L[M],R[M],Z[M],T;
inline ll F(ll x){return x*(x+1)/2;}
inline ll S(vector<int> &v){
	ll res=0;
	for(int x:v) res+=abs(x);
	return res;
}

signed main(){
	cin>>m>>n>>k,s.resize(k);
	for(int i=0;i<k;i++) cin>>s[i];
	for(int i=1;i<=m;i++) cin>>l[i];

	int tot=0;
	T.push({0,vector<int>(k-1,0)});
	map<vector<int>,bool> vis;
	vis[T.top().second]=1;
	for(int i=1;T.size()&&i<=m;i++){
		auto v=T.top().second;
		Z[T.top().first].push({0,v});
		T.pop();
		for(int j=0;j<k-1;j++){
			v[j]--;
			if(v[j]+s[j]>=1&&!vis[v]) T.push({S(v),v}),vis[v]=1;
			v[j]++;
			v[j]++;
			if(v[j]+s[j]<=n&&!vis[v]) T.push({S(v),v}),vis[v]=1;
			v[j]--;
		}
	}
	while(Z[tot].size()) tot++;
	tot--;
	
	for(int i=1;i<=m;i++){
		int p=-1;Data cur={inf,vector<int>()};char c='*';
		for(int j=0;j<=tot;j++){
			if(Z[j].size()){
				Data res=Z[j].top();
				if(s[k-1]-(l[i]>>1)>=1&&s[k-1]+(l[i]-1>>1)<=n) res.first=F(l[i]>>1)+F(l[i]-1>>1)+1ll*j*l[i];
				else if(s[k-1]+(l[i]-1>>1)<=n) res.first=F(s[k-1]-1)+F(l[i]-s[k-1])+1ll*j*l[i];
				else res.first=F(n-s[k-1])+F(l[i]-(n-s[k-1])-1)+1ll*j*l[i];
				if(res<cur) swap(cur,res),p=j,c='Z';
			}
			if(L[j].size()){
				Data res=L[j].top();
				if(s[k-1]-res.first-l[i]+1>=1){
					res.first=F(l[i]-1)+res.first*l[i]+1ll*j*l[i];
					if(res<cur) swap(cur,res),p=j,c='L';
				}
			}
			if(R[j].size()){
				Data res=R[j].top();
				if(s[k-1]+res.first+l[i]-1<=n){
					res.first=F(l[i]-1)+res.first*l[i]+1ll*j*l[i];
					if(res<cur) swap(cur,res),p=j,c='R';
				}
			}
		}
		if(c=='*') cout<<"Skip"<<endl;
		else{
			for(int j=0;j<k-1;j++) cout<<s[j]+cur.second[j]<<' ';
			if(c=='Z'){
				Z[p].pop();
				if(s[k-1]-(l[i]>>1)>=1&&s[k-1]+(l[i]-1>>1)<=n){
					cout<<s[k-1]-(l[i]>>1)<<endl;
					L[p].push({(l[i]>>1)+1,cur.second});
					R[p].push({(l[i]-1>>1)+1,cur.second});
				}else if(s[k-1]+(l[i]-1>>1)<=n){
					cout<<1<<endl;
					R[p].push({l[i]-s[k-1]+1,cur.second});
				}else{
					cout<<n-l[i]+1<<endl;
					L[i].push({l[i]-(n-s[k-1]),cur.second});
				}
			}else if(c=='L'){
				int t=L[p].top().first;
				L[p].pop();
				cout<<s[k-1]-t-l[i]+1<<endl;
				L[p].push({t+l[i],cur.second});
			}else if(c=='R'){
				int t=R[p].top().first;
				R[p].pop();
				cout<<s[k-1]+t<<endl;
				R[p].push({t+l[i],cur.second});
			}
		}
	}

	return 0;
}