#include <bits/stdc++.h>
#include "pnc.h"
using namespace std;

namespace Grader{
	int tid,n,x,y,m,q1,q2,gt;
	long long V;
	vector<int> u,v,l,r,tk;
	map<long long,int> G;
	void main()
	{
		ios::sync_with_stdio(0);
		cin.tie(0);cout.tie(0);
		cin>>tid>>n>>x>>y>>m>>q1>>q2;

		l.resize(n),r.resize(n),u.resize(n-1),v.resize(n-1);
		for(int i=1;i<=n;i++)
			cin>>l[i-1]>>r[i-1];
		for(int i=1;i<n;i++)
			cin>>u[i-1]>>v[i-1];

		init(tid,n,x,y,m,u,v,l,r);
		
		for(int i=1;i<=q1;i++)
		{
			cin>>V;
			gt=query1(V);
			cout<<gt<<"\n";
			G[V]=gt;
		}

		for(int i=1;i<=q2;i++)
		{
			cin>>V;
			tk=query2(V,G[V]);
			for(int g:tk) cout<<g<<" ";
			cout<<"\n";
		}
	}
}
int main()
{
	Grader::main();
	return 0;
}
