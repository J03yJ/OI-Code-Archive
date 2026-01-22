#include<bits/stdc++.h>

using namespace std;

ifstream fin("paper.in");
ofstream fout("paper.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=2e5+9;

int a[N],d[N],pre[N],suc[N],n;

signed main(){
	cin>>n;
	for(int i=1;i<n;i++) cin>>a[i];
	for(int i=1;i<n;i++) pre[i+1]=i,suc[i]=i+1;

	vector<int> stk(1);
	for(int i=2;i<n;i++){
		if(a[i]>a[stk.back()]) stk.push_back(i);
		if(a[i]<a[stk.back()]){
			int j=stk.back();
			pre[suc[i]]=pre[i],suc[pre[i]]=suc[i];
			pre[i]=pre[j],suc[i]=j;
			suc[pre[i]]=i,pre[j]=i;
			stk.pop_back();
		}
	}

	int x=1;
	while(x){
		cout<<x<<' ';
		if(suc[x]) d[min(x,suc[x])]++,d[max(x,suc[x])]--;
		x=suc[x];
	}
	cout<<endl;

	for(int i=1;i<n;i++) d[i]+=d[i-1];
	for(int i=1;i<n;i++) assert(d[i]==a[i]);

	return 0;
}