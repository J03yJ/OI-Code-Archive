#include<bits/stdc++.h>
#include"haru.h"
using namespace std;
vector<int> haru(int n){
	vector<int> U,V,ans(n);
	for(int i=0;i<n-1;i++) U.push_back(i),V.push_back(i+1);
	int x=!guess(U,V,n);
	for(int i=0;i<n;i++) ans[i]=x+i;
	return ans;
}