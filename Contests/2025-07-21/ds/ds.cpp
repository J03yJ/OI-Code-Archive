#include<bits/stdc++.h>

using namespace std;

ifstream fin("ds.in");
ofstream fout("ds.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=5e5+9;

int p[N],s[N],l[N],r[N],n,typ;
int ql[N],qr[N],q;
ll sum[N],ans[N];

struct Fenw{
	ll tr[N];
	inline void Add(int x,ll k){while(x<=n){tr[x]+=k,x+=x&-x;}}
	inline ll Ask(int x){ll sum=0;while(x){sum+=tr[x],x&=x-1;}return sum;}
	inline ll Ask(int l,int r){return l<=r?Ask(r)-Ask(l-1):0;}
	inline void Clear(){for(int i=1;i<=n;i++) tr[i]=0;}
}t0,t1,t2;

vector<int> qry[N],qly[N];

signed main(){
	cin>>n>>q>>typ;
	for(int i=1;i<=n;i++) cin>>p[i];
	for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i];

	vector<int> stk;
	for(int i=n;i>=1;i--){
		while(stk.size()&&p[stk.back()]<=p[i]){
			l[stk.back()]=i+1;
			stk.pop_back();
		}
		stk.push_back(i);
		r[i]=i;
		s[i]=stk.size();
	}
	for(int i:stk) l[i]=1;


	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+s[i];
	for(int i=1;i<=q;i++) ans[i]=2ll*(qr[i]-ql[i]+1)*(sum[qr[i]]-sum[ql[i]-1]);

	for(int i=1;i<=q;i++) qry[qr[i]].push_back(i),qly[ql[i]].push_back(i);

	for(int i=n;i>=1;i--){
		t2.Add(l[i],1);
		for(int j:qry[i]){
			ans[j]-=t2.Ask(1,ql[j])*(qr[j]-ql[j]+1)*(qr[j]-ql[j]+1);
		}
	}
	t2.Clear();

	for(int i=1;i<=n;i++){
		t0.Add(l[i],1ll*(r[i]-l[i]+1)*(r[i]-l[i]+1));
		for(int j:qry[i]){
			ans[j]-=t0.Ask(ql[j],qr[j]);
			if(ql[j]==l[i]&&qr[j]==r[i]){
				ans[j]+=1ll*(r[i]-l[i]+1)*(r[i]-l[i]+1);
			}
		}
	}
	t0.Clear();

	for(int i=n;i>=1;i--){
		for(int j:qry[i]){
			ans[j]-=t0.Ask(ql[j]+1,qr[j]);
			ans[j]-=t1.Ask(ql[j]+1,qr[j])*(qr[j]+1);
			ans[j]-=t2.Ask(ql[j]+1,qr[j])*(qr[j]+1)*(qr[j]+1);
		}
		t0.Add(l[i],1ll*l[i]*l[i]);
		t1.Add(l[i],-2ll*l[i]);
		t2.Add(l[i],1);
	}
	t0.Clear();
	t1.Clear();
	t2.Clear();

	for(int i=1;i<=n;i++){
		for(int j:qly[i]){
			ans[j]+=t0.Ask(1,ql[j]-1);
			ans[j]+=t1.Ask(1,ql[j]-1)*ql[j];
			ans[j]+=t2.Ask(1,ql[j]-1)*ql[j]*ql[j];
		}
		for(int j:qry[i]){
			ans[j]-=t0.Ask(1,ql[j]-1);
			ans[j]-=t1.Ask(1,ql[j]-1)*ql[j];
			ans[j]-=t2.Ask(1,ql[j]-1)*ql[j]*ql[j];
		}
		t0.Add(l[i],1ll*(r[i]+1)*(r[i]+1));
		t1.Add(l[i],-2ll*(r[i]+1));
		t2.Add(l[i],1);
	}
	t0.Clear();
	t1.Clear();
	t2.Clear();

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;
	
	return 0;
}