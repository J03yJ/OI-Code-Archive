#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e6+9;

int r[N],n;
ll res[N];
char s[N];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>s[i];

		int lst[3]={n+1,n+1,n+1};
		for(int i=n;i>=1;i--){
			int f=s[i]-'A';
			lst[f]=i;
			r[i]=min(lst[(f+1)%3],lst[(f+2)%3])-1;
		}

		ll sum=0;
		int cnt[3]={0,0,0};
		for(int i=1,j=1;i<=n;i++){
			int f=s[i]-'A';
			cnt[f]++,sum+=cnt[(f+2)%3];
			while(j<=i&&cnt[0]&&cnt[1]&&cnt[2]){
				int g=s[j]-'A';
				cnt[g]--,sum-=cnt[(g+1)%3];
				j++;
			}
			res[i]=res[j-1]+sum;
			if(r[j]<i){
				int g=s[j]-'A';
				res[i]=max(res[i],res[r[j]]+sum-1ll*(r[j]-j+1)*cnt[(g+1)%3]);
			}
		}

		cout<<res[n]<<endl;
	}

	return 0;
}