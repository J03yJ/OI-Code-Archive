#include<bits/stdc++.h>

using namespace std;

ifstream fin("change.in");
ofstream fout("change.out");
#define cin fin
#define cout fout
#define endl '\n'

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		vector<char> val(n);
		vector<string> s((n<<1)-1);
		for(auto &o:s) cin>>o;
		for(auto &c:val) cin>>c;

		auto Decode=[](string s){
			int num=0;
			for(int i=1;i<s.size();i++){
				num*=10;
				num+=s[i]-'0';
			}
			return num;
		};
		
		vector<array<int,2>> stk;
		for(string &o:s){
			if(o.front()=='x'){
				int x=Decode(o)-1;
				if(val[x]=='0') stk.push_back({0,1});
				else stk.push_back({1,0});
			}else if(o.front()=='|'){
				array<int,2> x=stk.end()[-1],y=stk.end()[-2];
				stk.erase(stk.end()-2,stk.end());
				stk.push_back({x[0]+y[0],min(min(x[0]+y[1],x[1]+y[0]),x[1]+y[1])});
			}else if(o.front()=='&'){
				array<int,2> x=stk.end()[-1],y=stk.end()[-2];
				stk.erase(stk.end()-2,stk.end());
				stk.push_back({min(x[0]+y[0],min(x[0]+y[1],x[1]+y[0])),x[1]+y[1]});
			}
		}

		cout<<max(stk.back()[0],stk.back()[1])<<endl;
	}

	return 0;
}