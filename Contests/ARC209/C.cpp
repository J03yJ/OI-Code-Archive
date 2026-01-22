#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1e5+9;
const int lgN=2e1;

int a[N],w[N],s[N],ed[N],llm[N],to[N][lgN],n,lim,q;
vector<int> val[N];

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>lim>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>w[i],s[i]=s[i-1]+max(w[i],0);

	for(int i=1;i<=n;i++){
		int v=a[i]-1;
		val[i].push_back(lim);
		for(int l=v/lim+1,r,x;l<=v;l=r+1){
			r=v/(x=v/l);
			val[i].push_back(x+1);
			val[i].push_back(x);
		}
		val[i].push_back(1);
		val[i].erase(unique(val[i].begin(),val[i].end()),val[i].end());
	}
	val[0].push_back(lim),val[0].push_back(1);

	unordered_map<int,int> lst,cur;
	for(int x:val[n]) lst[x]=n+1;
	for(int i=n;i>=1;i--){
		for(int x:val[i-1]){
			if(w[i]==1){
				if(1ll*x*lim<a[i]) cur[x]=i;
				else{
					if(w[i+1]==1) cur[x]=llm[i+1];
					else cur[x]=lst[(a[i]-1)/x+1];
				}
			}else{
				if(x>=a[i]) cur[x]=i;
				else{
					if(w[i+1]==-1) cur[x]=ed[i+1];
					else cur[x]=lst[min((a[i]-1)/x,lim)];
				}
			}
		}
		ed[i]=cur[1],llm[i]=cur[lim];
		to[i][0]=max(cur[1],cur[lim])+1;
		swap(lst,cur),cur.clear();
	}
	to[n+1][0]=to[n+2][0]=n+2;

	for(int k=1;k<lgN;k++){
		for(int i=1;i<=n+2;i++) to[i][k]=to[to[i][k-1]][k-1];
	}

	while(q--){
		int l,r;
		cin>>l>>r;

		int sum=s[r]-s[l-1];
		if(ed[l]>r) cout<<sum<<endl;
		else{
			int x=ed[l]+1,cnt=1;
			for(int k=lgN-1;~k;k--){
				if(to[x][k]<=r+1){
					x=to[x][k];
					cnt+=1<<k;
				}
			}
			cout<<sum-cnt<<endl;
		}
	}
	
	return 0;
}