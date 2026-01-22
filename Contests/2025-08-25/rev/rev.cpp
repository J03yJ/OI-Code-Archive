#include<bits/stdc++.h>

using namespace std;

ifstream fin("rev.in");
ofstream fout("rev.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int mod=998244353;

inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int QPow(int x,int y){
	int res=1;
	while(y){
		if(y&1) MulAs(res,x);
		MulAs(x,x);
		y>>=1;
	}
	return res;
}
#define Inv(x) QPow(x,mod-2)

signed main(){
	int n,a,b;
	cin>>n>>a>>b;

	if(a==1&&b==1) cout<<1<<endl;
	else if(a==1||b==1) cout<<2<<endl;
	else{
		int ans=1;
		map<int,int> cnt;
		vector<int> p(n,0),vis(n,0),len;
		iota(p.begin(),p.end(),0);
		reverse(p.begin(),p.begin()+a);
		reverse(p.begin()+n-b,p.end());
		for(int i=0;i<n;i++){
			if(vis[i]) continue ;
			int cur=i,l=0;
			while(!vis[cur]){
				l++;
				vis[cur]=1;
				cur=p[cur];
			}
			len.push_back(l);
		}
		for(int x:len){
			for(int i=2;i*i<=x;i++){
				int c=0;
				while(!(x%i)) x/=i,c++;
				cnt[i]=max(cnt[i],c);
			}
			if(x!=1) cnt[x]=max(cnt[x],1);
		}
		for(auto p:cnt) MulAs(ans,QPow(p.first,p.second));
		cout<<Mul(2,ans)<<endl;
	}

	return 0;
}