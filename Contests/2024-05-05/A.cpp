#include<bits/stdc++.h>
using namespace std;
const int N=4e4+9;
int sa[N],rk[N],lsa[N],lrk[N],cnt[N],h[N];
int f[N];
bool cmp(pair<int,int> x,pair<int,int> y){
	return x.first>y.first;
}

int tr[N];
void insert(int x,int k,int n){
	while(x<=n){
		tr[x]=max(tr[x],k);
		x+=x&-x;
	}
}
int ask(int x){
	int ans=0;
	while(x){
		ans=max(ans,tr[x]);
		x&=x-1;
	}
	return ans;
}

signed main(){
	string s;
	int n;
	cin>>n>>s;
	s=" "+s;
	for(int i=1;i<=n;i++) cnt[rk[i]=s[i]]++;
	for(int i=1;i<=127;i++) cnt[i]+=cnt[i-1];
	for(int i=n;i>=1;i--) sa[cnt[rk[i]]--]=i;
	for(int i=1;i<=n;i++) lrk[i]=rk[i];
	for(int i=1,tot=0;i<=n;i++){
		if(lrk[sa[i]]==lrk[sa[i-1]]) rk[sa[i]]=tot;
		else rk[sa[i]]=++tot;
	}
	for(int k=1;k<n;k*=2){
		for(int i=0;i<=n;i++) lsa[i]=sa[i],cnt[i]=0;
		for(int i=1;i<=n;i++) cnt[rk[lsa[i]+k]]++;
		for(int i=1;i<=n;i++) cnt[i]+=cnt[i-1];
		for(int i=n;i>=1;i--) sa[cnt[rk[lsa[i]+k]]--]=lsa[i];
		for(int i=0;i<=n;i++) lsa[i]=sa[i],cnt[i]=0;
		for(int i=1;i<=n;i++) cnt[rk[lsa[i]]]++;
		for(int i=1;i<=n;i++) cnt[i]+=cnt[i-1];
		for(int i=n;i>=1;i--) sa[cnt[rk[lsa[i]]]--]=lsa[i];
		for(int i=1;i<=n;i++) lrk[i]=rk[i];
		for(int i=1,tot=0;i<=n;i++){
			if(lrk[sa[i]]==lrk[sa[i-1]]&&lrk[sa[i]+k]==lrk[sa[i-1]+k]) rk[sa[i]]=tot;
			else rk[sa[i]]=++tot;
		}
	}
	
	for(int i=1,k=0;i<=n;i++){
		if(rk[i]==1) continue ;
		if(k) k--;
		while(s[i+k]==s[sa[rk[i]-1]+k]) k++;
		h[rk[i]]=k;
	}
	h[0]=-1;
	
	vector<pair<int,int>> v;
	int m=ceil(sqrt(n));
	for(int i=1;i<=n;i++){
		for(int j=h[i];j<=2*m&&sa[i]+j<=n;j++){
			int k=i+1;
			v.push_back({sa[i],sa[i]+j});
			int pos=v.size()-1;
			while(h[k]>j&&k<=n){
				v.push_back({sa[k],sa[k]+j});
				k++;
			}
			sort(v.begin()+pos,v.end(),cmp);
		}
	}
	
	for(pair<int,int> p:v){
//		for(int i=p.first;i<=p.second;i++) cout<<s[i];cout<<endl;
		f[p.second]=max(f[p.second],ask(p.first-1)+1);
//		cout<<p.second<<' '<<f[p.second]<<endl;
		insert(p.second,f[p.second],n);
	}
	
	cout<<ask(n)<<endl;
	return 0;
}

/*
16
zjehjvambierkwsz
*/
