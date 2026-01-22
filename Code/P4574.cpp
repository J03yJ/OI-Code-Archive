#include<bits/stdc++.h>
using namespace std;

#define int long long

int cnt(int x){
	int cnt=0;
	while(x){
		if(x&1) cnt++;
		x>>=1;
	}
	return cnt;
}
int Cnt(int x){
	int cnt=0;
	while(x){
		cnt++;
		x>>=1;
	}
	return cnt;
}

signed main(){
	int a,b,c;
	cin>>a>>b>>c;
	int x=cnt(a),y=cnt(b),z=cnt(c);
	if(x<y) swap(x,y);
	int mx=max(Cnt(a),max(Cnt(b),Cnt(c)));
	
	if(z<=y){
		if(Cnt(((1<<x)-1)+((1<<z)-1|((1<<y-z)-1<<x)))>mx) cout<<-1<<endl;
		else cout<<((1<<x)-1)+((1<<z)-1|((1<<y-z)-1<<x))<<endl;
	}
	else if(z<=y){
		if(Cnt(((1<<x)-1)+((1<<y)-1<<z-y))>mx) cout<<-1<<endl;
		else cout<<((1<<x)-1)+((1<<y)-1<<z-y)<<endl;
	}
	else if(z<=x+y){
		if(Cnt(((1<<x)-1<<z-x)+((1<<z-x)-1|((1<<x+y-z)-1<<z+z-x-y)))>mx) cout<<-1<<endl;
		else cout<<(((1<<x)-1<<z-x)+((1<<z-x)-1|((1<<x+y-z)-1<<z+z-x-y)))<<endl;
	}
	else cout<<-1<<endl;
	
	return 0;
}
