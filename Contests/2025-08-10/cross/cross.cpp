#include<bits/stdc++.h>

using namespace std;

ifstream fin("cross.in");
ofstream fout("cross.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e6+9;
const double eps=1e-8;

struct Point{
	ll x,y;
	Point(){}
	Point(ll _x,ll _y){x=_x,y=_y;}
	inline Point operator +(Point p){return Point(x+p.x,y+p.y);}
	inline Point operator -(Point p){return Point(x-p.x,y-p.y);}
	inline Point operator -(){return Point(-x,-y);}
};
inline ll Cross(Point p,Point q){return p.x*q.y-p.y*q.x;}
inline vector<Point> Convex(vector<Point> p){
	sort(p.begin(),p.end(),[](Point p,Point q){
		if(p.x!=q.x) return p.x<q.x;
		else return p.y<q.y;
	});
	vector<Point> r;
	for(Point t:p){
		while(r.size()>1){
			Point u=r.end()[-1],v=r.end()[-2];
			if(Cross(v-u,v-t)<0) break ;
			r.pop_back();
		}
		r.push_back(t);
	}
	return r;
}
inline vector<Point> Merge(vector<Point> p,vector<Point> q){
	p.insert(p.end(),q.begin(),q.end());
	return Convex(p);
}
inline vector<Point> MinkSum(vector<Point> p,vector<Point> q){
	vector<Point> dp(p.size()-1),dq(q.size()-1);
	for(int i=0;i<dp.size();i++) dp[i]=p[i+1]-p[i];
	for(int i=0;i<dq.size();i++) dq[i]=q[i+1]-q[i];
	vector<Point> d;
	d.insert(d.end(),dp.begin(),dp.end());
	d.insert(d.end(),dq.begin(),dq.end());
	sort(d.begin(),d.end(),[](Point p,Point q){
		return Cross(p,q)<0;
	});
	vector<Point> r({p.front()+q.front()});
	for(Point t:d) r.push_back(r.back()+t);
	return Convex(r);
}

int n,q;
Point p[N],s[N];
inline vector<Point> Work(int l,int r){
	if(l==r) return {p[l]};
	int mid=l+r>>1;
	vector<Point> lp,rp;
	for(int i=l;i<=mid;i++) lp.push_back(-s[i-1]);
	for(int i=mid+1;i<=r;i++) rp.push_back(s[i]);
	lp=Convex(lp),rp=Convex(rp);
	vector<Point> res=MinkSum(lp,rp);
	return Merge(res,Merge(Work(l,mid),Work(mid+1,r)));
}

signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>p[i].x>>p[i].y;

	for(int i=1;i<=n;i++) s[i]=s[i-1]+p[i];
	vector<Point> pres=Work(1,n);
	vector<double> pslp(pres.size());
	pslp[0]=1e18;
	for(int i=1;i<pres.size();i++){
		Point d=pres[i]-pres[i-1];
		pslp[i]=double(d.y)/d.x;
	}

	for(int i=1;i<=n;i++) p[i]=-p[i],s[i]=-s[i];
	vector<Point> nres=Work(1,n);
	vector<double> nslp(nres.size());
	nslp[0]=1e18;
	for(int i=1;i<nres.size();i++){
		Point d=nres[i]-nres[i-1];
		nslp[i]=double(d.y)/d.x;
	}

	while(q--){
		Point p;
		cin>>p.x>>p.y;
		if(p.x<0){
			double k=double(p.y)/double(p.x+eps);
			int pos=upper_bound(nslp.begin(),nslp.end(),k,greater<double>())-nslp.begin()-1;
			cout<<Cross(p,-nres[pos])<<endl;
		}else{
			double k=double(p.y)/double(p.x+eps);
			int pos=upper_bound(pslp.begin(),pslp.end(),k,greater<double>())-pslp.begin()-1;
			cout<<Cross(p,pres[pos])<<endl;
		}
	}

	return 0;
}