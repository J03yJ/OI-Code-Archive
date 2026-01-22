#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;

int n;
char s[N];
inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i];

	int cnt=0;
	for(int i=n;i>=1;i--){
		if(s[i]=='(') cnt++;
		else{
			if(s[i+1]=='('&&cnt>1){
				cout<<n-2<<endl;
				return ;
			}
		}
	}
	cout<<-1<<endl;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}