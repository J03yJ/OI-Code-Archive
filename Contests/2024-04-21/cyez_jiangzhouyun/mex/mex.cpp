#include<bits/stdc++.h>
using namespace std;
#define int long long

ifstream fin("mex.in");
ofstream fout("mex.out");
#define cin fin
#define cout fout

signed main(){
	int n;
	cin>>n;
	cout<<2*n-1<<endl;
	
	int mid=n+1>>1;
	int sum=0,l=mid,r=mid;
	sum+=l*(n-r+1);
	for(int i=1;i<=n;i++){
		if(!l){
			r++;
			sum+=l*(n-r+1);
			continue ;
		}
		if(r>n){
			l--;
			sum+=l*(n-r+1);
			continue ;
		}
		if((l-1)*(n-r+1)>l*(n-r)){
			l--;
			sum+=l*(n-r+1);
		}else{
			r++;
			sum+=l*(n-r+1);
		}
	}
	cout<<sum<<endl;
	return 0;
}
