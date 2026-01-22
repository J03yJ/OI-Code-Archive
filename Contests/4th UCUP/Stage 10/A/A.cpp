#include<bits/stdc++.h>

using namespace std;

const int N=5e2+9;

int c[N],n;
vector<int> t[N];
inline int P(int x){
	int res;
	cout<<"+ "<<x<<endl;
	cin>>res;
	return res;
}
inline int D(){
	int res;
	cout<<'-'<<endl;
	cin>>res;
	return res;
}
inline void D(int t){while(t--) D();}

// int a[N],seed,cnt=0;
// inline void Init(){
// 	mt19937 rng(seed);
// 	for(int i=1;i<=n;i++) a[i]=rng()%n+1;
// }
// deque<int> q;
// inline int Q(){
// 	set<int> s;
// 	int cnt=0;
// 	for(int x:q) cnt+=s.insert(x).second;
// 	return cnt;
// }
// inline int P(int x){
// 	cnt++;
// 	q.push_back(a[x]);
// 	return Q();
// }
// inline void D(int x){
// 	cnt+=x;
// 	while(x--) q.pop_front();
// }
// inline void Debug(){
// 	for(int i=1;i<=n;i++){
// 		if(!t[i].size()) continue ;
// 		vector<int> tmp=t[i];
// 		for(int &x:tmp) x=c[x];
// 		if(count(tmp.begin(),tmp.end(),tmp.front())!=tmp.size()){
// 			cout<<"Wrong Answer on #"<<i<<endl;
// 			return ;
// 		}
// 	}
// 	cout<<"Accepted with "<<cnt<<" query(s)"<<endl;
// }

inline void Conquer(vector<int> z,vector<int> v){
	if(!v.size()) return ;
	// cout<<"Conquer : ";
	// for(int x:z) cout<<x<<' ';cout<<"| ";
	// for(int x:v) cout<<x<<' ';cout<<endl;
	if(z.size()==1){
		for(int x:v) c[x]=c[z.front()];
		return ;
	}
	vector<int> lv,rv;
	vector<int> lz,rz;
	for(int i=0;i<z.size()/2;i++) lz.push_back(z[i]);
	for(int i=z.size()/2;i<z.size();i++) rz.push_back(z[i]);
	int lst=0;
	for(int x:lz) lst=P(x);
	for(int x:v){
		int now=P(x);
		if(now>lst) rv.push_back(x);
		else lv.push_back(x);
		lst=now;
	}
	D(lz.size()+v.size());
	// cout<<" -> ";
	// for(int x:lz) cout<<x<<' ';cout<<"| ";
	// for(int x:lv) cout<<x<<' ';cout<<endl;
	// cout<<" -> ";
	// for(int x:rz) cout<<x<<' ';cout<<"| ";
	// for(int x:rv) cout<<x<<' ';cout<<endl;
	Conquer(lz,lv),Conquer(rz,rv);
}

signed main(){
	cin>>n;

	// cin>>n>>seed;
	// Init();

	int B=sqrt(n);

	vector<vector<int>> row;
	vector<int> lft(n);
	iota(lft.begin(),lft.end(),1);
	while(true){
		row.push_back(vector<int>());
		vector<int> tmp;
		int lst=0;
		for(int x:lft){
			int now=P(x);
			if(now>lst) row.back().push_back(x);
			else tmp.push_back(x);
			lst=now;
		}
		D(lft.size());
		lft=tmp;
		if(row.back().size()<=B) break ;
	}

	for(int i=0;i<row[0].size();i++) c[row[0][i]]=i+1;
	for(int i=1;i<row.size();i++) Conquer(row[i-1],row[i]);

	// for(auto v:row){
	// 	for(int x:v) cout<<x<<' ';cout<<endl;
	// }

	for(int x:lft){
		int lst=P(x);
		for(int y:row.back()){
			int now=P(y);
			if(now==lst) c[x]=c[y];
			lst=now;
		}
		D(row.back().size()+1);
	}

	cout<<"! "<<row[0].size()<<endl;
	for(int i=1;i<=n;i++) t[c[i]].push_back(i);
	for(int i=1;i<=row[0].size();i++){
		cout<<t[i].size()<<' ';
		for(int x:t[i]) cout<<x<<' ';cout<<endl;
	}

	// cout<<endl;
	// for(int i=1;i<=n;i++) cout<<i<<" : "<<a[i]<<endl;cout<<endl;
	// Debug();

	return 0;
}