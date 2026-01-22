#include<bits/stdc++.h>

using namespace std;

ifstream fin("phigros.in");
ofstream fout("phigros.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e5+9;

int a[N],t[N],w[N],s[N],px[N],py[N],n;
vector<array<int,3>> op,tmp;
vector<int> val;

ll f[N],tr[N];
inline void Insert(int x,ll k){while(x<=n) tr[x]=max(tr[x],k),x+=x&-x;}
inline ll Query(int x){ll mx=0;while(x) mx=max(mx,tr[x]),x&=x-1;return mx;}
inline void EraseAll(int x){while(x<=n) tr[x]=0,x+=x&-x;}
inline void Work(int l,int r){
	if(l==r) return ;
	int mid=l+r>>1;
	Work(l,mid);
	sort(op.begin()+l,op.begin()+mid+1,[](auto p,auto q){return px[p[2]]<px[q[2]];});
	sort(op.begin()+mid+1,op.begin()+r+1,[](auto p,auto q){return px[p[2]]<px[q[2]];});
	int i=mid+1,j=l;
	while(i<=r){
		while(j<=mid&&px[op[j][2]]<=px[op[i][2]]){
			if(op[j][1]==0) Insert(py[op[j][2]],f[op[j][2]]);
			j++;
		}
		if(op[i][1]==1) f[op[i][2]]=max(f[op[i][2]],w[op[i][2]]+Query(py[op[i][2]]));
		i++;
	}
	while(--j>=l) EraseAll(py[op[j][2]]);
	for(int p=l;p<=r;p++) op[p]=tmp[p];
	Work(mid+1,r);
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i]>>t[i]>>w[i]>>s[i];

	for(int i=1;i<=n;i++){
		op.push_back({t[i],1,i});
		op.push_back({t[i]+s[i],0,i});
		px[i]=-a[i]+t[i],py[i]=a[i]+t[i];
		val.push_back(py[i]);
		f[i]=w[i];
	}
	val.push_back(INT_MIN);
	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()),val.end());
	for(int i=1;i<=n;i++) py[i]=lower_bound(val.begin(),val.end(),py[i])-val.begin();

	sort(op.begin(),op.end()),tmp=op;
	Work(0,op.size()-1);

	ll ans=0;
	for(int i=1;i<=n;i++) ans=max(ans,f[i]);

	cout<<ans<<endl;

	return 0;
}