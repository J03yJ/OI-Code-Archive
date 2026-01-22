#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;
const int lgN=2e1+1;

int a[N],c[N],pref[N],suff[N],posf[N],posg[N],wrg[N],n,len,k;

struct RMQ{
	int mn[N][lgN],lg[N],op;
	inline void Init(int n,int *a,int o){
		op=o;
		for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
		for(int i=0;i<=n;i++) mn[i][0]=a[i]*op;
		for(int k=1;k<=lg[n];k++){
			for(int i=0;i<=n-(1<<k)+1;i++){
				mn[i][k]=min(mn[i][k-1],mn[i+(1<<k-1)][k-1]);
			}
		}
	}
	inline int R(int l,int r){
		int k=lg[r-l+1];
		return min(mn[l][k],mn[r-(1<<k)+1][k])*op;
	}
	inline void Clear(int n){
		for(int k=0;k<=lg[n];k++){
			for(int i=0;i<=n;i++) mn[i][k]=0;
		}
		for(int i=0;i<=n;i++) lg[i]=0;
		op=0;
	}
}pmn,smx,wmx;

inline void Solve(){
	cin>>n>>len>>k;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]++;

	int lim=4*n,ans=0,res=0;
	sort(a+1,a+n+1);
	for(int i=1;i<=lim;i++){
		c[i]=upper_bound(a+1,a+n+1,i)-lower_bound(a+1,a+n+1,i-len+1);
		if(c[i]==k) ans++;
	}
	for(int i=1;i<=lim;i++){
		if(i-len>=1){
			if(c[i]==k+1) pref[i]++;
			if(c[i]==k) pref[i]--;
			if(c[i-len]==k-1) pref[i]++;
			if(c[i-len]==k) pref[i]--;
		}
		if(i+len<=lim){
			if(c[i]==k+1) suff[i]++;
			if(c[i]==k) suff[i]--;
			if(c[i+len]==k-1) suff[i]++;
			if(c[i+len]==k) suff[i]--;
		}
		if(c[i]==k) posf[i]--,posg[i]--;
		if(c[i]==k+1) posf[i]++;
		if(c[i]==k-1) posg[i]++;
		pref[i]+=pref[i-1];
		suff[i]+=suff[i-1];
		posf[i]+=posf[i-1];
		posg[i]+=posg[i-1];
		if(i>=len) wrg[i]=posg[i]-posg[i-len];
	}
	wmx.Init(lim,wrg,-1);
	pmn.Init(lim,pref,1);
	smx.Init(lim,suff,-1);

	// for(int i=1;i<=lim;i++) cout<<c[i]<<' ';cout<<endl;
	// for(int i=1;i<=lim;i++) cout<<pref[i]-pref[i-1]<<' ';cout<<endl;
	// for(int i=1;i<=lim;i++) cout<<suff[i]-suff[i-1]<<' ';cout<<endl;
	// for(int i=1;i<=lim;i++) cout<<posf[i]-posf[i-1]<<' ';cout<<endl;
	// for(int i=1;i<=lim;i++) cout<<posg[i]-posg[i-1]<<' ';cout<<endl;
	// for(int i=1;i<=lim;i++) cout<<wrg[i]<<' ';cout<<endl;

	for(int i=1;i<=n;i++){
		int x=a[i];
		int spf=posf[x+len-1]-posf[x-1];
		if(x-len>=1) res=max(res,wmx.R(1,x-1)+spf);
		if(x+len+len-1<=lim) res=max(res,wmx.R(x+len+len-1,lim)+spf);
		// res=max(res,pref[x-1]-pmn.R(max(0,x-len-1),x-1));
		res=max(res,pref[x+len-1]-pmn.R(x-1,x+len-1));
		res=max(res,smx.R(x-1,min(x+len-1,lim))-suff[x-1]);
		// if(x-len>=1) cout<<x<<" -> "<<pref[x+len-1]-pref[x-1]<<" / "<<spf+wrg[x-1]<<endl;
		// if(x+len<=lim) cout<<x<<" -> "<<suff[x+len-1]-suff[x-1]<<" / "<<spf+wrg[x+len+len-1]<<endl;
	}

	cout<<ans+res<<endl;

	wmx.Clear(lim);
	pmn.Clear(lim);
	smx.Clear(lim);
	for(int i=0;i<=lim;i++) a[i]=c[i]=pref[i]=suff[i]=posf[i]=posg[i]=wrg[i]=0;
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}