#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;

using ll=long long;
using uint=unsigned;
const uint mod=(1<<30);

int qry[N],m,tot;
uint ans[N];
vector<array<int,6>> opt;
vector<int> val;

struct Fenw{
	uint tr[N<<2];
	inline void Add(int x,uint k){while(x<=tot) tr[x]+=k,x+=x&-x;}
	inline int Ask(int x){uint ans=0;while(x) ans+=tr[x],x&=x-1;return ans;}
	inline int Ask(int l,int r){return Ask(r)-Ask(l-1);}
}tr[4];

inline int Signed(uint x){
	return x>=mod/2?signed(x-mod):x;
}
inline void Work1(int l,int r){
	if(l==r) return ;
	int mid=l+r>>1;
	Work1(l,mid),Work1(mid+1,r);
	int i=mid+1,j=l;
	vector<array<int,6>> tmp;
	tmp.reserve(r-l+1);
	while(i<=r){
		while(j<=mid&&opt[j][1]+opt[j][2]>=opt[i][1]+opt[i][2]){
			if(opt[j][0]==0){
				uint t=opt[j][1]+opt[j][2]+1;
				tr[0].Add(opt[j][5],opt[j][3]*(t*t+t));
				tr[1].Add(opt[j][5],opt[j][3]*-(2*t+1));
				tr[2].Add(opt[j][5],opt[j][3]);
			}
			tmp.push_back(opt[j]);
			j++;
		}
		if(opt[i][0]==2){
			uint t=opt[i][1]+opt[i][2];
			ans[opt[i][4]]+=opt[i][3]*tr[0].Ask(opt[i][5]);
			ans[opt[i][4]]+=opt[i][3]*tr[1].Ask(opt[i][5])*t;
			ans[opt[i][4]]+=opt[i][3]*tr[2].Ask(opt[i][5])*t*t;
		}
		tmp.push_back(opt[i]);
		i++;
	}
	for(int k=j;k<=mid;k++) tmp.push_back(opt[k]);
	while(--j>=l){
		if(opt[j][0]==0){
			uint t=opt[j][1]+opt[j][2]+1;
			tr[0].Add(opt[j][5],-opt[j][3]*(t*t+t));
			tr[1].Add(opt[j][5],-opt[j][3]*-(2*t+1));
			tr[2].Add(opt[j][5],-opt[j][3]);
		}
	}
	for(int k=l;k<=r;k++) opt[k]=tmp[k-l];
}
inline void Work2(int l,int r){
	if(l==r) return ;
	int mid=l+r>>1;
	Work2(l,mid),Work2(mid+1,r);
	int i=mid+1,j=l;
	vector<array<int,6>> tmp;
	while(i<=r){
		while(j<=mid&&opt[j][2]>=opt[i][2]){
			if(opt[j][0]==0){
				uint t=opt[j][2]+1;
				tr[0].Add(opt[j][5],opt[j][3]*(t*t+t));
				tr[1].Add(opt[j][5],opt[j][3]*-(2*t+1));
				tr[2].Add(opt[j][5],opt[j][3]);
			}
			tmp.push_back(opt[j]);
			j++;
		}
		if(opt[i][0]==2){
			uint t=opt[i][2];
			ans[opt[i][4]]+=opt[i][3]*tr[0].Ask(opt[i][5]+1,tot);
			ans[opt[i][4]]+=opt[i][3]*tr[1].Ask(opt[i][5]+1,tot)*t;
			ans[opt[i][4]]+=opt[i][3]*tr[2].Ask(opt[i][5]+1,tot)*t*t;
		}
		tmp.push_back(opt[i]);
		i++;
	}
	for(int k=j;k<=mid;k++) tmp.push_back(opt[k]);
	while(--j>=l){
		if(opt[j][0]==0){
			uint t=opt[j][2]+1;
			tr[0].Add(opt[j][5],-opt[j][3]*(t*t+t));
			tr[1].Add(opt[j][5],-opt[j][3]*-(2*t+1));
			tr[2].Add(opt[j][5],-opt[j][3]);
		}
	}
	i=mid+1,j=l;
	while(i<=r){
		while(j<=mid&&opt[j][2]>=opt[i][2]){
			if(opt[j][0]==1){
				uint _x=opt[j][1]+1,_y=opt[j][2]+1;
				tr[0].Add(opt[j][5],opt[j][3]*_x*_y);
				tr[1].Add(opt[j][5],-opt[j][3]*_y);
				tr[2].Add(opt[j][5],-opt[j][3]*_x);
				tr[3].Add(opt[j][5],opt[j][3]);
			}
			j++;
		}
		if(opt[i][0]==2){
			uint x=opt[i][1],y=opt[i][2];
			ans[opt[i][4]]+=opt[i][3]*tr[0].Ask(opt[i][5],tot)*1;
			ans[opt[i][4]]+=opt[i][3]*tr[1].Ask(opt[i][5],tot)*x;
			ans[opt[i][4]]+=opt[i][3]*tr[2].Ask(opt[i][5],tot)*y;
			ans[opt[i][4]]+=opt[i][3]*tr[3].Ask(opt[i][5],tot)*x*y;
		}
		i++;
	}
	while(--j>=l){
		if(opt[j][0]==1){
			uint _x=opt[j][1]+1,_y=opt[j][2]+1;
			tr[0].Add(opt[j][5],-opt[j][3]*_x*_y);
			tr[1].Add(opt[j][5],opt[j][3]*_y);
			tr[2].Add(opt[j][5],opt[j][3]*_x);
			tr[3].Add(opt[j][5],-opt[j][3]);
		}
	}
	for(int k=l;k<=r;k++) opt[k]=tmp[k-l];
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);
	
	cin>>m;
	for(int i=1,op;i<=m;i++){
		int x,y,z,w;
		cin>>op>>x>>y>>z>>w;
		if(op==1){
			int _x=x+z-1,_y=y+z-1;
			opt.push_back({0,x,_y,w,i});
			opt.push_back({0,_x+1,y-1,-w,i});
			opt.push_back({1,_x,y-1,-2*w,i});
			opt.push_back({1,x-1,y-1,2*w,i});
		}else if(op==2){
			qry[i]=1;
			opt.push_back({2,x,z,1,i});
			opt.push_back({2,y+1,z,-1,i});
			opt.push_back({2,x,w+1,-1,i});
			opt.push_back({2,y+1,w+1,1,i});
		}
	}

	for(auto t:opt) val.push_back(t[1]);
	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()),val.end());
	val.insert(val.begin(),-1145);
	for(auto &t:opt) t[5]=lower_bound(val.begin(),val.end(),t[1])-val.begin();
	tot=val.size()-1;

	sort(opt.begin(),opt.end(),[](auto oi,auto oj){return oi[4]<oj[4];});
	Work1(0,opt.size()-1);
	sort(opt.begin(),opt.end(),[](auto oi,auto oj){return oi[4]<oj[4];});
	Work2(0,opt.size()-1);

	for(int i=1;i<=m;i++) if(qry[i]) cout<<(ans[i]/2)%mod<<endl;

	return 0;
}