#include<bits/stdc++.h>
using namespace std;
const int maxn=320;
const int maxL=2000020;
const int Score[11]={100,33,25,16,12,8,7,5,2,1,0};
std::mt19937 rnd(time(0));
void Assert(bool S,int k){
	if(!S){
		printf("ERROR ON @%d\n",k);
		exit(0);
	}
}
int str[maxL];
int N,M,T[maxn],V[maxn][maxn];
int main(int argc,char *argv[]){
	freopen("A.out","r",stdin);
	scanf("%d%d",&N,&M);
	Assert(1<=N&&N<=300&&2<=M&&M<=128,1);
	for(int i=1;i<=N;i++){
		scanf("%d",T+i);
		Assert(0<=T[i]&&T[i]<=1,2);
		if(T[i]){
			scanf("%d%d",V[i],V[i]+1);
			Assert(0<=V[i][0]&&V[i][0]<M&&-1<=V[i][1]&&V[i][1]<=N,3);
		}
		else{
			for(int j=0;j<=M;j++){
				scanf("%d",V[i]+j);
				Assert(-1<=V[i][j]&&V[i][j]<=N,4);
			}
		}
	}
	int len=atoi(argv[1]),l,r,tim,now,cnt=0;
	Assert(0<=len&&len<=1000000,5);
	for(int i=1;i<=100;i++){
		for(int j=1;j<=len;j++)
			str[j]=(rnd()>>17)&1;
		tim=0;now=1;l=1;r=len;
		while(now>0&&tim<=1000000){
			tim++;
			if(T[now]){
				str[++r]=V[now][0];
				now=V[now][1];
			}
			else{
				if(l>r)now=V[now][M];
				else now=V[now][str[l++]];
			}
		}
		if(tim<=1000000){
			r=0;l=0;
			for(int j=1;j<=len;j++)
				if(str[j]){
					if(r==0){l=-1;break;}
					r--;
				}
				else r++;
			if(r)l=-1;
			cnt+=(l==now);
		}
	}
	printf("Passed: %d\n",cnt);
	printf("Score: ");
	for(int i=10;i>=0;i--)
		if(cnt+Score[i]>=100){
			printf("%d\n",i);
			return 0;
		}
}