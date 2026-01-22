#include<bits/stdc++.h>

using namespace std;

ifstream fin("instrument.in");
ofstream fout("instrument.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=5e5+9;

int a[N],b[N],bel[N],t[N],n,mod;
inline int To(int x,int p){return (p-x+mod)%mod;}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
	for(int i=1;i<=n;i++){
		bel[a[i]]=bel[b[i]]=i;
		t[a[i]]=b[i],t[b[i]]=a[i];
	}
	mod=n<<1;
	
	map<int,int> mp;
	mp[1]=0;
	for(int i=1;i<=n;i++) mp[(a[i]+b[i])%mod]++;
	int mx=-1,p=-1;
	for(pair<int,int> t:mp){
		if(t.second>mx&&(t.first&1)){
			mx=t.second;
			p=t.first;
		}
	}
	cout<<n-mx<<endl;

	map<int,int> vis;
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(vis[a[i]]) continue ;
		if((a[i]+b[i])%mod==p) continue ;
		int j=a[i];
		while(!vis[j]){
			cnt++;
			cout<<bel[j]-1<<' '<<t[j]<<' '<<To(j,p)<<endl;
			vis[j]=vis[To(j,p)]=1;
			j=t[To(j,p)];
		}
	}
	
	return 0;
}