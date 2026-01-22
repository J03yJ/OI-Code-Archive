#include<bits/stdc++.h>

using namespace std;

ifstream fin("bounce.in");
ofstream fout("bounce.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=1e6+9;

int ans[21],cnt[21],n,q;
inline int CalcAns(vector<int> &v,int x){

}
inline void GetAns(vector<int> &v){for(int i=1;i<=20;i++) ans[i]=CalcAns(v,i);}
inline void Work1(vector<int> &v,int x){
	if(!cnt[x]) return ;
	vector<int> u;
	for(int y:v){
		if(y%x==1){
			for(int i=1;i<=20;i++) if(y%i==1) cnt[i]--;
		}else u.push_back(y);
	}
	v=u;
}
inline void Work2(vector<int> &v,int x){
	vector<int> u;
	for(int i=0;i<v.size();i++){
		if(i%x==0){
			for(int j=1;j<=20;j++) if(v[i]%j==1) cnt[j]--;
		}else u.push_back(v[i]);
	}
	v=u;
}

signed main(){
	cin>>n>>q;
	for(int i=1;i<=20;i++) cnt[i]=(n-1)/i+1;
	vector<int> cur(n);
	iota(cur.begin(),cur.end(),1);

	while(q--){
		int op,m;
		cin>>op>>m;
		if(op==1) Work1(cur,m);
		else if(op==2) Work2(cur,m);
		else cout<<ans[m]<<endl;
	}

	return 0;
}