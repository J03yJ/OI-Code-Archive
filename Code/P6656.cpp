#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1e6+9;
const int lgN=2e1;

struct SufArr{
	string s;
	int sa[N],rk[N<<1],lsa[N],lrk[N<<1],cnt[N],h[N],lg[N],mn[lgN][N],n;

	inline void Init(string str){
		s=" "+str;
		n=str.size();

		for(int i=1;i<=n;i++) cnt[rk[i]=s[i]]++;
		for(int i=1;i<128;i++) cnt[i]+=cnt[i-1];
		for(int i=n;i>=1;i--) sa[cnt[rk[i]]--]=i;
		for(int i=0;i<128;i++) cnt[i]=0;

		int m=0;
		for(int i=1;i<=n;i++) lrk[i]=rk[i];
		for(int i=1;i<=n;i++){
			if(lrk[sa[i]]!=lrk[sa[i-1]]) m++;
			rk[sa[i]]=m;
		}

		for(int k=1;k<=n&&m<n;k<<=1){
			int t=0;
			for(int i=n-k+1;i<=n;i++) lsa[++t]=i;
			for(int i=1;i<=n;i++) if(sa[i]>k) lsa[++t]=sa[i]-k;
			
			for(int i=1;i<=n;i++) cnt[rk[lsa[i]]]++;
			for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
			for(int i=n;i>=1;i--) sa[cnt[rk[lsa[i]]]--]=lsa[i];
			for(int i=0;i<=m;i++) cnt[i]=0;

			m=0;
			for(int i=1;i<=n;i++) lrk[i]=rk[i];
			for(int i=1;i<=n;i++){
				if(lrk[sa[i]]!=lrk[sa[i-1]]||lrk[sa[i]+k]!=lrk[sa[i-1]+k]) m++;
				rk[sa[i]]=m;
			}
		}

		for(int i=1,k=0;i<=n;i++){
			if(k) k--;
			while(s[i+k]==s[sa[rk[i]-1]+k]) k++;
			h[rk[i]]=k;
		}

		for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
		for(int i=1;i<=n;i++) mn[0][i]=h[i];
		for(int k=1;k<=lg[n];k++){
			for(int i=1;i<=n-(1<<k)+1;i++){
				mn[k][i]=min(mn[k-1][i],mn[k-1][i+(1<<k-1)]);
			}
		}
	}
	inline int Min(int l,int r){
		int k=lg[r-l+1];
		return min(mn[k][l],mn[k][r-(1<<k)+1]);
	}
	inline int LCP(int i,int j){
		if(i==j) return n-i+1;
		else return Min(min(rk[i],rk[j])+1,max(rk[i],rk[j]));
	}
}arr,rra;

string s;
int f[N],g[N],n;
vector<array<int,3>> runs;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>s;

	arr.Init(string(s.begin(),s.end()));
	rra.Init(string(s.rbegin(),s.rend()));

	n=s.size();
	s=" "+s;

	vector<int> stk;
	for(int c:{0,1}){
		for(int i=n;i>=1;i--){
			while(stk.size()&&((arr.rk[i]<arr.rk[stk.back()])^c)) stk.pop_back();
			if(stk.size()){
				int j=stk.back(),p=j-i;
				int l=i-rra.LCP(n-i+1,n-j+1)+1,r=j+arr.LCP(i,j)-1;
				if(r-l+1>=2*p&&arr.LCP(l,l+p)==r-l+1-p) runs.push_back({l,r,p});
			}
			stk.push_back(i);
		}
		stk.clear();
	}

	sort(runs.begin(),runs.end());
	runs.erase(unique(runs.begin(),runs.end()),runs.end());

	cout<<runs.size()<<endl;
	for(auto t:runs) cout<<t[0]<<' '<<t[1]<<' '<<t[2]<<endl;

	return 0;
}