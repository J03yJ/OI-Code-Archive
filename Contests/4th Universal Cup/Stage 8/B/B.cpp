#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;

int a[N],b[N],tr[N],n;
inline void Add(int x,int k){while(x<=n) tr[x]+=k,x+=x&-x;}
inline int Ask(int x){int sum=0;while(x) sum+=tr[x],x&=x-1;return sum;}
inline int Ask(int l,int r){return Ask(r)-Ask(l-1);}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],b[a[i]]=i;

	int ans=n;
	deque<int> q;
	for(int i=n;i>=1;i--){
		if(!q.size()||b[q.front()]>b[i]) q.push_front(i);
		else while(q.size()&&b[q.back()]>b[i]) q.pop_back();
		ans=min(ans,n-signed(q.size()));
	}

	cout<<ans<<endl;
	
	return 0;
}