#include<bits/stdc++.h>
#include"haru.h"
using namespace std;
#define ll long long
namespace Interactive_Lib{
bool used_query;int cnt_query,cnt_guess,cnt_fail,max_query,max_guess;
vector<int> a,b,E[505];int n,T;ll dp[505],ans;bool vis[505];
void Wrong_Answer(int o){
	cout<<"Wrong Answer ["<<o<<"]"<<endl;
	exit(1);
}
void dfs(int u,int fa){
	vis[u]=true;dp[u]=a[u];
	for(int v:E[u]) if(v!=fa&&!vis[v]){
		dfs(v,u);ans=max(ans,dp[v]+dp[u]);dp[u]=max(dp[u],dp[v]+a[u]);
	}
}
vector<ll> query(const vector<vector<int>> &U,const vector<vector<int>> &V){
	if(used_query) Wrong_Answer(1);
	used_query=true;
	if(U.size()!=V.size()||U.size()>2000) Wrong_Answer(2);
	cnt_query=U.size();
	vector<ll> R(cnt_query);
	for(int t=0;t<cnt_query;t++){
		if(U[t].size()!=n-1||V[t].size()!=n-1) Wrong_Answer(3);
		for(int i=0;i<n;i++) E[i].clear(),vis[i]=false;
		for(int i=0;i<n-1;i++){
			if(U[t][i]<0||n<=U[t][i]||V[t][i]<0||n<=V[t][i]) Wrong_Answer(4);
			E[U[t][i]].push_back(V[t][i]);
			E[V[t][i]].push_back(U[t][i]);
		}
		ans=0;dfs(0,-1);
		for(int i=0;i<n;i++) if(!vis[i]) Wrong_Answer(5);
		R[t]=ans;
	}
	return R;
}
bool guess(const vector<int> &U,const vector<int> &V,ll x){
	if(++cnt_guess>2000) Wrong_Answer(6);
	if(U.size()!=n-1||V.size()!=n-1) Wrong_Answer(7);
	for(int i=0;i<n;i++) E[i].clear(),vis[i]=false;
	for(int i=0;i<n-1;i++){
		if(U[i]<0||n<=U[i]||V[i]<0||n<=V[i]) Wrong_Answer(8);
		E[U[i]].push_back(V[i]);
		E[V[i]].push_back(U[i]);
	}
	ans=0;dfs(0,-1);
	for(int i=0;i<n;i++) if(!vis[i]) Wrong_Answer(9);
	return ans==x;
}
void main(){
	cin>>T;max_query=0,max_guess=0;
	for(int i=1;i<=T;i++){
		used_query=cnt_query=cnt_guess=cnt_fail=0;
		cin>>n;
		a.resize(n);
		for(int i=0;i<n;i++) cin>>a[i];
		b=haru(n);
		if(b.size()!=n) Wrong_Answer(10);
		for(int i=0;i<n;i++){
			if(b[i]==-1) cnt_fail++;
			else if(a[i]!=b[i]) Wrong_Answer(11);
		}
		if(cnt_fail>2) Wrong_Answer(12);
		max_query=max(max_query,cnt_query);
		max_guess=max(max_guess,cnt_guess);
	}
	cout<<"AC with "<<max_query<<" query(s) and "<<max_guess<<" guess(es)."<<endl;
	return;
}
}
vector<ll> query(const vector<vector<int>> &U,const vector<vector<int>> &V){
	return Interactive_Lib::query(U,V);
}
bool guess(const vector<int> &U,const vector<int> &V,ll x){
	return Interactive_Lib::guess(U,V,x);
}
int main(){
	Interactive_Lib::main();
	return 0;
}