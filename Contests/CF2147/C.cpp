#include<bits/stdc++.h>

using namespace std;

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		string c;
		cin>>c;

		auto Check=[](string c){
			bool flag=0;
			if(c.front()=='1'){
				for(int i=0,oc=0,occ=0,xcc=0;i<c.size();i++){
					if(c[i]=='0'){
						oc++,occ++;
						xcc=0;
						if(occ>1) break ;
					}else{
						xcc++;
						occ=0;
						if(xcc>1) flag|=oc&1;
					}
					if(xcc&&i==c.size()-1) flag|=oc&1;
				}
			}
			return flag;
		};

		bool flag=Check(c)|Check(string(c.rbegin(),c.rend()));
		vector<int> tmp(n,0);
		for(int i=0;i+1<n;i++){
			if(c[i]=='1'&&c[i+1]=='1') tmp[i]=tmp[i+1]=1;
		}
		for(int i=0,j=-1;i<n;i++){
			if(!tmp[i]) continue ;
			if(~j) flag|=Check(c.substr(j,i-j+1));
			j=i;
		}

		if(flag) cout<<"NO"<<endl;
		else cout<<"YES"<<endl;
	}

	return 0;
}