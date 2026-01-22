#include<bits/stdc++.h>
using namespace std;

ifstream fin("stone.in");
ofstream fout("stone.out");
#define cin fin
#define cout fout

const int N=1e5+9;
int a[N];

int main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		bool flag=0;
		map<int,int> mp;
		
		int k=1e9+8,mn=1e9;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			mp[a[i]]++;
			if(mp[a[i]]>n/2) k=a[i];
			mn=min(mn,a[i]);
		}
		
		if(mn==k) cout<<"BaoBao"<<endl;
		else cout<<"DK"<<endl;
	}
	return 0;
}
