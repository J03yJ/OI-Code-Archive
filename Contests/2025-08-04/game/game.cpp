#include<bits/stdc++.h>

using namespace std;

ifstream fin("game.in");
ofstream fout("game.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=2e5+9;

int x[N],y[N],n;
inline int S(int x,int y){return y?(x/y&1)^S(y,x%y):0;}
inline int SG(int x,int y){return S(x,y)^S(x-1,y)^S(x,y-1)^S(x-1,y-1);}

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>x[i]>>y[i];

		int s=0;
		for(int i=1;i<=n;i++) s^=SG(x[i],y[i]);
		
		if(s) cout<<"FIRST"<<endl;
		else cout<<"SECOND"<<endl;
	}
	return 0;
}