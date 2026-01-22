#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

int u1[N],v1[N],u2[N],v2[N],n,m1,m2,k;

inline int Get(vector<char> &a){
	int sum=0;
	for(int i=1;i<=m1;i++){
		if(a[u1[i]]=='C'&&a[v1[i]]=='C') sum+=2;
	}
	for(int i=1;i<=m2;i++){
		if(a[u2[i]]==a[v2[i]]){
			if(a[u2[i]]!='C') sum-=2;
		}else if(a[u2[i]]=='C'||a[v2[i]]=='C') sum-=1;
	}
	return sum;
}

int cnt;
inline void DFS1(int i,vector<char> &a){
	if(i>n){
		for(int i=1;i<=n;i++) cout<<a[i];cout<<endl;
		cnt++;
		return ;
	}
	if(a[i]=='?'){
		for(char c:{'A','B','C'}){
			a[i]=c;
			DFS1(i+1,a);
			a[i]='?';
			if(cnt>=k) return ;
		}
	}else DFS1(i+1,a);
}
int now=INT_MIN;
vector<int> res;
inline int Encode(vector<char> &a){
	int res=0;
	for(int i=n;i>=1;i--) res=res*3+a[i]-'A';
	return res;
}
inline void Decode(int x){
	for(int i=1;i<=n;i++){
		cout<<char(x%3+'A');
		x/=3;
	}
	cout<<endl;
}
inline void DFS2(int i,vector<char> &a){
	if(i>n){
		int cur=Get(a);
		if(cur>now) res.clear(),res.push_back(Encode(a)),now=cur;
		else if(cur==now&&res.size()<k) res.push_back(Encode(a));
		return ;
	}
	if(a[i]=='?'){
		for(char c:{'A','B','C'}){
			a[i]=c;
			DFS2(i+1,a);
			a[i]='?';
		}
	}else DFS2(i+1,a);
}

signed main(){
	cin>>n>>m1>>m2>>k;
	vector<char> a(n+1);
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m1;i++) cin>>u1[i]>>v1[i];
	for(int i=1;i<=m2;i++) cin>>u2[i]>>v2[i];
	
	if(!m1&&!m2){
		cout<<0<<endl;
		DFS1(1,a);
	}else if(n<=15){
		DFS2(1,a);
		cout<<now<<endl;
		for(auto v:res){
			Decode(v);
		}
	}else{
		for(int i=1;i<=n;i++) if(a[i]=='?') a[i]='C';

		cout<<Get(a)<<endl;
	}

	return 0;
}