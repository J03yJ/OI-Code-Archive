#include<bits/stdc++.h>

using namespace std;

ifstream fin("lcp.in");
ofstream fout("lcp.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;	
const int N=3e5+9;

int n;
char a[N],b[N],c[N];

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++) cin>>b[i];
		for(int i=1;i<=n;i++) cin>>c[i];

		int ans=3,p=a[1]-'a';
		int s[26];
		memset(s,0,sizeof s);
		for(int i=2;i<=n;i++){
			int q=c[i]-'a';
			for(int j=0;j<26;j++){
				if(!s[j]) continue ;
				int cnt=(p==q)+(p==j)+(q==j);
				ans=min(ans,cnt);
			}
			s[b[i]-'a']|=1;
		}

		cout<<ans<<endl;
	}

	return 0;
}