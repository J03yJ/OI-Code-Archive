#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=3e5+9;

int id[N<<1],typ[N<<1],l[N],r[N],w[N],n,k;
ll sum[N<<1],c[N<<1];

signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>l[i]>>r[i]>>w[i];
		typ[l[i]]=0,typ[r[i]]=1;
		id[l[i]]=id[r[i]]=i;
	}

	ll ans=0;
	for(int i=2*n;i>=0;i--){
		if(typ[i]) continue ;
		ll sum=0;
		// queue<int> q;
		// priority_queue<array<int,2>> h;
		int c=0,maxc=0;
		vector<int> lim(2*n+1,0);
		vector<ll> con(2*n+1,0);
		for(int j=i+1;j<=2*n;j++){
			if(typ[j]==0) maxc=max(maxc,++c);
			else if(typ[j]==1&&l[id[j]]>i) c--,sum+=w[id[j]];
			lim[j]=k-maxc,con[j]=sum;
		}
		sum=0;
		priority_queue<int> q;
		vector<ll> shr(2*n+1,0);
		for(int j=2*n;j>i;j--){
			if(typ[j]==1&&l[id[j]]<i){
				q.push(-w[id[j]]);
				sum+=w[id[j]];
			}
			while(q.size()&&q.size()>lim[j]){
				sum-=-q.top();
				q.pop();
			}
			cout<<i<<" : "<<j<<" = "<<sum<<endl;
			shr[j]=sum;
		}
		int t=2*n+1;
		for(int j=i+1;j<=2*n;j++){
			if(lim[j]<0){
				t=j;
				break ;
			}
			// shr[j]=max(shr[j],shr[j-1]);
			ans=max(ans,shr[i+1]+con[j]);
		}
		cout<<i<<" : "<<t-1<<endl;
		for(int j=1;j<=2*n;j++) cout<<lim[j]<<' ';cout<<endl;
	}

	cout<<ans<<endl;

	return 0;
}