#include<bits/stdc++.h>

using namespace std;

inline bool Check(string &s){
	int cnt=0;
	for(char c:s){
		if(c=='(') cnt++;
		else{
			if(!cnt) return 0;
			cnt--;
		}
	}
	return !cnt;
}

signed main(){
	int T;
	cin>>T;
	while(T--){
		int k;
		string s;
		cin>>s>>k;

		if(!Check(s)) cout<<"First"<<endl;
		else if(k&1) cout<<"First"<<endl;
		else{
			int c=(s.size()-k)>>1;
			vector<int> b(s.size(),0),stk;
			for(int i=0;i<s.size();i++){
				if(s[i]=='(') stk.push_back(i);
				else{
					int j=stk.back();
					stk.pop_back();
					b[i]=j,b[j]=i;
				}
			}
			int p=0;
			while(p<s.size()&&b[p]+p==s.size()-1) p++;
			if(c<=p) cout<<"Second"<<endl;
			else{
				string t=s.substr(p,s.size()-2*p);
				int cl=0,ct=0;
				for(int i=0;i<t.size();i+=2){
					if(t[i]=='('&&t[i+1]==')') cl++;
					else break ;
				}
				for(int i=t.size()-1;~i;i-=2){
					if(t[i-1]=='('&&t[i]==')') ct++;
					else break ;
				}
				c-=p;
				if(c>min(cl,ct)) cout<<"First"<<endl;
				else cout<<"Second"<<endl;
			}
		}
	}
	
	return 0;
}