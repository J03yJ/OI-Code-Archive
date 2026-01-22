#include<bits/stdc++.h>

using namespace std;

ifstream fin("prize.in");
ofstream fout("prize.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e6+9;
const int B=20;
const int S=(1<<B)+9;

int a[N],n,q;
ll cnt[S],sum[S],ans[S];

signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];

	ll tot=0;
	for(int i=1;i<=n;i++){
		tot+=a[i];
		for(int j=B-1,tmp=0;~j;j--){
			if(a[i]>>j&1) tmp|=1<<j;
			else{
				cnt[tmp|(1<<j)]++;
				sum[tmp|(1<<j)]+=a[i]&((1<<j+1)-1);
			}
		}
	}
	for(int i=0;i<B;i++){
		for(int j=1;j<(1<<B);j++){
			if(j>>i&1) continue ;
			cnt[j]+=cnt[j|(1<<i)];
			sum[j]+=sum[j|(1<<i)];
		}
	}
	for(int i=(1<<B)-1;~i;i--){
		for(int k=0;k<B;k++){
			if(i>>k&1) break ;
			cnt[i]-=cnt[i|(1<<k)];
			sum[i]-=sum[i|(1<<k)];
		}
	}

	for(int i=0;i<(1<<B);i++){
		ll s=0;
		for(int j=1;j<=n;j++){
			for(int k=B-1;~k;k--){
				if((i>>k&1)&&(~a[j]>>k&1)){
					s+=(i&((1<<k+1)-1))-(a[j]&((1<<k+1)-1));
					break ;
				}
			}
		}
		for(int j=B-1,tmp=0;~j;j--){
			if(~i>>j&1) continue ;
			tmp|=1<<j;
			ans[i]+=cnt[tmp]*(i&((1<<j+1)-1))-sum[tmp];
		}
	}
	for(int i=(1<<B)-1;i;i--) ans[i-1]=min(ans[i-1],ans[i]);

	while(q--){
		ll k;
		cin>>k;
		if(k>=1ll*(1<<B)*n-tot){
			ll ans=0;
			k+=tot;
			for(int i=60;~i;i--){
				if(__int128(1)*(ans|(1ll<<i))*n<=k) ans|=1ll<<i;
			}
			cout<<ans<<endl;
		}else{
			int pos=upper_bound(ans,ans+(1<<B),k)-ans-1;
			cout<<pos<<endl;
		}
	}

	return 0;
}