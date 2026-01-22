#include<bits/stdc++.h>

using namespace std;

ifstream fin("bracket.in");
ofstream fout("bracket.out");
#define cin fin
#define cout fout
#define endl '\n'

#define fir(x) (x).first
#define sec(x) (x).second
using pii=pair<int,int>;
using ll=long long;
const int N=2e5+9;
const int lgN=2e1;

struct Table{
	int st[N][lgN],lg[N];
	inline void Init(int n,int *a){
		for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
		for(int i=1;i<=n;i++) st[i][0]=a[i];
		for(int k=1;k<=lg[n];k++){
			for(int i=1;i<=n-(1<<k)+1;i++){
				st[i][k]=min(st[i][k-1],st[i+(1<<k-1)][k-1]);
			}
		}
	}
	inline int Min(int l,int r){
		if(l>r) return 1e9;
		int k=lg[r-l+1];
		return min(st[l][k],st[r-(1<<k)+1][k]);
	}
}at,bt;

int a[N],apre[N],b[N],bpre[N],n;
vector<pii> q[N];
string s;

signed main(){
	cin>>s;
	n=s.size();
	for(int i=1;i<=n;i++){
		a[i]=(s[i-1]=='('?1:-1);
		b[i]=-a[i];
		apre[i]=apre[i-1]+a[i];
		bpre[i]=bpre[i-1]+b[i];
	}

	at.Init(n,apre);
	bt.Init(n,bpre);
	for(int i=1;i<=n;i++){
		int l=i-1,r=n+1;
		while(l+1<r){
			int mid=l+r>>1;
			if(apre[i-1]+bt.Min(i,mid)-bpre[i-1]>=0) l=mid;
			else r=mid;
		}
		q[i-1].push_back({apre[i-1],-1});
		q[l].push_back({apre[i-1],1});
	}

	ll ans=0;
	map<int,int> mp;
	for(int i=1;i<=n;i++){
		mp[apre[i]]++;
		for(pii p:q[i]) ans+=sec(p)*mp[fir(p)];
	}

	cout<<ans<<endl;

	return 0;
}