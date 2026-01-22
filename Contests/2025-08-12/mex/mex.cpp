#include<bits/stdc++.h>

using namespace std;

ifstream fin("mex.in");
ofstream fout("mex.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=3e5+9;
const int S=6e2+9;

bool bg;
set<int> s[N];
int a[N],lp[N],rp[N],n,m,q,T;
int iblk[N],iL[S],iR[S],B;
int suf[S][S];
bool st;
inline void Init(){
	B=sqrt(m);
	for(int i=1;i<=m;i++) iblk[i]=(i-1)/B+1;
	for(int i=1;i<=m;i++) iR[iblk[i]]=i;
	for(int i=m;i>=1;i--) iL[iblk[i]]=i;
	for(int i=1;i<=iblk[m];i++){
		for(int j=1;j<=iblk[m];j++) suf[j][i]=n;
	}
}
inline void Rebuild(int x){
	for(int i=1;i<=iblk[m];i++) suf[x][i]=n;
	for(int i=iL[x];i<=iR[x];i++){
		if(rp[i]) suf[x][iblk[rp[i]]]=min(suf[x][iblk[rp[i]]],a[rp[i]]);
	}
	for(int i=iblk[m]-1;i>=1;i--) suf[x][i]=min(suf[x][i],suf[x][i+1]);
}
inline int Query(int l,int r){
	int ans=n;
	if(iblk[r]<iblk[m]){
		for(int i=1;i<iblk[l];i++) ans=min(ans,suf[i][iblk[r]+1]);
	}
	for(int i=iL[iblk[l]];i<=l;i++){
		if(rp[i]&&rp[i]>=r) ans=min(ans,a[rp[i]]);
	}
	for(int i=r;i<=iR[iblk[r]];i++){
		if(lp[i]&&lp[i]<=l) ans=min(ans,a[i]);
	}
	return ans;
}
inline void Insert(int x){
	int l=0,r=0;
	auto ir=s[a[x]].upper_bound(x);
	if(ir!=s[a[x]].end()) r=*ir;
	if(ir!=s[a[x]].begin()) l=*prev(ir);
	s[a[x]].insert(x);
	if(l) rp[l+1]=x,lp[x]=l+1,Rebuild(iblk[l+1]);
	else lp[x]=0;
	if(r) rp[x+1]=r,lp[r]=x+1,Rebuild(iblk[x+1]);
	else rp[x+1]=0;
}
inline void Erase(int x){
	int l=0,r=0;
	s[a[x]].erase(x);
	auto ir=s[a[x]].upper_bound(x);
	if(ir!=s[a[x]].end()) r=*ir;
	if(ir!=s[a[x]].begin()) l=*prev(ir);
	if(l) rp[l+1]=r,lp[x]=0,Rebuild(iblk[l+1]);
	if(r) rp[x+1]=0,lp[r]=l+1,Rebuild(iblk[x+1]);
}

signed main(){
	cin>>T>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i+n],a[i+n]=min(a[i+n],n-1);
	for(int i=1;i<=n;i++) a[i]=a[i+n+n]=i-1;
	m=3*n;

	Init();
	for(int i=1;i<=n;i++) Insert(i);
	for(int i=1;i<=n;i++) Insert(i+n);
	for(int i=1;i<=n;i++) Insert(i+n+n);

	int ans=0;
	while(q--){
		int op,x,y;
		cin>>op>>x>>y;
		x=(x+T*ans)%n+1,y=(y+T*ans)%n+op;
		if(op==0){
			Erase(x+n);
			a[x+n]=y;
			Insert(x+n);
		}else{
			if(x>y) swap(x,y);
			ans=Query(x+n,y+n+1);
			cout<<ans<<endl;
		}
	}

	return 0;
}