#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
inline int Count(string s){
	int cnt=0;
	for(char c:s) if(c=='0') cnt++;
	return cnt;
}
inline int Prefix(string s){
	int cnt=0;
	for(char c:s){
		if(c=='1') return cnt;
		else cnt++;
	}
	return cnt;
}
inline int Suffix(string s){
	reverse(s.begin(),s.end());
	return Prefix(s);
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		string s(n,'#'),t(n,'#');
		for(char &c:s) cin>>c;
		for(char &c:t) cin>>c;

		if(Count(s)!=Count(t)) cout<<"No"<<endl;
		else if(n-Count(s)==1){
			if(s.front()!=t.front()) cout<<"No"<<endl;
			else if(s.back()!=t.back()) cout<<"No"<<endl;
			else cout<<"Yes"<<endl;
		}else cout<<"Yes"<<endl;
	}

	return 0;
}