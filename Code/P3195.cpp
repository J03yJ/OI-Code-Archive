#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N=2e5+9;

int c[N],s[N],f[N];
int n,L;

int val(int l,int r){
//	cout<<l<<' '<<r<<": "<<s[l]<<' '<<s[r]<<endl;
	return (s[r]-s[l]-L)*(s[r]-s[l]-L)+f[l];
}
int get_pt(int i,int j){ // i<j
	int l=j-1,r=n+1;
	while(l+1<r){
		int mid=l+r>>1;
		if(val(i-1,mid)>=val(j-1,mid)) r=mid;
		else l=mid;
	}
	return r;
}

signed main(){
	cin>>n>>L;
	L++;
	for(int i=1;i<=n;i++) cin>>c[i];
	for(int i=1;i<=n;i++) s[i]=s[i-1]+c[i];
	for(int i=1;i<=n;i++) s[i]+=i;
	
	vector<int> st;int head=0;
	for(int i=1;i<=n;i++){
		while(st.size()>1&&get_pt(st[st.size()-2]-1,st.back())>=get_pt(st.back()-1,i)) st.pop_back();
		st.push_back(i);
		while(st[head]!=i&&get_pt(st[head],st[head+1])<=i) head++;
//		for(int x:st) cout<<x<<'/'<<val(x-1,i)<<' ';cout<<endl;
//		for(int j=0;j<st.size()-1;j++) cout<<get_pt(st[j],st[j+1])<<' ';cout<<endl;
		f[i]=val(st[head]-1,i);
//		cout<<f[i]<<' '<<head<<endl;
	}
	
	cout<<f[n]<<endl;
}
