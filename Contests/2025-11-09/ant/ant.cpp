#include<bits/stdc++.h>

using namespace std;

ifstream fin("ant.in");
ofstream fout("ant.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e5+9;

ll wsum;
int w[N],x[N],typ[N],n,L;
vector<int> pos[2];

signed main(){
	cin>>n>>L;
	for(int i=1;i<=n;i++) cin>>w[i]>>x[i]>>typ[i],wsum+=w[i];

	for(int i=1;i<=n;i++){
		typ[i]=(typ[i]>0);
		pos[typ[i]].push_back(x[i]);
	}
	for(int k:{0,1}) sort(pos[k].begin(),pos[k].end());

	vector<array<int,2>> T;
	for(int i=1,t;i<=n;i++){
		int cl=lower_bound(pos[1].begin(),pos[1].end(),x[i])-pos[1].begin();
		int cr=pos[0].end()-upper_bound(pos[0].begin(),pos[0].end(),x[i]);
		if(typ[i]){
			if(cl<cr) t=*(lower_bound(pos[0].begin(),pos[0].end(),x[i])+cl);
			else t=L-*(lower_bound(pos[1].begin(),pos[1].end(),x[i])-cr);
		}else{
			if(cr<cl) t=L-*(lower_bound(pos[1].begin(),pos[1].end(),x[i])-cr-1);
			else t=*(lower_bound(pos[0].begin(),pos[0].end(),x[i])+cl);
		}
		T.push_back({t,w[i]});
	}
	sort(T.begin(),T.end());

	ll cur=0;int t=-1;
	for(auto p:T){
		cur+=p[1];
		if(cur*2>=wsum){
			t=p[0];
			break ;
		}
	}

	ll ans=0;
	for(int x:pos[1]){
		ans+=lower_bound(pos[0].begin(),pos[0].end(),x+2ll*t)
		-lower_bound(pos[0].begin(),pos[0].end(),x);
	}

	cout<<ans<<endl;

	return 0;
}