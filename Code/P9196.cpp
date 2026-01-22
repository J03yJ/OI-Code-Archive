#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=4e6+9;

struct Node{
	int son[26],fail,ans;
}tr[N];
int cnt,root=0;
inline int Allc(){return ++cnt;}
inline int Insert(string &s){
	int u=root;
	for(int i=0;i<s.size();i++){
		int k=s[i]-'A';
		if(!tr[u].son[k]) tr[u].son[k]=Allc();
		u=tr[u].son[k];
	}
	return u;
}
inline void Build(){
	queue<int> q;
	for(int i=0;i<26;i++){
		if(!tr[root].son[i]) continue ;
		q.push(tr[root].son[i]);
		tr[tr[root].son[i]].fail=root;
	}
	while(q.size()){
		int x=q.front();
		q.pop();
		for(int i=0;i<26;i++){
			if(tr[x].son[i]){
				tr[tr[x].son[i]].fail=tr[tr[x].fail].son[i];
				q.push(tr[x].son[i]);
			}else tr[x].son[i]=tr[tr[x].fail].son[i];
		}
	}
}
inline void Modify(string &s){
	int u=root;
	for(int i=0;i<s.size();i++){
		int k=s[i]-'A';
		u=tr[u].son[k];
		tr[u].ans++;
	}
}
inline void Work(){
	queue<int> q;
	vector<int> d(cnt+1,0);
	for(int i=1;i<=cnt;i++) d[tr[i].fail]++;
	for(int i=1;i<=cnt;i++){
		if(d[i]) continue ;
		q.push(i);
	}
	while(q.size()){
		int x=q.front();
		q.pop();
		tr[tr[x].fail].ans+=tr[x].ans;
		if(!--d[tr[x].fail]) q.push(tr[x].fail);
	}
}

int id[N],n,m;
string s[N],t[N];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		s[i]=s[i]+"Z"+s[i];
	}
	for(int i=1;i<=m;i++){
		string p,q;
		cin>>p>>q;
		t[i]=q+"Z"+p;
		id[i]=Insert(t[i]);
	}

	Build();
	for(int i=1;i<=n;i++) Modify(s[i]);
	Work();

	for(int i=1;i<=m;i++) cout<<tr[id[i]].ans<<endl;

	return 0;
}