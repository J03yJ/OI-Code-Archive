#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;
const int lgN=2e1;

ll a[N],mx[N][lgN];
int b[N],lg[N],n,k;
vector<ll> s[2];

inline ll Max(int l,int r){
	int k=lg[r-l+1];
	return max(mx[l][k],mx[r-(1<<k)+1][k]);
}
inline bool Check(int mid){
	ll lim=Max(mid,s[0].size()-1)-1ll*n*mid,o=1ll*n*(s[0].size()+1);
	int tar=k-mid,cnt=0;
	for(ll x:s[1]){
		while(x+o<lim&&o<=1ll*n*n) o+=n;
		// cout<<mid<<" ? "<<x/n<<' '<<n-x%n<<' '<<o/n<<" : "<<lim/n<<' '<<n-lim%n<<endl;
		if(o>1ll*n*n) break ;
		cnt++,o+=n;
	}
	return cnt>=tar;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>k;
	for(int i=1,x;i<=n;i++){
		cin>>b[i];
		for(int j:{0,1,2,3}){
			cin>>x;
			a[i]+=x;
		}
		a[i]=a[i]*n+(n-i);
		s[b[i]].push_back(a[i]);
	}
	
	sort(s[0].begin(),s[0].end(),greater<ll>());
	for(int i=0;i<s[0].size();i++) s[0][i]+=1ll*n*(i+1);
	for(int i=0;i<s[0].size();i++) mx[i][0]=s[0][i];
	for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
	for(int k=1;k<=lg[n];k++){
		for(int i=0;i+(1<<k)-1<s[0].size();i++){
			mx[i][k]=max(mx[i][k-1],mx[i+(1<<k-1)][k-1]);
		}
	}
	sort(s[1].begin(),s[1].end(),greater<ll>());

	int l=-1,r=s[0].size();
	while(l+1<r){
		int mid=l+r>>1;
		if(Check(mid)) r=mid;
		else l=mid;
	}

	cout<<k-r<<endl;

	return 0;
}