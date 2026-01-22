#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

inline bool DFS(vector<vector<char>> &v,int xl,int xr,int yl,int yr,bool cur){
	if(xl==xr&&yl==yr) return v[xl][yl]-'0'^cur;
	bool flag=1;
	if(xl!=xr){
		flag&=DFS(v,xl+1,xr,yl,yr,cur^1);
		flag&=DFS(v,xl,xr-1,yl,yr,cur^1);
	}
	if(yl!=yr){
		flag&=DFS(v,xl,xr,yl+1,yr,cur^1);
		flag&=DFS(v,xl,xr,yl,yr-1,cur^1);
	}
	return !flag;
}
inline bool Check(vector<vector<char>> &v){
	int n=v.size(),m=v.front().size();
	int x=max(0,(n-1)/2-1),y=max(0,(m-1)/2-1),lx=min(n,4-(n&1)),ly=min(m,4-(m&1));
	vector<vector<char>> t(lx,vector<char>(ly,0));
	for(int i=0;i<lx;i++) for(int j=0;j<ly;j++) t[i][j]=v[i+x][j+y];
	return DFS(t,0,lx-1,0,ly-1,0);
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--){
		int n,m;
		cin>>n>>m;
		vector<vector<char>> a(n,vector<char>(m,0));
		for(auto &v:a) for(char &c:v) cin>>c;
		if(Check(a)) cout<<"First"<<endl;
		else cout<<"Second"<<endl;
	}

	return 0;
}