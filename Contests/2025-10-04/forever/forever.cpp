#include<bits/stdc++.h>

using namespace std;

ifstream fin("forever.in");
ofstream fout("forever.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e6+9;

int vis[N],a[N<<1],n;

inline array<int,2> Merge(array<int,2> x,array<int,2> y){
	if(x[0]!=y[0]) return max(x,y);
	else return {x[0],x[1]+y[1]};
}

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i],a[i+n]=a[i];
		
		ll ans=0;

		vector<int> stk;
		stk.reserve(n<<1);
		for(int i=1;i<=2*n;i++){
			int lst=0;
			array<int,2> tmp={0,0};
			while(stk.size()&&a[stk.back()]<a[i]){
				lst=stk.back();
				tmp=Merge(tmp,{a[stk.back()],1});
				stk.pop_back();
				if(stk.size()&&tmp[0]<a[stk.back()]){
					lst=(lst-1)%n+1;
					if(!vis[lst]){
						vis[lst]=1;
						ans+=1ll*tmp[1]*(tmp[1]-1)/2;
						if(stk.back()%n==i%n) ans+=tmp[1];
						else ans+=2*tmp[1];
					}
				}
			}
			stk.push_back(i);
		}
		stk.clear();

		array<int,2> tmp={0,0};
		for(int i=1;i<=n;i++) tmp=Merge(tmp,{a[i],1});
		ans+=1ll*tmp[1]*(tmp[1]-1)/2;

		cout<<ans<<endl;

		for(int i=1;i<=n;i++) vis[i]=0;
	}

	return 0;
}