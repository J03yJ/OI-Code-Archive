#include<bits/stdc++.h>

using namespace std;

ifstream fin("class.in");
ofstream fout("class.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e5+9;
const int S=5e2+9;

ll sum[S][S],ans,su;
int blk[N],L[S],R[S],B,n,m,q,op;
int lm[N],rm[N],sm[N],idx[N],idy[N],ix[N],iy[N],xval[N],yval[N],buc[N];
inline void Discretize(){
	for(int i=1;i<=m;i++) xval[i]=rm[i],yval[i]=lm[i];
	sort(xval+1,xval+m+1);
	sort(yval+1,yval+m+1);
	for(int i=1;i<=m;i++) buc[rm[i]]++;
	for(int i=1;i<=n;i++) buc[i]+=buc[i-1];
	for(int i=m;i>=1;i--) idx[i]=buc[rm[i]]--;
	for(int i=1;i<=n;i++) buc[i]=0;
	for(int i=1;i<=m;i++) buc[lm[i]]++;
	for(int i=1;i<=n;i++) buc[i]+=buc[i-1];
	for(int i=m;i>=1;i--) idy[i]=buc[lm[i]]--;
	for(int i=1;i<=n;i++) buc[i]=0;
	for(int i=1;i<=m;i++) ix[idx[i]]=iy[idy[i]]=i;
}
inline void InitBlock(){
	B=sqrt(m);
	for(int i=1;i<=m;i++) blk[i]=(i-1)/B+1;
	for(int i=1;i<=m;i++) R[blk[i]]=i;
	for(int i=m;i>=1;i--) L[blk[i]]=i;
	for(int i=1;i<=m;i++) sum[blk[idx[i]]][blk[idy[i]]]+=sm[i];
	for(int i=1;i<=blk[m];i++){
		for(int j=1;j<=blk[m];j++){
			sum[i][j]+=sum[i-1][j];
		}
	}
	for(int i=1;i<=m;i++) su+=sm[i];
	ans=su;
}
inline ll BQuery(int x,int y){
	ll ans=0;
	for(int i=blk[m];i>blk[y];i--) ans+=sum[blk[x]-1][i];
	for(int i=R[blk[y]];i>=y;i--) if(idx[iy[i]]<L[blk[x]]) ans+=sm[iy[i]];
	for(int i=L[blk[x]];i<=x;i++) if(idy[ix[i]]>=y) ans+=sm[ix[i]];
	return ans;
}
inline ll Query(int l,int r){
	int x=upper_bound(xval+1,xval+m+1,r)-xval-1;
	int y=lower_bound(yval+1,yval+m+1,l)-yval;
	if(x<1||y>m) return 0;
	return BQuery(x,y);
}

set<array<int,2>> s;
inline void InitSet(){s.insert({1,n});}
inline void Assign1(int l,int r){
	while(s.size()){
		auto it=s.upper_bound({l+1,0});
		if(it==s.begin()) break ;
		array<int,2> t=*--it;
		if(t[1]>=l-1){
			s.erase(it);
			ans-=Query(t[0],t[1]);
			l=min(l,t[0]),r=max(r,t[1]);
		}else break ;
	}
	while(s.size()){
		auto it=s.lower_bound({l,0});
		if(it==s.end()) break ;
		array<int,2> t=*it;
		if(t[0]<=r+1){
			s.erase(it);
			ans-=Query(t[0],t[1]);
			l=min(l,t[0]),r=max(r,t[1]);
		}else break ;
	}
	ans+=Query(l,r);
	s.insert({l,r});
}
inline void Assign0(int l,int r){
	auto it=s.upper_bound({l+1,0});
	if(it!=s.begin()){
		array<int,2> t=*--it;
		if(t[0]<=l&&r<=t[1]){
			s.erase(it);
			ans-=Query(t[0],t[1]);
			if(t[0]<l) ans+=Query(t[0],l-1),s.insert({t[0],l-1});
			if(t[1]>r) ans+=Query(r+1,t[1]),s.insert({r+1,t[1]});
		}else if(t[0]<=l&&l<=t[1]){
			s.erase(it);
			ans-=Query(t[0],t[1]);
			if(t[0]<l) ans+=Query(t[0],l-1),s.insert({t[0],l-1});
		}
	}
	while(s.size()){
		auto it=s.lower_bound({l,0});
		if(it==s.end()) break ;
		array<int,2> t=*it;
		if(t[0]<=r){
			s.erase(it);
			ans-=Query(t[0],t[1]);
			if(t[1]>r) ans+=Query(r+1,t[1]),s.insert({r+1,t[1]});
		}else break ;
	}
}

signed main(){
	cin>>n>>m>>op;
	for(int i=1;i<=m;i++){
		cin>>lm[i]>>rm[i]>>sm[i];
		if(lm[i]>rm[i]) swap(lm[i],rm[i]);
	}

	Discretize();
	InitBlock();
	InitSet();

	cin>>q;
	while(q--){
		ll typ,l,r;
		cin>>typ>>l>>r;
		l^=(su-ans)*op,r^=(su-ans)*op;
		if(l>r) swap(l,r);
		if(!typ) Assign1(l,r);
		else Assign0(l,r);
		cout<<su-ans<<endl;
	}

	return 0;
}