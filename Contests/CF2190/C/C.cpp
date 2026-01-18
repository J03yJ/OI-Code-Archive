#include<bits/stdc++.h>

using namespace std;

inline int Q(int i,int j){
	cout<<"? "<<i<<' '<<j<<endl;
	int c;
	cin>>c;
	if(c==-1) assert(0);
	return c;
}

int n;
inline void Solve(){
	cin>>n;

	int p=0,q=0,r=0;
	for(int i=n;i>1;i--){
		if(!Q(i-1,i)){
			if(!q) q=i;
		}else{
			if(q){
				p=i-1;
				break ;
			}
		}
	}

	if(!p){
		cout<<"! "<<-1<<endl;
		return ;
	}

	int j=p+1;
	r=q;
	vector<int> t1,ans(n+1,0);
	for(int i=n;i>q;i--){
		while(j<=q&&Q(i,j)){
			r=i;
			t1.push_back(j++);
		}
		if(j>p+1) t1.push_back(i);
	}
	while(j<=q) t1.push_back(j++);
	reverse(t1.begin(),t1.end());

	int t=0;
	vector<int> t2;
	for(int i:t1){
		if(!t&&Q(p,i)){
			t=i;
			t2.push_back(p);
		}
		t2.push_back(i);
	}
	
	j=p+1;
	for(int i=1;i<p;i++) ans[i]=i;
	for(int i=n;i>r;i--) ans[i]=i;
	ans[p]=t;
	for(int i:t2){
		if(i==t) continue ;
		ans[j++]=i;
	}

	cout<<"! ";for(int i=1;i<=n;i++) cout<<ans[i]<<' ';cout<<endl;
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}