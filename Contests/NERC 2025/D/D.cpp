#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=3e5+9;

int k[N],lx[N],rx[N],lp[N],rp[N],it[N],s[N],n;
vector<int> len[N];
multiset<int> ls,rs;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>k[i]>>lx[i]>>rx[i];
		len[i].resize(k[i]);
		for(int &x:len[i]) cin>>x;
		s[i]=accumulate(len[i].begin(),len[i].end(),0);
	}

	int ans=0;
	priority_queue<array<int,2>> q;
	for(int i=1;i<=n;i++){
		ls.insert(lp[i]=lx[i]);
		rs.insert(rp[i]=rx[i]-s[i]);
		it[i]=0;
		if(it[i]<k[i]) q.push({-(lp[i]+len[i][it[i]]),i});
	}

	ans=max(ans,*rs.begin()-*ls.rbegin());
	while(q.size()){
		int i=q.top()[1];
		q.pop();
		ls.erase(ls.find(lp[i]));
		rs.erase(rs.find(rp[i]));
		ls.insert(lp[i]+=len[i][it[i]]);
		rs.insert(rp[i]+=len[i][it[i]]);
		it[i]++;
		if(it[i]<k[i]) q.push({-(lp[i]+len[i][it[i]]),i});
		ans=max(ans,*rs.begin()-*ls.rbegin());
	}

	cout<<ans<<endl;

	return 0;
}