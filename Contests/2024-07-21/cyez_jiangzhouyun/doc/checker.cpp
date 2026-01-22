#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
const int N = 1e6 + 5,Lim = 1e6;
int n,k;
int U[N],V[N];
vector<int> G[N],Q[N];
int Path[N];
int ton[N];
int main(int argc,char **argv)
{
	registerTestlibCmd(argc,argv);
	int T = inf.readInt();
	while(T--)
	{
		n = inf.readInt(1,Lim);
		k = inf.readInt(1,n);

		for(int i = 1;i <= n;i++)
		{
			vector<int>().swap(G[i]);
			vector<int>().swap(Q[i]);
			ton[i] = 0;
		}
			
		for(int i = 1;i < n;i++)
			U[i] = inf.readInt(1,n),
			V[i] = inf.readInt(1,n),
			G[U[i]].push_back(V[i]),
			G[V[i]].push_back(U[i]);

		int pans = ouf.readInt(),jans = ans.readInt();
		if(pans > jans) quitf(_wa,"WrongAnswer[1]\n");

		for(int i = 1;i <= pans;i++)
			Path[i] = ouf.readInt(1,n);
		for(int i = 1;i <= jans;i++)
			ans.readInt(1,n);
		for(int i = 1;i < pans;i++)
			Q[Path[i]].push_back(Path[i + 1]);

		for(int i = 1;i <= n;i++)
			sort(G[i].begin(),G[i].end()),
			sort(Q[i].begin(),Q[i].end());

		for(int i = 1;i <= n;i++)
		{
			int j = 0,k = 0;
			while(j < (int)Q[i].size())
			{
				while(k < (int)G[i].size() && G[i][k] < Q[i][j]) ++k;
				if(k >= (int)G[i].size() || G[i][k] != Q[i][j]) quitf(_wa,"WrongAnswer[2]\n");
				++j;
			}
		}
        for(int i = 1;i <= n;i++)
            ton[i] = 0;
		for(int i = 1;i <= pans;i++)
			ton[Path[i]]++;
		int sum = 0;
		for(int i = 1;i <= n;i++)
			sum += (ton[i] > 0);
		if(sum != k) quitf(_wa,"WrongAnswer[3]\n");
		if(pans < jans) quitf(_fail,"The participant's answer is better than the Judge's\n");
	}
    quitf(_ok, "Accepted");
	return 0;
}