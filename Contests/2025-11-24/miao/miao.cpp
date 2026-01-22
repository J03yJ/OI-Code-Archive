#include<bits/stdc++.h>

using namespace std;

ifstream fin("miao.in");
ofstream fout("miao.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=2e6+9;

int a[N],cnt[N],n,m;
vector<array<int,2>> b,ans;
inline bool Check(int l,int r){
	int mid=l+r>>1;
	int lc=l<mid?cnt[mid-1]-cnt[l]:0,rc=r>mid?cnt[r-1]-cnt[mid]:0;
	return cnt[mid+lc]-cnt[mid-rc-1];
}
inline void Constr(int l,int r){
	int mid=l+r>>1;
	int lc=l<mid?cnt[mid-1]-cnt[l]:0,rc=r>mid?cnt[r-1]-cnt[mid]:0,p=0;
	for(int i=mid-rc;i<=mid+lc;i++) if(b[i][1]>1) p=i;
	if(p<=mid){
		int c=mid-p;
		for(int i=mid+1;i<r;i++) if(c&&b[i][1]>1) b[i][0]=-b[i][0],c--;
	}else{
		int c=p-mid;
		for(int i=mid-1;i>l;i--) if(c&&b[i][1]>1) b[i][0]=-b[i][0],c--;
	}
	b[p][0]=-b[p][0];
	vector<array<int,2>> stk;
	bool flag=0;
	for(int i=l;i<=r;i++){
		for(int j=1;j<=b[i][1];j++) ans.push_back({1,0});
		if(b[i][0]>0){
			if(stk.size()&&stk.back()[0]==b[i][0]){
				if(flag){
					ans.push_back({2,stk.back()[1]+b[i][1]});
					stk.pop_back();
				}else stk.back()[1]+=b[i][1];
			}else stk.push_back(b[i]);
		}else ans.push_back({2,b[i][1]});
		if(i==p) flag=1;
	}
}
inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	b.push_back({0,0});
	for(int i=1;i<=n;i++){
		if(b.back()[0]!=a[i]) b.push_back({a[i],1});
		else b.back()[1]++;
	}

	m=b.size()-1;
	for(int i=1;i<=m;i++) cnt[i]=cnt[i-1]+(b[i][1]>1);

	if(m&1){
		if(!Check(1,m)) cout<<"No"<<endl;
		else{
			cout<<"Yes"<<endl;
			Constr(1,m);
			cout<<ans.size()<<endl;
			for(auto t:ans){
				if(t[0]==1) cout<<t[0]<<endl;
				else cout<<t[0]<<' '<<t[1]<<endl;
			}
		}
	}else{
		bool flag=0;
		for(int i=1;i<=m;i+=2){
			if(!Check(1,i)||!Check(i+1,m)) continue ;
			cout<<"Yes"<<endl;
			Constr(1,i),Constr(i+1,m);
			cout<<ans.size()<<endl;
			for(auto t:ans){
				if(t[0]==1) cout<<t[0]<<endl;
				else cout<<t[0]<<' '<<t[1]<<endl;
			}
			flag=1;
			break ;
		}
		if(!flag) cout<<"No"<<endl;
	}

	b.clear(),ans.clear();
	for(int i=1;i<=m;i++) cnt[i]=0;
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}