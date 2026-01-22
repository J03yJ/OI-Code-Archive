#include<bits/stdc++.h>

using namespace std;

ifstream fin("say.in");
ofstream fout("say.out");
#define cin fin
#define cout fout
#define endl '\n'

signed main(){
	int T;
	cin>>T;
	while(T--){
		string s;
		cin>>s;
		if(~s.back()&1){
			string t;
			int lst=0;
			for(char c:s){
				int x=c-'0'+lst;
				lst=(x&1)*10;
				t.push_back('0'+(x>>1));
			}
			cout<<t<<endl;
			cout<<t<<endl;
			cout<<t<<endl;
		}
	}

	return 0;
}