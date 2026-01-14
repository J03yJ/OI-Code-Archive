#include<bits/stdc++.h>

using namespace std;

ifstream fin("invert.in");
ofstream fout("invert.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e6+9;
const int M=1e1+9;
const int K=(1<<10)+9;

ll sum[K],cnt[K];
vector<ll> pos[K],psum[K];
int a[N][M],n,m,p,q;

signed main(){
	cin>>n>>m>>p>>q;
	for(int sta=0;sta<(1<<m);sta++){
		pos[sta].push_back(LLONG_MIN);
		psum[sta].push_back(0);
	}
	for(int i=1;i<=n;i++){
		int sta=0;
		for(int j=1;j<=m;j++){
			char c;
			cin>>c;
			a[i][j]=c-'0';
			sta|=a[i][j]<<j-1;
		}
		cnt[sta]++;
		sum[sta]+=i;
		pos[sta].push_back(i);
		psum[sta].push_back(psum[sta].back()+i);
	}

	ll ans=LLONG_MIN;
	for(int sta=0;sta<(1<<m);sta++){
		ll res=0;
		for(int tta=0;tta<(1<<m);tta++){
			if(pos[tta].size()<=1) continue ;
			ll b[2]={0,0},k[2]={0,0};
			for(int i=1;i<=m;i++){
				b[((sta^tta)>>i-1&1)^1]+=i*q;
				k[((sta^tta)>>i-1&1)^1]+=p;
			}
			if(b[0]<b[1]||b[0]==b[1]&&k[0]<k[1]){
				swap(b[0],b[1]);
				swap(k[0],k[1]);
			}
			auto F=[b,k,tta](int op,int pos)->ll{
				return b[op]*pos+k[op]*psum[tta][pos];
			};
			auto G=[b,k,tta,F](int op,int l,int r)->ll{
				return F(op,r)-F(op,l-1);
			};
			if(k[0]>=k[1]){
				res+=F(0,pos[tta].size()-1);
				continue ;
			}
			int p=(b[0]-b[1]+k[1]-k[0]-1)/(k[1]-k[0]);
			int i=lower_bound(pos[tta].begin(),pos[tta].end(),p)-pos[tta].begin();
			res+=G(0,1,i-1);
			res+=G(1,i,pos[tta].size()-1);
		}
		ans=max(ans,res);
	}

	cout<<ans<<endl;

	return 0;
}