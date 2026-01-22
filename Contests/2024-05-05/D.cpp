#include<bits/stdc++.h>
using namespace std;
#define int long long

const int p=998244353;
int qpow(int x,int y){
	int m=1;
	while(y){
		if(y&1) m=m*x%p;
		x=x*x%p;
		y>>=1;
	}
	return m;
}

int P,Q,m;
int ans[30];
#define sback(x) (x[x.size()-2])
void F(vector<int> &v){
	while(v.size()>=2&&sback(v)==v.back()){
		int x=v.back();
		v.pop_back();v.pop_back();
		v.push_back(2*x);
	}
}
void dfs(vector<int> &v,int k,int pr){
//	cout<<k<<' '<<pr<<endl;
//	for(int x:v) cout<<x<<' ';cout<<endl;
	ans[v.size()]=(ans[v.size()]+pr*k%p)%p;
	if(v.size()==m) return ;
	vector<int> tmp=v;
	v.push_back(1),tmp.push_back(2);
	F(v),F(tmp);
	dfs(v,k+1,pr*P%p);
	dfs(tmp,k+2,pr*Q%p);
}

signed main(){
	int op,x,y;
	cin>>op>>m>>x>>y;
	P=qpow(y,p-2)*x%p;
	Q=(1-P+p)%p;
	vector<int> v;
	dfs(v,0,1);
	if(!op) cout<<ans[m]<<endl;
	else{
		for(int i=1;i<=m;i++) cout<<ans[i]<<' ';cout<<endl;
	}
}
