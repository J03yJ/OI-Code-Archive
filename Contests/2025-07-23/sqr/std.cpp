#include<bits/stdc++.h>
#define N 180005
using namespace std;
int V[N],v[N],a,s=99,n,q,i,j,k,o,l,r,L[N],R[N],t,M[N];
long double S;vector<double>g[2333];
double x,f[N][44],h[N][44];
void G(int&x)
{
	char c=getchar();
	while(c<48||c>57)c=getchar();
	for(x=0;c>47&&c<58;c=getchar())x=x*10+c-48;
}
void D()
{
	if(76-v[j]>M[i])g[i].push_back(g[i][M[i]]),M[i]++;
	for(k=40,a=75-v[j];k;a--,k--)g[i][a]+=h[j][k];v[j]--;
}
main()
{
	freopen("std.in","r",stdin);freopen("std.out","w",stdout);
	for(cin>>n>>q,t=(n+s-1)/s,i=0;i<t;i++)g[i].resize(41),V[i]=35,M[i]=40,L[i]=i*s+1,R[i]=min(i*s+s,n);
	for(i=1;i<=n;i++)
	{
		for(G(a),x=a,v[i]=j=35;~j;j--)g[(i-1)/s][j]+=f[i][j]=x,x=sqrt(x);
		for(j=36,x=a;j<=40;j++)x=min(x*x,1e8),g[(i-1)/s][j]+=f[i][j]=x;
		for(j=40;j;j--)h[i][j]=f[i][j-1]-f[i][j];
	}
	int c=0;
	while(q--)if(G(o),G(l),G(r),o>2)
	{
		for(S=i=0;i<t;i++)if(l<=L[i]&&R[i]<=r)S+=g[i][max(0,min(M[i],V[i]))];
		else for(j=max(L[i],l);j<=min(R[i],r);j++)S+=f[j][max(0,min(40,v[j]+V[i]-35))];
		cout<<"# "<<(++c)<<endl;
		printf("%lld\n",(long long)(S+.5));
		printf("%.8Lf\n",S);
	}
	else if(o<2)
	{
		for(i=0;i<t;i++)if(l<=L[i]&&R[i]<=r)V[i]++;else
		if(l<=R[i]&&r>=L[i])for(V[i]++,j=L[i];j<=R[i];j++)if(j<l||j>r)D();
	}
	else for(i=0;i<t;i++)if(l<=L[i]&&R[i]<=r)V[i]--;else for(j=max(L[i],l);j<=min(R[i],r);j++)D();
}
