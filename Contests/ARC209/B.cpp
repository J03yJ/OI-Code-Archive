#include<bits/stdc++.h>

using namespace std;

inline string Insert(string s,int t,char c){
	string r;
	for(int i=0;i+1<s.size();i++){
		r.push_back(s[i]);
		if(s[i]==s[i+1]){
			if(t) r.push_back(c),t--;
		}
	}
	if(s.size()) r.push_back(s.back());
	s=r;
	r.clear();
	for(int i=0;i+1<s.size();i++){
		r.push_back(s[i]);
		if(s[i]!=c&&s[i+1]!=c){
			if(t) r.push_back(c),t--;
		}
	}
	if(s.size()) r.push_back(s.back());
	if(t) r.insert(r.begin(),c),t--;
	while(t--) r.push_back(c);
	return r;
}

signed main(){
	int T;
	cin>>T;
	while(T--){
		string s;
		cin>>s;
		int n=s.size();

		int cnt[26];
		memset(cnt,0,sizeof cnt);
		for(char c:s) cnt[c-'a']++;

		int p=max_element(cnt,cnt+26)-cnt;
		if(cnt[p]<=n-cnt[p]){
			string r;
			int id[26];
			iota(id,id+26,0);
			sort(id,id+26,[&](int i,int j){return cnt[i]<cnt[j];});
			for(int i=0;i<26;i++){
				int j=id[i];
				r=Insert(r,cnt[j],j+'a');
			}
			cout<<r<<endl;
		}else{
			string tmp;
			for(int i=0;i<26;i++){
				if(i==p) continue ;
				while(cnt[i]--) tmp.push_back(i+'a');
			}
			
			int m=n-cnt[p]+1;
			vector<int> res(m,0);
			for(int i=0;i<cnt[p]%m;i++) res[i]=cnt[p]/m+1;
			for(int i=cnt[p]%m;i<m;i++) res[i]=cnt[p]/m;

			for(int i=0;i+1<m;i++){
				if(res[i]%2==0&&res[i]==res[i+1]){
					res[i]++,res[i+1]--;
				}
			}
			for(int i=0;i<m;i++){
				if(res[i]%2==0){
					swap(res[i],res[0]);
					break ;
				}
			}

			string r;
			for(int i=0;i<m;i++){
				while(res[i]--) r.push_back(p+'a');
				if(i+1<m) r.push_back(tmp[i]);
			}

			cout<<r<<endl;
		}
	}
	
	return 0;
}