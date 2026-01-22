#include<bits/stdc++.h>

using namespace std;

ifstream fin("maze.in");
ofstream fout("maze.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e5+9;

int a[N],c[N],n,k;

int tr[N];
inline void Add(int x,int k){while(x<=n) tr[x]+=k,x+=x&-x;}
inline int Ask(int x){int sum=0;while(x) sum+=tr[x],x&=x-1;return sum;}
inline int Ask(int l,int r){return Ask(r)-Ask(l-1);}

inline void Solve(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];

	ll ans=0;
	for(int i=1;i<=n;i++){
		c[a[i]]=Ask(a[i],n);
		Add(a[i],1);
	}
	for(int i=1;i<=n;i++) Add(a[i],-1);
	vector<int> cur({a[1]});
	for(int i=2;i<=n;i+=k-1){
		for(int j=i;j<=min(n,i+k-2);j++) cur.push_back(a[j]);
		if(cur.size()>k){
			priority_queue<int> q;
			for(int j=0;j<k;j++) q.push(-cur[j]);
			for(int j=0;j<cur.size();j++){
				cur[j]=-q.top(),q.pop();
				if(j+k<cur.size()) q.push(-cur[j+k]);
			}
		}
		while(cur.size()>k) cur.pop_back();
		bool flag=0;
		for(int x:cur){
			if(Ask(x,n)) flag=1;
			c[x]-=Ask(x,n);
			Add(x,1);
		}
		for(int x:cur) Add(x,-1);
		ans+=flag;
	}
	for(int i=1;i<=n;i++) ans+=(c[i]+k-2)/(k-1);
	
	cout<<ans<<endl;
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}