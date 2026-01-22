#include<bits/stdc++.h>

using namespace std;

ifstream fin("logic.in");
ofstream fout("logic.out");
#define cin fin
#define cout fout
#define endl '\n'

inline int Dig(string s){
	int x=0;
	for(char c:s) x=x*10+c-'0';
	return x;
}

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		vector<string> s(2*n-1);
		for(string &str:s) cin>>str;
		vector<int> x(n+1);
		for(int i=1;i<=n;i++) cin>>x[i];

		vector<array<int,2>> stk;
		for(string &str:s){
			if(str[0]=='x'){
				int i=Dig(str.substr(1));
				array<int,2> tmp={0,0};
				tmp[!x[i]]=1;
				stk.push_back(tmp);
			}else if(str[0]=='|'){
				array<int,2> p=stk.end()[-1],q=stk.end()[-2],tmp={n+1,n+1};
				stk.pop_back(),stk.pop_back();
				for(int s:{0,1}){
					for(int t:{0,1}) tmp[s|t]=min(tmp[s|t],p[s]+q[t]);
				}
				stk.push_back(tmp);
			}else if(str[0]=='&'){
				array<int,2> p=stk.end()[-1],q=stk.end()[-2],tmp={n+1,n+1};
				stk.pop_back(),stk.pop_back();
				for(int s:{0,1}){
					for(int t:{0,1}) tmp[s&t]=min(tmp[s&t],p[s]+q[t]);
				}
				stk.push_back(tmp);
			}
		}

		cout<<max(stk.back()[0],stk.back()[1])<<endl;
	}

	return 0;
}