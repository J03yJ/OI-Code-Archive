#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	srand(time(0));
	while(true){
		int n=rand()%20+1;
		string s="";
		for(int i=1;i<=n;i++) s+=char(rand()%26+'a');
		ofstream fout("A.in");
		fout<<n<<endl<<s<<endl;
		fout.close();
		system("A < A.in > A.out");
		system("Asol < A.in > A.ans");
		if(system("fc A.out A.ans > tmp")){
			system("type A.in");
			system("pause");
		}else cout<<"Accepted"<<endl;
	}
}
