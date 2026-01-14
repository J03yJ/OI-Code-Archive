#include<bits/stdc++.h>

using namespace std;

inline int F(int n,vector<int> p){
	vector<int> fi(n,0),gi(n,0),impi(n,0),di;
	for(int i=0;i<n;i++){
		fi[i]=upper_bound(di.begin(),di.end(),p[i],less<int>())-di.begin();
		if(fi[i]>=di.size()) di.push_back(p[i]);
		else di[fi[i]]=p[i];
	}
	di.clear();
	for(int i=n-1;~i;i--){
		gi[i]=upper_bound(di.begin(),di.end(),p[i],greater<int>())-di.begin();
		if(gi[i]>=di.size()) di.push_back(p[i]);
		else di[gi[i]]=p[i];
	}
	int lis=di.size();
	for(int i=0;i<n;i++) if(fi[i]+gi[i]+1==lis) impi[i]=1;

	vector<int> fd(n,0),gd(n,0),impd(n,0),dd;
	for(int i=0;i<n;i++){
		fd[i]=upper_bound(dd.begin(),dd.end(),p[i],greater<int>())-dd.begin();
		if(fd[i]>=dd.size()) dd.push_back(p[i]);
		else dd[fd[i]]=p[i];
	}
	dd.clear();
	for(int i=n-1;~i;i--){
		gd[i]=upper_bound(dd.begin(),dd.end(),p[i],less<int>())-dd.begin();
		if(gd[i]>=dd.size()) dd.push_back(p[i]);
		else dd[gd[i]]=p[i];
	}
	int lds=dd.size();
	for(int i=0;i<n;i++) if(fd[i]+gd[i]+1==lds) impd[i]=1;

	int cnt=0;
	for(int i=0;i<n;i++) cnt+=(impi[i]&impd[i]);
	// for(int i=0;i<n;i++) cout<<fi[i]<<' '<<gi[i]<<" / "<<fd[i]<<' '<<gd[i]<<" / "<<lis<<' '<<lds<<endl;

	return cnt;
}

signed main(){
	// int n;
	// cin>>n;
	// vector<int> p(n);
	// iota(p.begin(),p.end(),1);
	// do{
	// 	int cnt=F(n,p);
	// 	for(int i=0;i<n;i++) cout<<p[i]<<' ';cout<<": "<<cnt<<endl;
	// }while(next_permutation(p.begin(),p.end()));
	// cout<<F(13,{3,4,8,7,2,1,5,6,9,10,11,12,13})<<endl;

	int T;
	cin>>T;
	while(T--){
		int n,k;
		cin>>n>>k;
		vector<int> ans;
		if(k==n){
			for(int i=1;i<=n;i++) ans.push_back(i);
		}else if(k>1){
			for(int i=1;i<=n-k;i++) ans.push_back(i);
			for(int i=n;i>n-k;i--) ans.push_back(i);
		}else if(k==1){
			if(n<=4) ;
			else{
				ans.push_back(2);
				for(int i=n-(~n&1);i>=1;i-=2) ans.push_back(i);
				for(int i=4;i<=n;i+=2) ans.push_back(i);
			}
		}else if(k==0){
			if(n<=7) ;
			else{
				ans={3,4,8,7,2,1,5,6};
				for(int i=9;i<=n;i++) ans.push_back(i);
			}
		}
		if(!ans.size()) cout<<-1<<endl;
		else{
			for(int i:ans) cout<<i<<' ';cout<<endl;
			// cout<<" -> "<<F(n,ans)<<endl;
		}
	}

	return 0;
}

/* 
2 5 3 1 4
1 3 6 4 2 5
1 2 4 7 5 3 6
*/