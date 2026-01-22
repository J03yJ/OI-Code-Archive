#include<bits/stdc++.h>

using namespace std;

ifstream fin("dameow.in");
ofstream fout("dameow.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e3+9;

int a[N][N],b1[N][N],b2[N][N],b3[N][N],n,m;
int U[N][N],D[N][N],L[N][N],R[N][N],cnt[N],s[N][N],t[N][N];
inline void Conquer(int a[N][N],int l1,int r1,int l2,int r2,ll &ans){
	if(l1==r1&&l2==r2) return ans+=a[l1][l2],void();
	for(int i=l1;i<=r1;i++){
		for(int j=l2;j<=r2;j++){
			if(a[i][j]){
				U[i][j]=(i-1>=l1?U[i-1][j]:0)+1;
				L[i][j]=(j-1>=l2?L[i][j-1]:0)+1;
			}else U[i][j]=L[i][j]=0;
		}
	}
	for(int i=r1;i>=l1;i--){
		for(int j=r2;j>=l2;j--){
			if(a[i][j]){
				D[i][j]=(i+1<=r1?D[i+1][j]:0)+1;
				R[i][j]=(j+1<=r2?R[i][j+1]:0)+1;
			}else D[i][j]=R[i][j]=0;
		}
	}
	if(r1-l1>r2-l2){
		int mid=l1+r1>>1;
		for(int i=l2;i<=r2;i++){
			s[i][i]=U[mid][i];
			for(int j=mid-U[mid][i]+1;j<=mid;j++) cnt[L[j][i]]++;
			for(int j=i-l2+1;j>=0;j--) cnt[j]+=cnt[j+1];
			for(int j=l2;j<i;j++) if(U[mid][j]>U[mid][i]) s[j][i]+=cnt[i-j+1];
			memset(cnt,0,(r2-l2+2)*sizeof int());
			for(int j=mid-U[mid][i]+1;j<=mid;j++) cnt[R[j][i]]++;
			for(int j=r2-i+1;j>=0;j--) cnt[j]+=cnt[j+1];
			for(int j=r2;j>i;j--) if(U[mid][j]>=U[mid][i]) s[i][j]+=cnt[j-i+1];
			memset(cnt,0,(r2-l2+2)*sizeof int());
		}
		for(int i=l2;i<=r2;i++){
			t[i][i]=D[mid+1][i];
			for(int j=mid+1;j<=mid+D[mid+1][i];j++) cnt[L[j][i]]++;
			for(int j=i-l2+1;j>=0;j--) cnt[j]+=cnt[j+1];
			for(int j=l2;j<i;j++) if(D[mid+1][j]>D[mid+1][i]) t[j][i]+=cnt[i-j+1];
			memset(cnt,0,(r2-l2+2)*sizeof int());
			for(int j=mid+1;j<=mid+D[mid+1][i];j++) cnt[R[j][i]]++;
			for(int j=r2-i+1;j>=0;j--) cnt[j]+=cnt[j+1];
			for(int j=r2;j>i;j--) if(D[mid+1][j]>=D[mid+1][i]) t[i][j]+=cnt[j-i+1];
			memset(cnt,0,(r2-l2+2)*sizeof int());
		}
		for(int i=l2;i<=r2;i++){
			for(int j=i;j<=r2;j++){
				ans+=s[i][j]*t[i][j];
				s[i][j]=t[i][j]=0;
			}
		}
		Conquer(a,l1,mid,l2,r2,ans);
		Conquer(a,mid+1,r1,l2,r2,ans);
	}else{
		int mid=l2+r2>>1;
		for(int i=l1;i<=r1;i++){
			s[i][i]=L[i][mid];
			for(int j=mid-L[i][mid]+1;j<=mid;j++) cnt[U[i][j]]++;
			for(int j=i-l1+1;j>=0;j--) cnt[j]+=cnt[j+1];
			for(int j=l1;j<i;j++) if(L[j][mid]>L[i][mid]) s[j][i]+=cnt[i-j+1];
			memset(cnt,0,(r1-l1+2)*sizeof int());
			for(int j=mid-L[i][mid]+1;j<=mid;j++) cnt[D[i][j]]++;
			for(int j=r1-i+1;j>=0;j--) cnt[j]+=cnt[j+1];
			for(int j=r1;j>i;j--) if(L[j][mid]>=L[i][mid]) s[i][j]+=cnt[j-i+1];
			memset(cnt,0,(r1-l1+2)*sizeof int());
		}
		for(int i=l1;i<=r1;i++){
			t[i][i]=R[i][mid+1];
			for(int j=mid+1;j<=mid+R[i][mid+1];j++) cnt[U[i][j]]++;
			for(int j=i-l1+1;j>=0;j--) cnt[j]+=cnt[j+1];
			for(int j=l1;j<i;j++) if(R[j][mid+1]>R[i][mid+1]) t[j][i]+=cnt[i-j+1];
			memset(cnt,0,(r1-l1+2)*sizeof int());
			for(int j=mid+1;j<=mid+R[i][mid+1];j++) cnt[D[i][j]]++;
			for(int j=r1-i+1;j>=0;j--) cnt[j]+=cnt[j+1];
			for(int j=r1;j>i;j--) if(R[j][mid+1]>=R[i][mid+1]) t[i][j]+=cnt[j-i+1];
			memset(cnt,0,(r1-l1+2)*sizeof int());
		}
		for(int i=l1;i<=r1;i++){
			for(int j=i;j<=r1;j++){
				ans+=s[i][j]*t[i][j];
				s[i][j]=t[i][j]=0;
			}
		}
		Conquer(a,l1,r1,l2,mid,ans);
		Conquer(a,l1,r1,mid+1,r2,ans);
	}
}

signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cin>>a[i][j];
	}

	int mx=INT_MIN,mn=INT_MAX;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			mx=max(mx,a[i][j]);
			mn=min(mn,a[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			b1[i][j]=(a[i][j]!=mx);
			b2[i][j]=(a[i][j]!=mn);
			b3[i][j]=(a[i][j]!=mx&&a[i][j]!=mn);
		}
	}

	ll ans=0,s1=0,s2=0,s3=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) ans+=1ll*i*j;
	}
	Conquer(b1,1,n,1,m,s1);
	Conquer(b2,1,n,1,m,s2);
	Conquer(b3,1,n,1,m,s3);
	ans-=s1;
	ans-=s2;
	ans+=s3;


	cout<<mx-mn<<' '<<ans<<endl;

	return 0;
}