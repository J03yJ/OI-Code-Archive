#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+9;
int n;string s,t[N];
struct node{
	int fl;
	int sn[29];
	int ed;
	int c;
}tr[N];
int cnt;
int root=0;
int fi[N],ne[N],to[N],adj;
void adeg(int x,int y){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
}
int sz[N],mp[N];
void ins(string s,int x){
	int p=root;
	for(int i=0;i<s.size();i++){
		if(!tr[p].sn[s[i]-'a']){
			tr[p].sn[s[i]-'a']=++cnt;
			tr[cnt].c=s[i]-'a';
			p=cnt;
		}else p=tr[p].sn[s[i]-'a'];
//		cout<<p<<' ';
	}
//	cout<<endl;
	tr[p].ed++;
	mp[x]=p;
}
queue<int>q;
void ACpre(){
	for(int i=0;i<26;i++){
		if(tr[root].sn[i]){
			tr[tr[root].sn[i]].fl=root;
			q.push(tr[root].sn[i]);
		}
	}
	while(q.size()){
		int p=q.front();q.pop();
//		cout<<p<<endl;
		for(int i=0;i<26;i++){
			if(tr[p].sn[i]){
				tr[tr[p].sn[i]].fl=tr[tr[p].fl].sn[i];
//				cout<<char('a'+i)<<' '<<tr[tr[p].sn[i]].fl<<endl;
				q.push(tr[p].sn[i]);
			}else tr[p].sn[i]=tr[tr[p].fl].sn[i];
		}
//		cout<<endl;
	}
}
const int inf=1e9+7;
void calc(int x){
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		calc(y);
		sz[x]+=sz[y];
	}
//	cout<<x<<' '<<sz[x]<<endl;
}
void ACask(string s){
	int p=root,sum=0;
//	for(int i=0;i<s.size();i++){
//		p=tr[p].sn[s[i]-'a'];
//		for(int k=p;k&&tr[k].ed!=inf;k=tr[k].fl){
//			sum+=tr[k].ed;
//			tr[k].ed=inf;
//		}
//	}
	p=root;
	for(int i=0;i<s.size();i++){
		p=tr[p].sn[s[i]-'a'];
		sz[p]++;
//		cout<<p<<endl;
	}
	for(int i=1;i<=cnt;i++){
		adeg(tr[i].fl,i);
	}
	calc(root);
	for(int i=1;i<=n;i++) cout<<sz[mp[i]]<<endl;
}
//void cls(){
//	for(int i=1;i<=n;i++){
//		mp[i]=0;
//	}
//	for(int i=0;i<=cnt;i++){
//		tr[i].c=tr[i].ed=tr[i].fl=fi[i]=ne[i]=to[i]=sz[i]=0;
//		for(int j=0;j<26;j++) tr[i].sn[j]=0;
//	}
//	n=root=cnt=adj=0;
//	while(q.size()) q.pop();
//}
signed main(){
    cin>>s;
	cin>>n;
	if(!n) return 0;
	for(int i=1;i<=n;i++){
		cin>>t[i];
		ins(t[i],i);
	}
	ACpre();
	ACask(s);
//	for(int i=0;i<=cnt;i++){
//		cout<<i<<' '<<tr[i].c<<' '<<tr[i].ed<<' '<<tr[i].fl<<endl;
//		for(int j=0;j<26;j++) cout<<tr[i].sn[j]<<' ';
//		cout<<endl<<endl;
//	}
}