#include<cstdio>
#include<cctype>
#include<vector>
#include<cstring>
#include<algorithm>
#define siz 708
#define N 500001
class istream{
	char buf[20000003],*s;
	public:
		inline istream(){
#ifndef ONLINE_JUDGE
			freopen("input.txt","r",stdin);
#endif
			fread(s=buf,1,20000003,stdin);
			fclose(stdin);
		}
		inline istream&operator>>(int&rhs){
			int f=rhs=0;
			for(;!isdigit(*s);++s)f=*s=='-';
			for(;isdigit(*s);)
			rhs=(rhs<<3)+(rhs<<1)+(*s++^'0');
			if(f)rhs=-rhs;
			return*this;
		}
}cin;
class ostream{
	char buf[5000005],*s;
	public:
		inline ostream(){s=buf;}
		inline ostream&operator<<(int rhs){
			if(rhs<0)*s++='-',rhs=-rhs;
			if(rhs==0){
				*s++='0';
				return*this;
			}
			static int w;
			for(w=1;w<=rhs;w*=10);
			for(w/=10;w;w/=10)*s++=(rhs/w)^'0',rhs%=w;
			return*this;
		}
		inline ostream&operator<<(const char&rhs){*s++=rhs;return*this;}
		inline~ostream(){
			fwrite(buf,1,s-buf,stdout);
		}
}cout;
int n,m,L[710],R[710],bel[N],blocks,mx[710][710],ans,tot[N],wz[N],a[N];
void init(){
	blocks=(n-1)/siz+1;
	for(int i=1;i<=blocks;++i)L[i]=R[i-1]+1,R[i]=i*siz;
	R[blocks]=n;
	for(int i=1;i<=blocks;++i){
		memset(tot,0,sizeof tot);
		for(int j=L[i];j<=R[i];++j)bel[j]=i;
		// for(int j=i;j<=blocks;++j){
		// 	int&F=mx[i][j];
		// 	F=mx[i][j-1];
		// 	for(int k=L[j];k<=R[j];++k)
		// 	F=std::max(F,++tot[a[k]]);
		// }
	}
    for(int i=1;i<=bel[n];i++){
        memset(tot,0,sizeof(tot));
        for(int j=i;j<=bel[n];j++){
            mx[i][j]=mx[i][j-1];
            for(int k=L[j];k<=R[j];k++) mx[i][j]=std::max(mx[i][j],++tot[a[k]]);
        }
    }
}
std::vector<int>ls,v[N];
int main(){
	ls.push_back(-1);
	cin>>n>>m;
	for(int i=1;i<=n;ls.push_back(a[i++]))cin>>a[i];
	std::sort(ls.begin(),ls.end());
	ls.erase(std::unique(ls.begin(),ls.end()),ls.end());
	for(int i=1;i<=n;++i)v[a[i]=std::lower_bound(ls.begin(),ls.end(),a[i])-ls.begin()].push_back(i),wz[i]=v[a[i]].size()-1;
	init();
	memset(tot,0,sizeof tot);
	while(m--){
		int l,r;cin>>l>>r;
		l^=ans,r^=ans;
		ans=0;
		if(bel[l]==bel[r]){
			for(int i=l;i<=r;i++){
                ans=std::max(ans,++tot[a[i]]);
            }
            for(int i=l;i<=r;i++) tot[a[i]]=0;
		}else{
			// ans=mx[bel[l]+1][bel[r]-1];
			// for(int i=l;i<=R[bel[l]];++i){
			// 	int it=wz[i];
			// 	while(it+ans<v[a[i]].size()&&v[a[i]][it+ans]<=r)++ans;
			// }
			// for(int i=L[bel[r]];i<=r;++i){
			// 	int it=wz[i];
			// 	while(it-ans>=0&&v[a[i]][it-ans]>=l)++ans;
			// }
            ans=mx[bel[l]+1][bel[r]-1];
            for(int i=l;i<=R[bel[l]];i++){
                while(wz[i]+ans<v[a[i]].size()&&v[a[i]][wz[i]+ans]<=r) ans++;
            }
            for(int i=L[bel[r]];i<=r;i++){
                while(wz[i]-ans>=0&&v[a[i]][wz[i]-ans]>=l) ans--;
            }
		}
		// cout<<ans<<'\n';
	}
	return 0;
}