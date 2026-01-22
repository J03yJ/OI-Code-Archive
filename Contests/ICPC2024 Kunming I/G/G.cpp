#include<bits/stdc++.h>

using namespace std;

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;

		if(n==1||n%4==0) cout<<"impossible"<<endl;
		else{
			int cur=0;
			list<int> s;
			for(int i=0;i<n;i++) s.push_back(i);
			
			for(int i=0;i<n;i++){
				if(s.front()^cur){
					cur^=s.front();
					cout<<s.front()<<' ';
					s.pop_front();
				}else{
					int x=s.front();
					s.pop_front();
					cur^=s.front();
					cout<<s.front()<<' ';
					s.pop_front();
					s.push_front(x);
				}
			}
			cout<<endl;
		}
	}

	return 0;
}