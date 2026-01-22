#include<bits/stdc++.h>

using namespace std;

signed main(){
	int n;
	cin>>n;

	int k=0;
	while(n%5==0){
		n/=5;
		k++;
		if(2*k>n){
			k--;
			n*=5;
			break ;
		}
	}

	for(int i=1;i<=k;i++) cout<<"AI";
	for(int i=1;i<=n-2*k;i++) cout<<'J';
	cout<<endl;

	return 0;
}