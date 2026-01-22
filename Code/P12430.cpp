#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=3e5+9;
const int lgN=20;

int a[N],ql[N],qr[N],bel[N],maxl[N],maxr[N],ans[N],cnt[N],cur[N],n,q;
vector<int> w[N],pos[N],lq[N],rq[N];
inline int Shift(int x,int k){return k<=20?x>>k:0;}

int mxp[N][lgN],lg[N];
inline int Cmp(int i,int j){return a[i]<a[j]?j:i;}
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

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=q;i++){
		cin>>ql[i]>>qr[i];
		if(ql[i]==qr[i]) ans[i]=a[ql[i]];
		qr[i]--;
	}
	for(int i=1;i<=n;i++) a[i]=max(a[i],a[i+1]);

	Init();
	vector<int> stk;
	for(int i=1;i<=n;i++){
		int tmp=0,c=0;
		while(stk.size()&&a[stk.back()]<a[i]){
			tmp=Shift(tmp,a[stk.back()]-c);
			w[stk.back()].push_back(w[stk.back()].back()+tmp);
			tmp=w[stk.back()].back()+pos[stk.back()].size()-1;
			c=a[stk.back()];
			stk.pop_back();
		}
		tmp=Shift(tmp,a[i]-c);
		if(!stk.size()||a[stk.back()]>a[i]){
			pos[i].push_back(0);
			pos[i].push_back(i);
			w[i].push_back(0);
			w[i].push_back(tmp);
			stk.push_back(i);
		}else{
			pos[stk.back()].push_back(i);
			w[stk.back()].push_back(w[stk.back()].back()+tmp);
		}
		bel[i]=stk.back();
		if(i==n){
			int tmp=0,c=0;
			while(stk.size()){
				tmp=Shift(tmp,a[stk.back()]-c);
				w[stk.back()].push_back(w[stk.back()].back()+tmp);
				tmp=w[stk.back()].back()+pos[stk.back()].size()-1;
				c=a[stk.back()];
				stk.pop_back();
			}
		}
	}
	for(int i=1;i<=q;i++){
		if(ql[i]>qr[i]) continue ;
		int p=bel[MaxPos(ql[i],qr[i])];
		int lp=lower_bound(pos[p].begin(),pos[p].end(),ql[i])-pos[p].begin();
		int rp=upper_bound(pos[p].begin(),pos[p].end(),qr[i])-pos[p].begin()-1;
		ans[i]=a[p];
		maxl[i]=pos[p][lp];
		maxr[i]=pos[p][rp];
		cnt[i]+=w[p][rp]-w[p][lp];
		cnt[i]+=rp-lp+1;
		lq[ql[i]].push_back(i);
		rq[qr[i]].push_back(i);
	}
	stk.clear();

	for(int i=1;i<=n;i++){
		int u=0;
		while(stk.size()&&a[stk.back()]<=a[i]) u=stk.back(),stk.pop_back();
		if(u) cur[i]=Shift(cur[u],a[i]-a[u]);
		stk.push_back(i);
		cur[i]++;
		array<int,2> lst({Shift(cur[u],a[i]-a[u]),cur[i]});
		for(int j=stk.size()-2;~j;j--){
			if(lst[0]==lst[1]) break ;
			int k=a[stk[j]]-a[stk[j+1]];
			lst={cur[stk[j]],cur[stk[j]]-Shift(lst[0],k)+Shift(lst[1],k)};
			cur[stk[j]]=lst[1];
		}
		for(int j:rq[i]){
			int k=lower_bound(stk.begin(),stk.end(),maxr[j])-stk.begin()+1;
			if(k>=stk.size()) continue ;
			cnt[j]+=Shift(cur[stk[k]],a[stk[k-1]]-a[stk[k]]);
		}
	}
	for(int i=1;i<=n;i++) cur[i]=0;
	stk.clear();
	
	for(int i=n;i>=1;i--){
		int u=0;
		while(stk.size()&&a[stk.back()]<=a[i]) u=stk.back(),stk.pop_back();
		if(u) cur[i]=Shift(cur[u],a[i]-a[u]);
		stk.push_back(i);
		cur[i]++;
		array<int,2> lst({Shift(cur[u],a[i]-a[u]),cur[i]});
		for(int j=stk.size()-2;~j;j--){
			if(lst[0]==lst[1]) break ;
			int k=a[stk[j]]-a[stk[j+1]];
			lst={cur[stk[j]],cur[stk[j]]-Shift(lst[0],k)+Shift(lst[1],k)};
			cur[stk[j]]=lst[1];
		}
		for(int j:lq[i]){
			int k=lower_bound(stk.begin(),stk.end(),maxl[j],greater<int>())-stk.begin()+1;
			if(k>=stk.size()) continue ;
			cnt[j]+=Shift(cur[stk[k]],a[stk[k-1]]-a[stk[k]]);
		}
	}
	for(int i=1;i<=n;i++) cur[i]=0;
	stk.clear();

	for(int i=1;i<=q;i++) cout<<ans[i]+lg[cnt[i]]+1<<endl;

	return 0;
}