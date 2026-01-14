#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;

int a[N],n,m;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m;
	for(int i=0;i<n;i++) cin>>a[i];

	int ans=n;
	for(int i=0;i<m;i++){
		int res=n;
		vector<int> v(n<<1);
		for(int j=0;j<n;j++) v[j]=v[j+n]=a[j]>>i&1;
		if(accumulate(v.begin(),v.end(),0)==0){
			ans=1;
			break ;
		}
		for(int j=0;j+2<n*2;j++){
			if(!v[j]&&!v[j+1]&&!v[j+2]){
				ans=1;
				break ;
			}
		}
		if(accumulate(v.begin(),v.end(),0)==v.size()) continue ;
		int p=find(v.begin(),v.end(),0)-v.begin();
		for(int j=p,k=0;j<p+n;j=k){
			while(k<n*2&&v[k]) k++;
			if(k==j) k++;
			else res=min(res,k-j);
		}
		ans=min(ans,res);
	}

	cout<<ans<<endl;

	return 0;
}