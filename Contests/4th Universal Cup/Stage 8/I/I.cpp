#include<bits/stdc++.h>

using namespace std;

signed main(){
	map<string,int> mp;
	
	mp["UW"]=11;
	mp["UJ"]=9;
	mp["UWR"]=8;
	mp["MAP"]=7;
	mp["PW"]=6;
	mp["AGH"]=5;
	mp["PG"]=4;
	mp["NLU"]=3;
	mp["PUT"]=3;
	mp["PO"]=2;
	mp["PWR"]=2;
	mp["SGGW"]=2;
	mp["UMCS"]=2;
	mp["UR"]=2;
	mp["ZUT"]=2;
	mp["DTP"]=1;
	mp["GOO"]=1;
	mp["HUA"]=1;
	mp["KUL"]=1;
	mp["PL"]=1;
	mp["PM"]=1;
	mp["PS"]=1;
	mp["UAM"]=1;
	mp["UG"]=1;
	mp["UMK"]=1;
	mp["UO"]=1;
	mp["WAT"]=1;

	string tar;
	cin>>tar;

	queue<string> buf;
	while(mp[tar]-->0) buf.push(tar);
	for(auto p:mp) while(p.second-->0) buf.push(p.first);

	string ans[8][10];
	for(int p:{0,1}){
		for(int q:{0,1}){
			for(int i=0;i<4;i++){
				for(int j=0;j<5;j++){
					ans[i<<1|p][j<<1|q]=buf.front();
					buf.pop();
				}
			}
		}
	}

	for(int i=0;i<8;i++){
		for(int j=0;j<10;j++) cout<<ans[i][j]<<' ';
		cout<<endl;
	}

	return 0;
}