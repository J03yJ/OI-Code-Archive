#include<bits/stdc++.h>

using namespace std;

ifstream inf("miao.in");
ifstream ouf("miao.out");

signed main(){
	int T;
	inf>>T;
	
	for(int o=1;o<=T;o++){
		int n;
		inf>>n;
		vector<int> a(n),cur;
		for(int &x:a) inf>>x;
		
		string tmp;
		ouf>>tmp;
		if(tmp=="No") continue ;
		int m,i=0;
		ouf>>m;
		while(m--){
			int op;
			ouf>>op;
			if(op==1){
				if(i>=n){
					cerr<<"#"<<o<<" : Op-1 Out Of Range"<<endl;
					return 0;
				}
				cur.push_back(a[i++]);
			}else{
				int x;
				ouf>>x;
				int c=-1;
				while(x--){
					if(!cur.size()){
						cerr<<"#"<<o<<" : Op-2 Not Enough"<<endl;
						return 0;
					}
					int p=cur.back();
					cur.pop_back();
					if(c!=-1&&p!=c){
						cerr<<"#"<<o<<" : Op-2 Not Same"<<endl;
						return 0;
					}else c=p;
				}
			}
			for(int x:cur) cerr<<x<<' ';cerr<<endl;
		}
		if(cur.size()){
			cerr<<"#"<<o<<" : Stack Not Empty"<<endl;
			return 0;
		}
	}

	cerr<<"Accepted"<<endl;

	return 0;
}