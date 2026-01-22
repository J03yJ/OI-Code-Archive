#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
	registerTestlibCmd(argc, argv);
	
	int T = inf.readInt();
	int correct = 1;
	for(int t=1;t<=T;t++) {
		int n = inf.readInt(), m = inf.readInt(), k = inf.readInt();
		
		map<pair<int, int>, int> edge;
		for (int i = 1; i < n; ++i) {
			int x = inf.readInt();
			int y = inf.readInt();
			edge[make_pair(x, y)] = 1;
			edge[make_pair(y, x)] = 1;
		}
		
		string usr_result = ouf.readToken();
		string std_result = ans.readToken();
		if (usr_result != std_result) {
			quitf(_wa," on %d Y/N",t);
			correct = 0;
		}
		
		if (usr_result == "Yes") {
			vector<int> v(m), vis(n + 1);
			for (int i = 0; i < m; ++i) {
				v[i] = ouf.readInt();
				if (v[i] < 1 || v[i] > n) {
					correct = 0;
					quitf(_wa," on %d Over",t);
				} else {
					vis[v[i]] = 1;
				}
			}
			for (int i = 1; i < m; ++i) {
				if (!edge[make_pair(v[i - 1], v[i])]) correct = 0;
			}
			int cnt = 0;
			for (int i = 1; i <= n; ++i) if (vis[i]) ++cnt;
			if (cnt != k) correct = 0,quitf(_wa," on %d Neq K",t);
		}
	}
	
	if (!correct) {
		quitf(_wa, "");
	} else {
		quitf(_ok, "");
	}
	
	return 0;
}
