#include<bits/stdc++.h>

using namespace std;

signed main(){
	int T;
	cin>>T;
	while(T--){
		string s;
		cin>>s;
		
		int n=s.size(),a=0,b=0,a1=0,a2=0,la=-1,fb=-1,len=0;
		for(int i=0;i<n;i++){
			if(s[i]=='a') a++;
			else b++;
		}
		for(int i=0;i<n;i++) if(s[i]=='a') la=i;
		for(int i=n-1;~i;i--) if(s[i]=='b') fb=i;
		for(int i=0;i<n;i++){
			if(s[i]=='a'&&(!i||s[i-1]=='b')&&(i+1>=n||s[i+1]=='b')) a1++;
		}
		for(int i=0;i<n;i++){
			if(s[i]=='a') a2++;
			if(i&&s[i]=='a'&&s[i-1]=='a') a2--;
		}
		a2-=a1;

		if(a==n||b==n) cout<<s<<endl;
		else if(la==n-1){
			for(int i=la;~i;i--){
				if(s[i]=='a') len++;
				else break ;
			}
			if(len>1) a2--;
			else if(len>0) a1--;
			int cnt=a1+(a2<<1);
			cnt+=cnt&1;
			for(int i=0;i<b;i++) cout<<'b';
			for(int i=0;i<a-cnt;i++) cout<<'a';
			cout<<endl;
		}else if(~a&1){
			for(int i=0;i<b;i++) cout<<'b';
			cout<<endl;
		}else if(la<fb){
			cout<<'a';
			for(int i=0;i<b;i++) cout<<'b';
			cout<<endl;
		}else if(n-la-1<=2){
			for(int i=0;i<n;i++){
				if(s[i]=='b') cout<<s[i];
				else if(i==la) cout<<s[i];
			}
			cout<<endl;
		}else{
			for(int i=0;i<n;i++){
				if(s[i]=='a') len++;
				else break ;
			}
			if(a2-(len>1)) a2--;
			else a1--;
			int cnt=a1+(a2<<1);
			cnt+=cnt&1;
			for(int i=0;i<b-2;i++) cout<<'b';
			for(int i=0;i<a-cnt;i++) cout<<'a';
			cout<<endl;
		}
	}

	return 0;
}