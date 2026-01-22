#include<bits/stdc++.h>

using namespace std;

const int N=4e5+9;

struct Node{
	int son[2];
}tr[N<<5];
#define son(x,k) tr[x].son[k]

int root,cnt;
inline int Allc(){return ++cnt;}
inline void Init(){root=Allc();}
inline void Clear(){while(cnt) memset(&tr[cnt--],0,sizeof Node());}
inline void Insert(int x){
	int u=root;
	for(int k=29;~k;k--){
		if(!son(u,x>>k&1)) son(u,x>>k&1)=Allc();
		u=son(u,x>>k&1);
	}
}
inline int Min(int x){
	int u=root,ans=0;
	for(int k=29;~k;k--){
		if(son(u,x>>k&1)) u=son(u,x>>k&1);
		else u=son(u,~x>>k&1),ans|=1<<k;
	}
	return ans;
}

inline int GetMin(vector<int> &a,vector<int> &b){
	int ans=INT_MAX;
	Init();
	for(int x:b) Insert(x);
	for(int x:a) ans=min(ans,Min(x));
	Clear();
	return ans;
}
inline int TryMax(vector<int> &v,int d){
	if(!v.size()||!~d) return 0;
	vector<int> s[2];
	for(int x:v) s[x>>d&1].push_back(x);
	if(s[0].size()&1) return GetMin(s[0],s[1]);
	else return max(TryMax(s[0],d-1),TryMax(s[1],d-1));
}

signed main(){
	int n;
	cin>>n;
	vector<int> a(n<<1);
	for(int &x:a) cin>>x;

	cout<<TryMax(a,29)<<endl;

	return 0;
}