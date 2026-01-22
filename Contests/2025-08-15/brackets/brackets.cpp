#include<bits/stdc++.h>

using namespace std;

ifstream fin("brackets.in");
ofstream fout("brackets.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e6+9;
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

string s,t;
int lp[N],rp[N];
inline array<int,2> Divide(string &s,int id,int l,int r,vector<int> &b){
	if(l==r) return {id,id};
	if(b[l]==r) return Divide(s,id,l+1,r-1,b);
	int mid=s[l]=='1'?l:b[l];
	if(mid<l||r<=mid) assert(0);
	array<int,2> lans=Divide(s,id,l,mid,b);
	array<int,2> rans=Divide(s,lans[1]+1,mid+1,r,b);
	if(!lp[lans[1]]) lp[lans[1]]=lans[0];
	else lp[lans[1]]=max(lp[lans[1]],lans[0]);
	if(!rp[rans[0]]) rp[rans[0]]=rans[1];
	else rp[rans[0]]=min(rp[rans[0]],rans[1]);
	return {lans[0],rans[1]};
}
inline int Work(string &s){
	vector<int> b(s.size(),0),stk;
	for(int i=0;i<s.size();i++){
		if(s[i]=='(') stk.push_back(i);
		else if(s[i]==')'){
			int j=stk.back();
			stk.pop_back();
			b[i]=j,b[j]=i;
		}
	}
	return Divide(s,1,0,s.size()-1,b)[1];
}

signed main(){
	cin>>s>>t;

	int n=(Work(s),Work(t)),ans=1;
	for(int i=1;i<n;i++){
		int llen=i-lp[i]+1,rlen=rp[i+1]-(i+1)+1;
		MulAs(ans,Mul(llen,rlen));
	}

	cout<<ans<<endl;

	return 0;
}