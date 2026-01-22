#include<bits/stdc++.h>
using namespace std;

const int N=2e6+9;

namespace L{
	int n,x[N],y[N];
	int m,x1[N],y1[N],x2[N],y2[N];
	int vcnt=1e7+1,val[20000009];
	int ans[N][4];
	
	int tr[N<<2];
	void add(int x,int k){
		while(x<=vcnt){
			tr[x]+=k;
			x+=x&-x;
		}
	}
	int ask(int x){
		int sum=0;
		while(x){
			sum+=tr[x];
			x&=x-1;
		}
		return sum;
	}
	int find(int k){
		return k+1;
//		return lower_bound(val+1,val+vcnt+1,k)-val;
	}
	
	
	int p[N];
	bool cmp(int a,int b){
		return x[a]!=x[b]?(x[a]<x[b]):(y[a]<y[b]);
	}
	
	int main(){
		cin>>n>>m;
		for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
		for(int i=1;i<=m;i++) cin>>x1[i]>>y1[i]>>x2[i]>>y2[i];
		
//		for(int i=1;i<=n;i++) val[++vcnt]=y[i];
//		for(int i=1;i<=m;i++) val[++vcnt]=y1[i]-1,val[++vcnt]=y2[i];
//		sort(val+1,val+1+vcnt);
//		vcnt=unique(val+1,val+vcnt+1)-val-1;
		
		for(int i=1;i<=n;i++) p[i]=i;
		sort(p+1,p+n+1,cmp);
		
		vector<pair<pair<int,int>,pair<int,int>>> q;
		for
		
		(int i=1;i<=m;i++){
			q.push_back({{x2[i],y2[i]},{i,0}});
			q.push_back({{x1[i]-1,y2[i]},{i,1}});
			q.push_back({{x2[i],y1[i]-1},{i,2}});
			q.push_back({{x1[i]-1,y1[i]-1},{i,3}});
		}
		sort(q.begin(),q.end());
		
		int i=1;
		for(pair<pair<int,int>,pair<int,int>> Q:q){
			for(;i<=n&&x[p[i]]<=Q.first.first;i++) add(find(y[p[i]]),1);
//			cout<<Q.first.first<<' '<<Q.first.second<<':'<<ask(find(Q.first.second))<<endl;
			ans[Q.second.first][Q.second.second]+=ask(find(Q.first.second)); 
		}
		
		for(int i=1;i<=m;i++){
//			cout<<ans[i][0]<<' '<<ans[i][1]<<" "<<ans[i][2]<<' '<<ans[i][3]<<endl;
			cout<<ans[i][0]-ans[i][1]-ans[i][2]+ans[i][3]<<endl;
		}
		
		return 0;
	}
}

int main(){
	return L::main();
}
