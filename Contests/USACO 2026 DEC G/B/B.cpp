#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;

int a[N],l[N],r[N],n;
vector<int> pos[N];

int tr[N];
inline void Add(int x,int k){while(x<=n) tr[x]+=k,x+=x&-x;}
inline int Ask(int x){int sum=0;while(x) sum+=tr[x],x&=x-1;return sum;}
inline int Ask(int l,int r){return Ask(r)-Ask(l-1);}

inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	vector<int> val(a+1,a+n+1);
	val.push_back(-1);
	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()),val.end());
	int tot=val.size()-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(val.begin(),val.end(),a[i])-val.begin();
		pos[a[i]].push_back(i);
		Add(i,1);
	}
	for(int i=1;i<=tot;i++) l[i]=0,r[i]=pos[i].size()-1;

	ll ans=0;
	for(int i=tot;i>=1;i--){
		while(l[i]<=r[i]){
			int dl=Ask(1,pos[i][l[i]])-1;
			int dr=Ask(pos[i][r[i]],n)-1;
			if(dl<dr) ans+=dl,Add(pos[i][l[i]],-1),l[i]++;
			else ans+=dr,Add(pos[i][r[i]],-1),r[i]--;
		}
		pos[i].clear();
		l[i]=r[i]=0;
	}

	cout<<ans<<endl;

	for(int i=1;i<=n;i++) tr[i]=0;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}