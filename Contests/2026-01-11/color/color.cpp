#include<bits/stdc++.h>

using namespace std;

ifstream fin("color.in");
ofstream fout("color.out");
#define cin fin
#define cout fout
#define endl '\n'

const int lgN=2e1+9;
const int N=1e6+9;

unsigned int x,y,ans=0;
int c[N],l[N],r[N],pos[N],n,m,q;
inline void GenC(unsigned int &a,unsigned int &b,int &ci){
	a+=(a<<13)-7;
	b+=(b<<11)+2;
	a+=(b>>2)-3;
	b+=(a>>4)+5;
	ci=(a+b)%m+1;
	return;
}
inline void GenQ(unsigned int &a,unsigned int &b,int &L,int &R,int &P){
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
inline void GenAns(unsigned int &a,unsigned int &b,unsigned int &ans,int tempans){
	a+=(a<<13)-7;
	b+=(b<<11)+2;
	a+=(b>>2)-3;
	b+=(a>>4)+5;
	unsigned int temp=a+b;
	ans=(tempans==1)?(ans+temp):(ans-temp);
	return;
}

int mn[lgN][N],t[N];
inline void Init(){
	for(int i=1;i<=n;i++) if(!t[c[i]]) t[c[i]]=i;
	for(int i=1;i<=n;i++) mn[0][i]=t[c[i]];
	for(int k=1;k<=__lg(n);k++){
		for(int i=1;i+(1<<k)-1<=n;i++){
			mn[k][i]=min(mn[k-1][i],mn[k-1][i+(1<<k-1)]);
		}
	}
}
inline int Min(int l,int r){
	int k=__lg(r-l+1);
	return min(mn[k][l],mn[k][r-(1<<k)+1]);
}
inline int Query(int L,int R,int P){return Min(L,R)>P;}

int main(){
	cin>>n>>m>>q>>x>>y;
	for(int i=1;i<=n;i++) GenC(x,y,c[i]);

	Init();
	for(int i=1;i<=q;i++){
		int l,r,pos;
		cin>>l>>r>>pos;
		GenQ(x,y,l,r,pos);
		GenAns(x,y,ans,Query(l,r,pos));
	}

	cout<<ans<<endl;
	
	return 0;
}
