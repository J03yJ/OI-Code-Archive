#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=4e1+9;
const int M=N*N*N*3;
const int inf=1e18;

int v[N][N][N],p,q,r,d;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
int Trs(int i,int j,int k){
    return (k-1)*p*q+(i-1)*q+j;
}

int fi[M],to[M<<4],ne[M<<4],w[M<<4],adj=1;
void AdEg(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}

int lev[M],cur[M];
bool BFS(int s,int t){
    queue<int> q;
	for(int i=1;i<=t;i++) lev[i]=0,cur[i]=fi[i];
    lev[s]=1;
	q.push(s);
	while(q.size()){
		int x=q.front();
		q.pop();
		if(x==t) return 1;
		for(int i=fi[x];i;i=ne[i]){
			int y=to[i];
			if(!w[i]) continue ;
            if(lev[y]) continue ;
			lev[y]=lev[x]+1;
            q.push(y);
		}
	}
	return 0;
}
int DFS(int x,int mn,int t){
	if(x==t) return mn;
	int k=mn;
	for(int &i=cur[x];i;i=ne[i]){
		int y=to[i];
        if(!w[i]) continue ;
		if(lev[x]+1!=lev[y]) continue ;
		int tmp=DFS(y,min(k,w[i]),t);
		k-=tmp;
		w[i]-=tmp;
		w[i^1]+=tmp;
		if(!k) return mn;
	}
	return mn-k;
}

signed main(){
    cin>>p>>q>>r>>d;
    for(int k=1;k<=r;k++){
        for(int i=1;i<=p;i++){
            for(int j=1;j<=q;j++) cin>>v[i][j][k];
        }
    }

    int s=Trs(p,q,r+1)+1,t=s+1;
    for(int i=1;i<=p;i++){
        for(int j=1;j<=q;j++){
            AdEg(s,Trs(i,j,1),inf);
            AdEg(Trs(i,j,1),s,0);
            for(int k=1;k<=r;k++){
                AdEg(Trs(i,j,k),Trs(i,j,k+1),v[i][j][k]);
                AdEg(Trs(i,j,k+1),Trs(i,j,k),0);
            }
            AdEg(Trs(i,j,r+1),t,inf);
            AdEg(t,Trs(i,j,r+1),0);
        }
    }
    for(int i=1;i<=p;i++){
        for(int j=1;j<=q;j++){
            for(int op:{0,1,2,3}){
                int ii=i+dx[op],jj=j+dy[op];
                if(ii<1||jj<1||ii>p||jj>q) continue ;
                for(int k=d+1;k<=r+1;k++){
                    AdEg(Trs(i,j,k),Trs(ii,jj,k-d),inf);
                    AdEg(Trs(ii,jj,k-d),Trs(i,j,k),0);
                }
            }
        }
    }

    int ans=0;
    while(BFS(s,t)) ans+=DFS(s,inf,t);
    cout<<ans<<endl;

    return 0;
}