#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=4e2+9;
const ll inf=1e18;

int a[N][N],n,m,k;
vector<ll> len[N];

signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++){
		for(int j=1;j<=n;j++) cin>>a[i][j];
	}

	ll cst=0,sum=0;
	for(int i=1;i<=n;i++){
		vector<int> tmp;
		for(int j=1;j<=k;j++) tmp.push_back(a[j][i]);
		sort(tmp.begin(),tmp.end());
		ll x=tmp[k-1>>1];
		for(int j=1;j<=k;j++) cst+=abs(a[j][i]-x);
		sum+=x;
	}
	
	// cout<<"! "<<sum<<' '<<m<<' '<<cst<<endl;
	for(int i=1;i<=n;i++){
		vector<int> tmp;
		for(int j=1;j<=k;j++) tmp.push_back(a[j][i]);
		sort(tmp.begin(),tmp.end());
		// for(int x:tmp) cout<<x<<' ';cout<<endl;
		if(sum>m){
			for(int j=k-1>>1;~j;j--){
				if(j==(k-1>>1)) len[i].push_back(0);
				else len[i].push_back(tmp[j+1]-tmp[j]);
			}
			len[i].push_back(tmp.front());
		}else{
			for(int j=k>>1;j<k;j++){
				if(j==(k-1>>1)) len[i].push_back(0);
				else len[i].push_back(tmp[j]-tmp[j-1]);
			}
			len[i].push_back(inf);
		}
		// cout<<i<<" : "<<tmp[k-1>>1]<<" | ";
		// for(ll x:len[i]) cout<<x<<' ';cout<<endl;
	}

	priority_queue<array<int,2>> q;
	for(int i=1;i<=n;i++) q.push({-0,i});
	while(sum!=m&&q.size()){
		int i=q.top()[1],j=-q.top()[0];
		q.pop();
		ll dlt=min(len[i][j],abs(m-sum));
		if(sum<=m) sum+=dlt;
		else sum-=dlt;
		cst+=(2ll*j-(k&1))*dlt;
		// cout<<" -> "<<i<<' '<<j<<' '<<dlt<<endl;
		if(j+1<len[i].size()) q.push({-(j+1),i});
	}
	cst>>=1;

	cout<<cst<<endl;

	return 0;
}