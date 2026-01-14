#include "archae.h"
#include <bits/stdc++.h>
#define quit(str) printf(str),exit(1);
using namespace std;
namespace grader
{
	int o,n,T;
	int G[3011][3011];
	int CNT;
	bool query(int x,int y)
	{
		++CNT;
		if(!(1<=x&&x<=n&&1<=y&&y<=n)) cerr<<x<<' '<<y<<endl,quit("x or y out of range.\n");
		if(CNT>30*n)quit("Too many queries.\n");
		return G[x][y];
	}
	void setTestType(int _o){o=_o;}
	int main()
	{
		freopen("archae.in","r",stdin);freopen("archae.out","w",stdout);//setvbuf(stdout,0,_IONBF,0);
		scanf("%d",&T);while(T--)
		{
			CNT=0;
			scanf("%d",&n);
			for(int i=1;i<=n;++i)for(int j=1;j<=n;++j)scanf("%d",G[i]+j);
			vector<int> vv=archae(n);
			for(int x:vv)printf("%d ",x);putchar(10);
			printf("CNT:%d\n",CNT);
		}
		fclose(stdin);fclose(stdout);return 0;
	}
}
bool query(int x,int y){return grader::query(x,y);}
void setTestType(int _o){grader::setTestType(_o);}
int main()
{
	grader::main();
}