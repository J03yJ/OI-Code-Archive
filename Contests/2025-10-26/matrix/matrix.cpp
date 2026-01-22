#include<bits/stdc++.h>

using namespace std;

ifstream fin("matrix.in");
ofstream fout("matrix.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=2e3+9;

char c[N][N];
int rs[N],cs[N],n,m;
vector<array<int,3>> ans;
inline void Init(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(c[i][j]=='1') rs[i]++,cs[j]++;
		}
	}
}
inline bool Judge(){
	int cnt=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) if(c[i][j]=='1') cnt++;
	}
	return cnt>=(n+m-1);
}
inline void RACw(int i,int j){
	ans.push_back({i,j,0});
	for(int x:{0,1}) for(int y:{0,1}) if(c[i+x][j+y]=='1') rs[i+x]--,cs[j+y]--;
	char s=c[i][j];
	c[i][j]=c[i][j+1];
	c[i][j+1]=c[i+1][j+1];
	c[i+1][j+1]=c[i+1][j];
	c[i+1][j]=s;
	for(int x:{0,1}) for(int y:{0,1}) if(c[i+x][j+y]=='1') rs[i+x]++,cs[j+y]++;
}
inline void RCw(int i,int j){
	ans.push_back({i,j,1});
	for(int x:{0,1}) for(int y:{0,1}) if(c[i+x][j+y]=='1') rs[i+x]--,cs[j+y]--;
	char s=c[i][j];
	c[i][j]=c[i+1][j];
	c[i+1][j]=c[i+1][j+1];
	c[i+1][j+1]=c[i][j+1];
	c[i][j+1]=s;
	for(int x:{0,1}) for(int y:{0,1}) if(c[i+x][j+y]=='1') rs[i+x]++,cs[j+y]++;
}
inline void Lu(int i,int j){return RCw(i-1,j-1);}
inline void Ld(int i,int j){return RACw(i,j-1);}
inline void Ru(int i,int j){return RACw(i-1,j);}
inline void Rd(int i,int j){return RCw(i,j);}
inline void Ul(int i,int j){return RACw(i-1,j-1);}
inline void Ur(int i,int j){return RCw(i-1,j);}
inline void Dl(int i,int j){return RCw(i,j-1);}
inline void Dr(int i,int j){return RACw(i,j);}
inline array<int,2> Find(){
	for(int j=2;j<=m;j++){
		if(cs[j]-(c[n][j]=='1')>0){
			for(int i=1;i<n;i++){
				if(c[i][j]=='1') return {i,j};
			}
			assert(0);
		}
	}
	for(int i=2;i<=n;i++){
		if(rs[i]-(c[1][i]=='1')>0){
			for(int j=2;j<=m;j++){
				if(c[i][j]=='1') return {i,j};
			}
			assert(0);
		}
	}
	return {-1,-1};
}
inline void Output(){
	cout<<ans.size()<<endl;
	for(auto t:ans) cout<<t[0]<<' '<<t[1]<<' '<<t[2]<<endl;
}
inline void Clear(){
	for(int i=1;i<=n;i++) rs[i]=0;
	for(int i=1;i<=m;i++) cs[i]=0;
	ans.clear();
}
inline void WorkC2(int i,int j,bool o){
	assert(j==2);
	int u=0,d=0;
	for(int t=i;t<=n;t++) if(c[t][1]=='1') d++;
	for(int t=1;t<=i;t++) if(c[t][1]=='1') u++;
	if(d<n-i+1||c[n][2]=='0'||o){
		while(i<n){
			Ld(i++,j);
			if(c[i][j]=='0') break ;
		}
	}else if(u<i){
		while(i>1){
			Lu(i--,j);
			if(c[i][j]=='0') break ;
		}
	}else assert(0);
	if(c[n-1][2]=='1'&&c[n][1]=='0'){
		RCw(n-1,1);
		RCw(n-1,1);
		return ;
	}
}
inline void WorkR2(int i,int j,bool o){
	assert(i==n-1);
	int l=0,r=0;
	for(int t=1;t<=j;t++) if(c[n][t]=='1') l++;
	for(int t=j;t<=m;t++) if(c[n][t]=='1') r++;
	if(l<j||c[n-1][1]=='0'||o){
		while(j>1){
			Dl(i,j--);
			if(c[i][j]=='0') break ;
		}
	}else if(r<m-j+1){
		while(j<m){
			Dr(i,j++);
			if(c[i][j]=='0') break ;
		}
	}else assert(0);
	if(c[n-1][2]=='1'&&c[n][1]=='0'){
		RCw(n-1,1);
		RCw(n-1,1);
		return ;
	}
}

inline void Solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>c[i][j];

	if(!Judge()){
		cout<<"NO"<<endl;
		Clear();
		return ;
	}else cout<<"YES"<<endl;
	if(n==1){
		Output();
		Clear();
		return ;
	}

	Init();
	
	while(rs[n]<m){
		auto t=Find();
		assert(~t[0]);
		int i=t[0],j=t[1];
		if(j==2){
			WorkC2(i,j,1);
			if(c[n-1][2]=='1') WorkR2(n-1,2,0);
		}else{
			while(i<n) Dl(i++,j);
			if(c[n-1][j-1]=='1') WorkR2(n-1,j-1,0);
		}
	}

	while(cs[1]<n){
		auto t=Find();
		assert(~t[0]);
		int i=t[0],j=t[1];
		if(i==n-1){
			WorkR2(i,j,1);
			if(c[n-1][2]=='1') WorkC2(n-1,2,0);
		}else{
			while(j>1) Ld(i,j--);
			if(c[i+1][2]=='1') WorkC2(i+1,2,0);
		}
	}

	Output();
	Clear();
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}