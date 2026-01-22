#include<bits/stdc++.h>

using namespace std;

using ll=long long;
using bint=__int128;

const int D=4e2;
const bint T=1e18;

ll k,n;
bint f[D][D<<3],g[D][D],p10[D];
inline bint Count(int t,bint lft,vector<int> &cnt){
	if(!t) return !lft;
	vector<int> trg(k+1);
	for(int i=0;i<k;i++) trg[i]=lft%10,lft/=10;
	g[0][0]=1;
	for(int i=0;i<k;i++){
		for(int p=0;p<=t;p++){
			for(int q=0;q<=t;q++){
				if(p*10+trg[i]-q>=0) g[i+1][p]+=g[i][q]*f[cnt[i]][p*10+trg[i]-q];	
			}
		}
	}
	bint ans=g[k][lft];
	for(int i=0;i<=k;i++){
		for(int p=0;p<=t;p++) g[i][p]=0;
	}
	return ans;
}

signed main(){
	cin>>k>>n;

	f[0][0]=1,p10[0]=1;
	for(int i=1;i<=37;i++){
		for(int j=0;j<=i*8;j++){
			for(int k=j;k>=max(j-8,0);k--) f[i][j]+=f[i-1][k];
		}
	}
	for(int i=1;i<=37;i++) p10[i]=p10[i-1]*10;

	bint ans=0,s9=0;
	for(int i=0;i<k;i++) s9=s9*10+9;
	for(int i=37;~i;i--){
		int t=(i+k-1)/k;
		vector<int> cnt(k,0);
		for(int j=0;j<i;j++) cnt[j%k]++;
		for(int x=0;x<9;x++){
			bint sum=-!ans;
			for(int c=0;c<=t;c++){
				bint lft=c*s9+(s9-ans%s9)%s9;
				sum+=Count(t,lft,cnt);
			}
			if(n<=sum) break ;
			n-=sum,ans+=p10[i];
		}
	}

	ans/=s9;

	if(ans<T) cout<<ll(ans)<<endl;
	else cout<<ll(ans/T)<<setw(18)<<setfill('0')<<ll(ans%T)<<endl;

	return 0;
}