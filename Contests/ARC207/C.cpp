#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;
const int T=3e1+9;

int a[N],pos[N][T],val[N][T],f[N][T],cnt[N],p[T],v[T],n;

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	for(int i=1;i<=n;i++){
		vector<int> o;
		for(int j=0;j<30;j++){
			if(a[i]>>j&1) v[j]=a[i],p[j]=i;
			else v[j]|=a[i];
			if(p[j]) o.push_back(j);
		}
		sort(o.begin(),o.end(),[](int x,int y){return p[x]>p[y];});
		pos[i][0]=i,val[i][0]=a[i];
		for(int j:o){
			if((a[i]|v[j])>(val[i][cnt[i]])){
				cnt[i]++;
				val[i][cnt[i]]=a[i]|v[j];
				pos[i][cnt[i]]=p[j];
			}
		}
	}

	memset(f,-0x3f,sizeof f);
	f[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=cnt[i];j++){
			for(int k=0;k<=cnt[pos[i][j]-1];k++){
				if(val[i][j]>=val[pos[i][j]-1][k]){
					f[i][j]=max(f[i][j],f[pos[i][j]-1][k]+1);
				}
			}
			for(int k=0;k<=cnt[i-1];k++){
				if(val[i][j]>=val[i][k]) f[i][j]=max(f[i][j],f[i-1][k]);
			}
		}
		for(int j=1;j<=cnt[i];j++) f[i][j]=max(f[i][j],f[i][j-1]);
	}

	int ans=0;
	for(int i=0;i<=cnt[n];i++) ans=max(ans,f[n][i]);

	cout<<ans<<endl;

	return 0;
}