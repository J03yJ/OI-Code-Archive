#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

int a[100],n,m;
inline int S(int i,int j){
	int x;
	cout<<i<<' '<<j<<endl;
	cout.flush();
	cin>>x;
	if(x==1) exit(0);
	return x;
}
// inline int S(int i,int j){
// 	a[i]+=j,a[i]=(a[i]-1)%n+1;
// 	int cnt=0;
// 	map<int,int> mp;
// 	for(int i=1;i<=n;i++) if(!mp[a[i]]) mp[a[i]]=1,cnt++;
// 	// cerr<<"Opt "<<i<<" += "<<j<<endl;
// 	if(cnt==1){
// 		// cerr<<"Succeeded."<<endl;
// 		// for(int i=1;i<=n;i++) cerr<<a[i]<<' ';cerr<<endl;
// 		exit(0);
// 	}
// 	return cnt;
// }
inline vector<int> Get(int x){
	vector<int> tmp(n,0);
	for(int i=1;i<=n;i++) tmp[i%n]=S(x,1);
	int mn=*min_element(tmp.begin(),tmp.end());
	for(auto &x:tmp) x=(x==mn);
	tmp[0]=1;
	return tmp;
}
inline vector<int> Shift(vector<int> v,int k){
	vector<int> tmp(n);
	for(int i=0;i<n;i++) tmp[(i+k%n+n)%n]=v[i];
	return tmp;
}
inline int RollCount(vector<int> v){
	int cnt=0;
	for(int i=0;i<n;i++) cnt+=(Shift(v,i)==v);
	return cnt;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>m;
	// cin>>n;
	// for(int i=1;i<=n;i++) cin>>a[i];

	// for(int sta=0;sta<(1<<n);sta++){
	// 	vector<int> tmp(n,0);
	// 	for(int i=0;i<n;i++) tmp[i]=sta>>i&1;
	// 	for(int x:tmp) cout<<x<<' ';cout<<": "<<RollCount(tmp)<<endl;
	// }
	
	int cnt=0;
	vector<int> tmp=Get(1);
	while(RollCount(tmp)>1){
		S(1,1);
		tmp=Get(1);
		cnt++;
		assert(cnt<=n*2);
	}

	vector<int> c(n+1,0);
	for(int i=2;i<=n;i++){
		vector<int> pmt=Get(i);
		for(int j=0;j<n;j++){
			if(Shift(tmp,j)==pmt){
				c[i]=j;
				break ;
			}
			if(j==n-1) assert(0);
		}
	}
	for(int i=1;i<=n;i++) S(i,c[i]);
	// assert(0);

	return 0;
}