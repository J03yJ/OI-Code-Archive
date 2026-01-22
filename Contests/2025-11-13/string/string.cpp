#include<bits/stdc++.h>

using namespace std;

ifstream fin("string.in");
ofstream fout("string.out");
#define cin fin
#define cout fout
#define endl '\n'

int n;
char c[200009];
inline int S(int l,int r,char x){
	if(l==r) return c[l]!=x;
	else{
		int mid=l+r>>1;
		int ans1=mid-l+1-count(c+l,c+mid+1,x)+S(mid+1,r,x+1);
		int ans2=r-mid-count(c+mid+1,c+r+1,x)+S(l,mid,x+1);
		return min(ans1,ans2);
	}
}

int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>c[i];

	cout<<S(1,n,'a')<<endl;
}