#include<bits/stdc++.h>
using namespace std;
int n,m,q;unsigned int x,y,ans=0;
int c[1000010];int l[1000010];int r[1000010];int pos[1000010];
void Generate_ci(unsigned int &a,unsigned int &b,int &ci){
	a+=(a<<13)-7;
	b+=(b<<11)+2;
	a+=(b>>2)-3;
	b+=(a>>4)+5;
	ci=(a+b)%m+1;
	return;
}
void Generate_query(unsigned int &a,unsigned int &b,int &L,int &R,int &P){
	a+=(a<<13)-7;
	b+=(b<<11)+2;
	L=a%n+1;R=b%n+1;
	a+=(b>>2)-3;
	b+=(a>>4)+5;
	if(L>R)swap(L,R);
	if(L>1000){P=(a+b)%((L>>6)+1)+1;}
	else{P=(a+b)%L+1;}
	return;
}
void Generate_ans(unsigned int &a,unsigned int &b,unsigned int &ans,int tempans){
	a+=(a<<13)-7;
	b+=(b<<11)+2;
	a+=(b>>2)-3;
	b+=(a>>4)+5;
	unsigned int temp=a+b;
	ans=(tempans==1)?(ans+temp):(ans-temp);
	return;
}
int query(int L,int R,int P){
	//do something
	return 0;
}

int main(){
	cin>>n>>m>>q>>x>>y;
	for(int i=1;i<=n;i++)Generate_ci(x,y,c[i]);
	for(int i=1;i<=q;i++){
		Generate_query(x,y,l[i],r[i],pos[i]);
		Generate_ans(x,y,ans,query(l[i],r[i],pos[i]));
	}
	cout<<ans<<endl;
	return 0;
}
