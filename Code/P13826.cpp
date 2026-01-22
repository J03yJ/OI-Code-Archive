#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=3e5+9;
const int T=6e2+9;

int a[N],blk[N],L[T],R[T],n,m,B,scnt;
array<int,2> rx[N],ry[N];
vector<array<int,3>> seg[N];
ll ans[N];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>rx[i][0]>>rx[i][1]>>ry[i][0]>>ry[i][1];
		rx[i][1]--,ry[i][1]--;
		seg[rx[i][0]].push_back({ry[i][0],ry[i][1],1});
		seg[rx[i][1]+1].push_back({ry[i][0],ry[i][1],-1});
	}

	B=sqrt(n);
	for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
	for(int i=1;i<=n;i++) R[blk[i]]=i;
	for(int i=n;i>=1;i--) L[blk[i]]=i;

	int cnt=0,ins=0;
	for(int p=1;p<=blk[n];p++){
		int tag=0,llim=0,rlim=0;
		vector<int> tags;
		auto PushTag=[&tag](int k){tag+=k;};
		auto Stamp=[&tag,&llim,&rlim,&tags](){
			llim=min(llim,tag);
			rlim=max(rlim,tag);
			tags.push_back(tag);
		};
		auto PushDown=[p,&tag,&llim,&rlim,&tags,&cnt](){
			cnt++;
			llim-=tag,rlim-=tag;
			vector<int> cnt(rlim-llim+1);
			// cout<<" : "<<llim<<' '<<rlim<<endl;
			for(int i:tags) cnt[(i-tag)-llim]++/* ,cout<<" -> "<<(i-tag)<<endl */;
			for(int i=L[p];i<=R[p];i++){
				a[i]+=tag;
				int tmp=(m-a[i]%m)%m;
				// cout<<"PushDown : "<<p<<' '<<i<<' '<<a[i]<<' '<<tmp<<endl;
				// for(int j=tmp;j<=rlim;j+=m) ans[a[i]+j]+=cnt[j-llim]/* ,cout<<">>> "<<a[i]<<' '<<j<<' '<<cnt[j-llim]<<endl */;
				// for(int j=tmp-m;j>=llim;j-=m) ans[a[i]+j]+=cnt[j-llim]/* ,cout<<">>> "<<a[i]<<' '<<j<<' '<<cnt[j-llim]<<endl */;
			}
			tags.clear();
			tags.shrink_to_fit();
			cnt.clear();
			cnt.shrink_to_fit();
			tag=llim=rlim=0;
		};
		auto Modify=[p,&tag,&llim,&rlim,&tags,&PushTag,&PushDown](int l,int r,int k){
			if(l==L[p]&&r==R[p]) PushTag(k);
			else{
				PushDown();
				for(int i=l;i<=r;i++) a[i]+=k;
			}
		};
		// cout<<"# "<<p<<'('<<L[p]<<'~'<<R[p]<<')'<<endl;
		// cerr<<"# "<<p<<'('<<L[p]<<'~'<<R[p]<<')'<<endl;
		for(int i=1;i<=n;i++){
			for(auto t:seg[i]){
				int l=max(t[0],L[p]),r=min(t[1],R[p]),k=t[2];
				if(l>r) continue ;
				// cout<<"! "<<l<<' '<<r<<' '<<k<<endl;
				Modify(l,r,k);
			}
			Stamp();
			// cout<<i<<" : "<<tag<<" | ";
			// for(int j=L[p];j<=R[p];j++) cout<<a[j]+tag<<' ';cout<<endl;
			// cout<<"$ ";for(int i:tags) cout<<i<<' ';cout<<endl;
		}
		PushDown();
	}

	cerr<<"PushDown Count = "<<cnt<<endl;

	for(int i=m;i<=n;i+=m) cout<<ans[i]<<endl;

	return 0;
}