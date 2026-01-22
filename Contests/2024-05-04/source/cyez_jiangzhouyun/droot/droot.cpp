#include<bits/stdc++.h>
using namespace std;
const int N=2e5+9;

#define int long long

ifstream fin("droot.in");
ofstream fout("droot.out");
#define cin fin
#define cout fout

string s[N],t[N];
int scnt,tcnt;

int ans=1;
string Rev(string s){
	string res="";
	for(int i=s.size()-1;~i;i--) res+=s[i];
	return res;
}
bool Suc(string s,string t){
//	cout<<s<<' '<<t<<endl;
	if(s.size()>t.size()) return 0;
	for(int i=t.size()-1,j=s.size()-1;~j;i--,j--){
		if(s[j]!=t[i]) return 0;
	}
//	cout<<"Kate"<<endl;
	return 1;
}

signed main(){
	s[++scnt]="";
	t[++tcnt]="";
	int q;
	cin>>q;
	while(q--){
		int op,x;char c;
		cin>>op>>x>>c;
		if(op==1){
			s[++scnt]=s[x]+c;
			for(int i=1;i<=tcnt;i++) ans+=Suc(Rev(s[scnt]),t[i]);
		}else{
			t[++tcnt]=t[x]+c;
			for(int i=1;i<=scnt;i++) ans+=Suc(Rev(s[i]),t[tcnt]);
		}
		cout<<ans<<endl;
	}
	return 0;
}
