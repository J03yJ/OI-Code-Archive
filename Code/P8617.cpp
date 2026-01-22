#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=5e5+9;

int sa[N],rk[N<<1],lsa[N],lrk[N<<1],cnt[N],h[N],n;
string s;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>s;
	n=s.size();
	s=" "+s;

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
		for(int i=1;i<=n;i++) cnt[rk[sa[i]+k]]++;
		for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
		for(int i=n;i>=1;i--) lsa[cnt[rk[sa[i]+k]]--]=sa[i];
		for(int i=0;i<=m;i++) cnt[i]=0;
		
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

	cout<<*max_element(h+1,h+n+1)<<endl;

	return 0;
}