#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e6+9;
const int C=3;
const int mod=1e9+7;

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

int fac[N],ifac[N];
inline void Init(int lim){
	fac[0]=1;
	for(int i=1;i<=lim;i++) fac[i]=Mul(fac[i-1],i);
	ifac[lim]=Inv(fac[lim]);
	for(int i=lim-1;~i;i--) ifac[i]=Mul(ifac[i+1],i+1);
}

signed main(){
	int Tid,T;
	cin>>Tid>>T;
	while(T--){
		string s;
		cin>>s;

		char tot='a';
		map<char,char> mp;
		for(auto &c:s){
			if(!mp[c]) mp[c]=tot++;
			c=mp[c];
		}
		int T=tot-'a';

		if(T==1){
			cout<<"13"[s.size()==1]<<endl;
			continue ;
		}

		Init(s.size());
		int cnt[C][C],in[C],out[C];
		memset(in,0,sizeof in);
		memset(out,0,sizeof out);
		memset(cnt,0,sizeof cnt);
		for(int i=0;i+1<s.size();i++) cnt[s[i]-'a'][s[i+1]-'a']++;
		for(int i=0;i<T;i++) for(int j=0;j<T;j++) out[i]+=cnt[i][j],in[j]+=cnt[i][j];

		int st=-1,ed=-1;
		for(int i=0;i<T;i++){
			if(in[i]<out[i]) st=i;
			if(in[i]>out[i]) ed=i;
		}

		int ans=0;
		for(int p=0;p<T;p++){
			if(~st&&p!=ed) continue ;
			for(int q=0;q<T;q++){
				if(~ed&&q!=st) continue ;
				if(!~st&&p!=q) continue ;
				int res=1;
				cnt[p][q]++,out[p]++,in[q]++;
				for(int i=0;i<T;i++) MulAs(res,fac[max(out[i]-1,0)]);
				if(T==3) MulAs(res,Sub(Mul(Sub(out[0],cnt[0][0]),Sub(out[1],cnt[1][1])),Mul(cnt[0][1],cnt[1][0])));
				else if(T==2) MulAs(res,Sub(out[0],cnt[0][0]));
				cnt[p][q]--,out[p]--,in[q]--;
				AddAs(ans,res);
			}
		}
		for(int i=0;i<T;i++) for(int j=0;j<T;j++) MulAs(ans,ifac[cnt[i][j]]);

		cout<<ans<<endl;
	}

	return 0;
}