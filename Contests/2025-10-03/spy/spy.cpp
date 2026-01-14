#include<bits/stdc++.h>

using namespace std;

ifstream fin("spy.in");
ofstream fout("spy.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e5+9;
const int K=1e1+9;
const double eps=1e-8;

struct Vec{
	ll x,y;
	Vec(){}
	Vec(ll _x,ll _y){x=_x,y=_y;}
	inline friend Vec operator +(Vec u,Vec v){return Vec(u.x+v.x,u.y+v.y);}
	inline friend Vec operator -(Vec u,Vec v){return Vec(u.x-v.x,u.y-v.y);}
	inline friend Vec operator *(ll k,Vec u){return Vec(u.x*k,u.y*k);}
	inline double Slope(){return double(x)/double(y+eps);}
}v[K],p[N],s[N];

ll ans[N];
int w[N],t[N],n,q,k;
inline double GetB(Vec p,double k){return p.y-p.x*k;}

vector<int> id[K];
vector<tuple<ll,double,int,int,int>> op[K];
inline void Solve(int x,int l,int r){
	if(l==r) return ;
	
	int mid=l+r>>1;
	Solve(x,l,mid),Solve(x,mid+1,r);

	ll sum=0;
	int i=l,j=mid+1;
	vector<int> ord;
	while(j<=r){
		while(i<=mid&&get<1>(op[x][id[x][i]])<=get<1>(op[x][id[x][j]])){
			if(!get<2>(op[x][id[x][i]])) sum+=get<4>(op[x][id[x][i]]);
			ord.push_back(id[x][i++]);
		}
		if(get<2>(op[x][id[x][j]])){
			cout<<l<<' '<<r<<" : "<<id[x][j]<<' '<<get<3>(op[x][id[x][j]])<<' '<<get<4>(op[x][id[x][j]])*sum<<endl;
			ans[get<3>(op[x][id[x][j]])]+=get<4>(op[x][id[x][j]])*sum;
		}
		ord.push_back(id[x][j++]);
	}
	while(i<=mid) ord.push_back(id[x][i++]);

	for(int i=l;i<=r;i++) id[x][i]=ord[i-l];
	cout<<l<<' '<<r<<" -> ";
	for(int x:ord) cout<<x<<' ';cout<<endl;
}

signed main(){
	cin>>k>>n>>q;
	for(int i=1;i<=k;i++) cin>>v[i].x>>v[i].y;
	for(int i=1;i<=n;i++) cin>>p[i].x>>p[i].y>>w[i];
	for(int i=1;i<=q;i++) cin>>s[i].x>>s[i].y>>t[i];

	for(int i=1;i<=k;i++) if(v[i].x<0) v[i]=-1*v[i];
	sort(v+1,v+k+1,[](Vec u,Vec v){return u.Slope()<v.Slope();});
	for(int i=1;i<=q;i++){
		Vec u=s[i];
		for(int j=1;j<=k;j++) u=u-t[i]*v[j];
		Vec lst=u;
		cout<<i<<" : "<<u.x<<' '<<u.y<<endl;
		for(int j=k;j>=1;j--){
			Vec now=lst+2*t[i]*v[j];
			cout<<" U = "<<now.x<<' '<<now.y<<endl;
			op[j].push_back({now.x,GetB(now,v[j].Slope()),1,i,1});
			op[j].push_back({lst.x-1,GetB(now,v[j].Slope()),1,i,-1});
			lst=now;
		}
		lst=u;
		for(int j=1;j<=k;j++){
			Vec now=lst+2*t[i]*v[j];
			cout<<" D = "<<now.x<<' '<<now.y<<endl;
			op[j].push_back({now.x,GetB(now,v[j].Slope()),1,i,-1});
			op[j].push_back({lst.x-1,GetB(now,v[j].Slope()),1,i,1});
			lst=now;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=k;j++){
			op[j].push_back({p[i].x,GetB(p[i],v[j].Slope()),0,i,w[i]});
		}
	}
	for(int i=1;i<=k;i++){
		id[i]=vector<int>(op[i].size());
		iota(id[i].begin(),id[i].end(),0);
		sort(id[i].begin(),id[i].end(),[&i](int p,int q){
			return op[i][p]<op[i][q];
		});
		for(int j=0;j<id[i].size();j++){
			cout<<i<<" / "<<j<<' '<<id[i][j]<<" = ";
			cout<<get<0>(op[i][id[i][j]])<<' ';
			cout<<get<1>(op[i][id[i][j]])<<' ';
			cout<<get<2>(op[i][id[i][j]])<<' ';
			cout<<get<3>(op[i][id[i][j]])<<' ';
			cout<<get<4>(op[i][id[i][j]])<<' ';
			cout<<endl;
		}
		Solve(i,0,op[i].size()-1);
	}

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;
	
	return 0;
}