#include<bits/stdc++.h>

using namespace std;

using ll=long long;
using ld=long double;
const ld eps=1e-12;

struct Vec{
	ll x,y;
	Vec(){};
	Vec(ll _x,ll _y){x=_x,y=_y;}
	inline friend Vec operator +(Vec p,Vec q){return Vec(p.x+q.x,p.y+q.y);}
	inline friend Vec operator -(Vec p,Vec q){return Vec(p.x-q.x,p.y-q.y);}
};
inline ll Cross(Vec p,Vec q){return p.x*q.y-p.y*q.x;}
inline ll Dot(Vec p,Vec q){return p.x*q.x+p.y*q.y;}
inline ld Len(Vec p){return sqrt(p.x*p.x+p.y*p.y);}
inline ld Angle(Vec p,Vec q){return acos(ld(Dot(p,q))/Len(p)/Len(q)-eps);}
inline ld DistPP(Vec p,Vec q){return Len(p-q);}
inline ld DistPL(Vec o,Vec p1,Vec p2){
	if(DistPP(p1,p2)<eps) return DistPP(o,p1);
	ld a=DistPP(o,p1),b=DistPP(o,p2),c=DistPP(p1,p2);
	ld x=(a*a-b*b+c*c)/(2*c);
	return sqrt(a*a-x*x);
}

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n;ll r;Vec o;
		cin>>n>>o.x>>o.y>>r;
		vector<Vec> p(n);
		for(auto &v:p) cin>>v.x>>v.y;

		cout<<fixed<<setprecision(16);

		ll ans=0,res=0;
		for(int i=0;i<n;i++) p.push_back(p[i]);
		for(int i=0,j=1;i<n;res-=Cross(p[i+1]-p[i],p[j-1]-p[i]),i++){
			while(j<i+n&&Cross(p[j]-p[i],o-p[i])>=0&&DistPL(o,p[i],p[j])>=r-eps){
				res+=Cross(p[j-1]-p[i],p[j]-p[i]);
				j++;
			}
			// cout<<i<<' '<<j<<" : "<<DistPL(o,p[i],p[j])<<endl;
			// cout<<" -> "<<p[i].x<<' '<<p[i].y<<endl;
			// cout<<" -> "<<(o-p[i]).x<<' '<<(o-p[i]).y<<endl;
			// cout<<" -> "<<(p[j]-p[i]).x<<' '<<(p[j]-p[i]).y<<endl;
			// cout<<" -> "<<Cross(p[j]-p[i],o-p[i])<<endl;
			ans=max(ans,res);
		}

		cout<<ans<<endl;
	}

	return 0;
}