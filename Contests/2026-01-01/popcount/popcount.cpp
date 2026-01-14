#include<bits/stdc++.h>

using namespace std;

ifstream fin("popcount.in");
ofstream fout("popcount.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=(1<<10)+9;

int a[N],n,m;

signed main(){
	cin>>n>>m;

	int lim=max(n,m);
	for(int i=1;i<=lim;i++){
		for(int j=(1<<i-1);j<(1<<i);j++){
			a[j]=(a[j-(1<<i-1)]^a[(1<<i-1)-1])|(1<<i-1);
		}
	}

	for(int i=0;i<(1<<n);i++){
		for(int j=0;j<(1<<m);j++){
			cout<<(a[i]<<m|a[j])<<' ';
		}
		cout<<endl;
	}

	return 0;
}