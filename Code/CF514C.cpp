#include<bits/stdc++.h>
using namespace std;

#define int long long

const int base=5143;
const int p1=(unsigned)-1;
const int p2=998244353;
int qpow(int x,int y,int p){
	int m=1;
	while(y){
		if(y&1) m=x*x%p;
		x=x*x%p;
		y>>=1;
	}
	return m;
}
int hsh(string s,int p){
	int ans=0;
	for(int i=0;i<s.size();i++) ans=base*ans%p,ans+=s[i]-'a',ans%=p;
	return ans;
}
int chg(int ans,int c1,int c2,int pos,int p){
	return (ans+(c1-c2)*qpow(base,pos,p)%p+p)%p;
}

signed main(){
	int n,m;
	cin>>n>>m;
	map<pair<int,int>,int> mp;
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		int k1=hsh(s,p1),k2=hsh(s,p2);
		for(int j=0;j<s.size();j++){
			for(int k:{0,1,2}) mp[{chg(k1,k,s[j]-'a',j,p1),chg(k2,k,s[j]-'a',j,p2)}]=1;
		}
	}
	for(int i=1;i<=m;i++){
		string t;
		cin>>t;
		if(mp[{hsh(t,p1),hsh(t,p2)}]) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
}
