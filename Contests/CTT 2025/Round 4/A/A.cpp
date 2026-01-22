#include<bits/stdc++.h>

using namespace std;

const int L=146;

signed main(){
	cout<<2*L+8<<' '<<4<<endl;

	int S1=1,S2=2,TR=-1,OK=0;
	int F1=L*2+3,F2=L*2+4,F3=L*2+5,CH=L*2+6;
	int LB=L*2+7,RB=L*2+8;
	int ST1=3,ED1=2+L,ST2=3+L,ED2=2+L+L;

	cout<<1<<' '<<2<<' '<<S2<<endl;// S1
	cout<<1<<' '<<3<<' '<<ST1<<endl;// S2
	cout<<0<<' '<<ST1+1<<' '<<TR<<' '<<F1<<' '<<TR<<' '<<TR<<endl;// ST1
	for(int i=ST1+1;i<ED1;i++) cout<<0<<' '<<i+1<<' '<<i-1<<' '<<TR<<' '<<TR<<' '<<TR<<endl;
	cout<<0<<' '<<LB<<' '<<ED1-1<<' '<<TR<<' '<<TR<<' '<<TR<<endl;// ED1
	cout<<0<<' '<<ST2+1<<' '<<RB<<' '<<F1<<' '<<TR<<' '<<TR<<endl;// ST2
	for(int i=ST2+1;i<ED2;i++) cout<<0<<' '<<i+1<<' '<<i-1<<' '<<TR<<' '<<TR<<' '<<TR<<endl;
	cout<<0<<' '<<LB<<' '<<ED2-1<<' '<<TR<<' '<<TR<<' '<<TR<<endl;// ED2
	cout<<1<<' '<<2<<' '<<F2<<endl;// F1
	cout<<0<<' '<<TR<<' '<<TR<<' '<<TR<<' '<<F3<<' '<<TR<<endl;// F2
	cout<<1<<' '<<3<<' '<<CH<<endl;// F3
	cout<<0<<' '<<ST1+1<<' '<<TR<<' '<<OK<<' '<<TR<<' '<<TR<<endl;// CH
	cout<<1<<' '<<0<<' '<<ED2<<endl;// LB
	cout<<1<<' '<<1<<' '<<ST2<<endl;// RB

	return 0;
}