#include<bits/stdc++.h>

using namespace std;

const int N=5e2+9;
const int M=N*N*4+9;
const int V=5e2;
const int inf=1e9;

int n,m,s,t;

int fi[M],to[M<<2],ne[M<<2],w[M<<2],adj=1;
void AdEg(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}
inline int Id(int i,int val,int op){
    return op*n*(V+1)+(i-1)*(V+1)+val;
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

int main(){
    cin>>n>>m;

    s=Id(n,V+1,1)+m+1,t=s+1;
    for(int i=1;i<=n;i++){
        AdEg(s,Id(i,1,0),inf);
        AdEg(Id(i,1,0),s,0);
        for(int j=1;j<=V;j++){
            AdEg(Id(i,j,0),Id(i,j+1,0),j);
            AdEg(Id(i,j+1,0),Id(i,j,0),0);
        }
        AdEg(Id(i,V+1,0),t,inf);
        AdEg(t,Id(i,V+1,0),0);
    }
    for(int i=1;i<=n;i++){
        AdEg(s,Id(i,V+1,1),inf);
        AdEg(Id(V+1,i,1),s,0);
        for(int j=V;j>=1;j--){
            AdEg(Id(i,j+1,1),Id(i,j,1),j);
            AdEg(Id(i,j,1),Id(i,j+1,1),0);
        }
        AdEg(Id(i,1,1),t,inf);
        AdEg(t,Id(i,1,1),0);
    }

    for(int i=1,x;i<=n;i++){
        cin>>x;
        AdEg(s,Id(i,x,0),inf);
        AdEg(Id(i,x,0),s,0);
    }
    for(int i=1,y;i<=n;i++){
        cin>>y;
        AdEg(Id(i,y,1),t,inf);
        AdEg(t,Id(i,y,1),0);
    }
    for(int i=1;i<=m;i++){
        int u=Id(n,V+1,1)+i;
        for(int j=1,a;j<=n;j++){
            cin>>a;
            AdEg(Id(j,a,1),u,inf);
            AdEg(u,Id(j,a,1),0);
            AdEg(u,Id(j,a,0),inf);
            AdEg(Id(j,a,0),u,0);
        }
    }

    int sum=0;
    while(BFS(s,t)) sum+=DFS(s,inf,t);
    cout<<sum<<endl;

    return 0;
}