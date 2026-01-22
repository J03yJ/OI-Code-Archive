#include<bits/stdc++.h>
using namespace std;
#define int long long

//ifstream fin("sky.in");
//ofstream fout("sky.out");
//#define cin fin
//#define cout fout

int d[19],ans,k;
int sum(__int128 x){
	int sum=0;
	while(x) sum+=x%10,x/=10;
	return sum;
}
int solve(__int128 x){
	int cnt=0;
	while(x>9) cnt++,x=sum(x);
	return cnt;
}
unordered_map<int,bool> mp;
void dfs(int stp,__int128 x){
//	cout<<stp<<' '<<(int)x<<endl;
	if(stp>d[ans]) return ;
//	if(mp[x]) continue ;
//	mp[x]=1;
	if(x<10){
		d[x]=min(d[x],stp);
//		if(x==ans) return ;
	}
	dfs(stp+1,sum(x));
	dfs(stp+1,x*k);
}
signed main(){
	int T;
	cin>>T;
	while(T--){
		int x;
		cin>>x>>k;
		memset(d,0x3f,sizeof(d));
		__int128 p=x;
		for(int i=0;i<9;i++){
			d[(p-1)%9+1]=min(d[(p-1)%9+1],i+solve(p));
			p*=k;
		}
		for(int i=1;i<10;i++){
			if(d[i]<1e6){
				ans=i;
				break ;
			}
		}
		dfs(0,x);
		cout<<ans<<' '<<d[ans]<<endl;
	}
	return 0;
}
