#include<bits/stdc++.h>

using namespace std;

ifstream fin("bool.in");
ofstream fout("bool.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=3e5+9;

string op[N];
int a[N][2],f[N],imp[N],n;
inline void GetVal(int x){
	if(op[x]=="IN") f[x]=a[x][0];
	else if(op[x]=="NOT"){
		GetVal(a[x][0]);
		f[x]=!f[a[x][0]];
	}else{
		GetVal(a[x][0]),GetVal(a[x][1]);
		if(op[x]=="AND") f[x]=f[a[x][0]]&f[a[x][1]];
		else if(op[x]=="OR") f[x]=f[a[x][0]]|f[a[x][1]];
		else if(op[x]=="XOR") f[x]=f[a[x][0]]^f[a[x][1]];
	}
}
inline void FindImp(int x){
	if(op[x]=="IN") imp[x]=1;
	else if(op[x]=="NOT") FindImp(a[x][0]);
	else if(op[x]=="AND"){
		for(int k:{0,1}){
			if((!f[a[x][k]]&f[a[x][!k]])!=f[x]) FindImp(a[x][k]);
		}
	}else if(op[x]=="OR"){
		for(int k:{0,1}){
			if((!f[a[x][k]]|f[a[x][!k]])!=f[x]) FindImp(a[x][k]);
		}
	}else if(op[x]=="XOR"){
		for(int k:{0,1}){
			if((!f[a[x][k]]^f[a[x][!k]])!=f[x]) FindImp(a[x][k]);
		}
	}
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>op[i];
		if(op[i]=="NOT"||op[i]=="IN") cin>>a[i][0];
		else cin>>a[i][0]>>a[i][1];
	}

	GetVal(1);
	FindImp(1);

	for(int i=1;i<=n;i++) if(op[i]=="IN") cout<<(f[1]^imp[i]);
	cout<<endl;

	return 0;
}