#include<bits/stdc++.h>

using namespace std;

ifstream fin("xor.in");
ofstream fout("xor.out");
#define cin fin
#define cout fout
#define endl '\n'

inline int Log2(int x){return !x?-1:__lg(x);}

signed main(){
	int T;
	cin>>T;
	while(T--){
		int a,b,c;
		cin>>a>>b>>c;
		if(!a&&!b){
			if(c){
				cout<<-1<<endl;
				continue ;
			}else{
				cout<<0<<endl<<endl;
				continue ;
			}
		}

		vector<int> ans;
		ans.reserve(64);
		auto Opr=[&a,&b,&ans](int o){
			if(o==1) a<<=1;
			else if(o==2) b>>=1;
			else if(o==3) a^=b;
			else b^=a;
			ans.push_back(o);
		};

		if(Log2(a)<Log2(b)) Opr(3);
		if(Log2(b)<Log2(a)) Opr(4);
		int lc=max(Log2(a),Log2(c)),la=Log2(a);
		for(int k=0;k<=la;k++){
			if((a>>la-k&1)!=(c>>lc-k&1)) Opr(3);
			if(b>1) Opr(2);
		}
		for(int k=lc-la-1;~k;k--){
			Opr(1);
			if(c>>k&1) Opr(3);
		}
		Opr(2);
		Opr(4);
		
		cout<<ans.size()<<endl;
		for(int o:ans) cout<<o<<' ';cout<<endl;
	}

	return 0;
}