#include<bits/stdc++.h>
 
using namespace std;
 
#define endl '\n'
using ll=long long;
const int N=3e5+9;
const int lgN=20;

map<string,int> id;
string s[N],t[N];
int prio[N],val[N],a[N],v[N],pos[N],ql[N],qr[N],n,m,q;
ll ans[N],cur[N];
vector<int> lq[N],rq[N];
 
int mxp[N][lgN],lg[N];
inline int Cmp(int i,int j){
	if(a[i]^a[j]) return a[i]<a[j]?j:i;
	else return i<j?i:j;
}
inline void Init(){
	lg[0]=-1;
	for(int i=1;i<=n;i++) lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;i++) mxp[i][0]=i;
	for(int k=1;k<=lg[n];k++){
		for(int i=1;i<=n-(1<<k)+1;i++) mxp[i][k]=Cmp(mxp[i][k-1],mxp[i+(1<<k-1)][k-1]);
	}
}
inline int MaxPos(int l,int r){
	int k=lg[r-l+1];
	return Cmp(mxp[l][k],mxp[r-(1<<k)+1][k]);
}

ll tr[N];
inline void Add(int x,ll k){while(x<=n) tr[x]+=k,x+=x&-x;}
inline ll Ask(int x){ll sum=0;while(x) sum+=tr[x],x&=x-1;return sum;}
inline ll Ask(int l,int r){return Ask(r)-Ask(l-1);}
inline ll F(int x){return x&1?-1:1;}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
 
	cin>>m>>n>>q;
	for(int i=1;i<=m;i++) cin>>prio[i]>>val[i]>>s[i];
	for(int i=1;i<=n;i++) cin>>t[i];
	for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i];

	for(int i=1;i<=m;i++) id[s[i]]=i;
	for(int i=1;i<=n;i++) a[i]=prio[id[t[i]]],v[i]=val[id[t[i]]];
 
	Init();
	for(int i=1;i<=q;i++){
		if(ql[i]>qr[i]) continue ;
		pos[i]=MaxPos(ql[i],qr[i]);
		ans[i]=v[pos[i]];
		lq[ql[i]].push_back(i);
		rq[qr[i]].push_back(i);
	}
	
	vector<int> stk;
	for(int i=1;i<=n;i++){
		int lst=0;
		while(stk.size()&&Cmp(stk.back(),i)==i){
			Add(stk.size(),-cur[stk.back()]);
			cur[stk.back()]+=cur[lst];
			lst=stk.back();
			stk.pop_back();
		}
		cur[i]=v[i]-cur[lst];
		stk.push_back(i);
		Add(stk.size(),cur[i]);
		for(int j:rq[i]){
			int p=lower_bound(stk.begin(),stk.end(),pos[j])-stk.begin()+1;
			ans[j]+=Ask(p+1,n);
		}
	}

	stk.clear();
	for(int i=1;i<=n;i++) cur[i]=0;
	for(int i=1;i<=n;i++) tr[i]=0;

	for(int i=n;i>=1;i--){
		int lst=0;
		while(stk.size()&&Cmp(stk.back(),i)==i){
			Add(stk.size(),-(cur[stk.back()]*F(stk.size())));
			cur[stk.back()]-=cur[lst];
			lst=stk.back();
			stk.pop_back();
		}
		cur[i]=v[i]+cur[lst];
		stk.push_back(i);
		Add(stk.size(),cur[i]*F(stk.size()));
		for(int j:lq[i]){
			int p=lower_bound(stk.begin(),stk.end(),pos[j],greater<int>())-stk.begin()+1;
			ans[j]-=Ask(p+1,n)*F(p+1);
		}
	}

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

	return 0;
}