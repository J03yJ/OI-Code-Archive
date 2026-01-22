#include<bits/stdc++.h>
using namespace std;

#define int long long

struct Vec{
	int x,y;
	Vec(){}
	Vec(int X,int Y){
		x=X;y=Y;
	}
	Vec operator -(Vec v){
		return Vec(x-v.x,y-v.y);
	}
	Vec operator +(Vec v){
		return Vec(x+v.x,y+v.y);
	}
	bool operator <(const Vec v)const{
		if(x*y!=v.x*v.y) return x*y<v.x*v.y;
		else return x<v.x;
	}
};
int Cross(Vec u,Vec v){
	return u.x*v.y-u.y*v.x;
}
#define IsClock(u,v) (Cross(u,v)<0)

const int N=5e4+9;
int fa[N],n,m;
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y){
	fa[find(y)]=find(x);
}

struct edge{
	Vec c;
	int u,v;
	int w;
	bool operator <(edge e){
		return w<e.w;
	}
}e[N];
Vec ans=Vec(1e9,1e9);
Vec Kruskal(){
	for(int i=1;i<=n;i++) fa[i]=i;
	sort(e+1,e+m+1);
	Vec res=Vec(0,0);
	for(int i=1,cnt=0;i<=m&&cnt<n-1;i++){
		if(find(e[i].u)==find(e[i].v)) continue ;
		merge(e[i].u,e[i].v);
		res=res+e[i].c;
		cnt++;
	}
	ans=min(ans,res);
	return res;
}
void solve(Vec a,Vec b){
	for(int i=1;i<=m;i++) e[i].w=(a.y-b.y)*e[i].c.x+(b.x-a.x)*e[i].c.y;
	Vec c=Kruskal();
	if(Cross(b-a,c-a)<0) solve(a,c),solve(c,b);
}


signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>e[i].u>>e[i].v>>e[i].c.x>>e[i].c.y,e[i].u++,e[i].v++;
	for(int i=1;i<=m;i++) e[i].w=e[i].c.x;Vec a=Kruskal();ans=min(ans,a);
	for(int i=1;i<=m;i++) e[i].w=e[i].c.y;Vec b=Kruskal();ans=min(ans,b);
	solve(a,b);
	cout<<ans.x<<' '<<ans.y<<endl;
	return 0;
}
