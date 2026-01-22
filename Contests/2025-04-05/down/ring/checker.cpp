#include "testlib.h"
#define LOG(FMT...) fprintf(stderr, FMT)
using namespace std;
const int N = 2005;
int n, m;
vector<int> e[N], re[N];
set<int> ed[N];
int deg[N], w[N];
double sqr(double x) {
	return x * x;
}
int main(int argc, char* argv[]) {
	registerTestlibCmd(argc, argv);
	n = inf.readInt(1, 2000);
	m = ouf.readInt(0, 100000);
	for (int i = 0; i < m; ++i) {
		int x, y;
		x = ouf.readInt(1, n);
		y = ouf.readInt(1, n);
		if (x == y) {
			quitf(_wa, "find 1-cyc (%d)", x);
		}
		if (ed[x].count(y) || ed[y].count(x)) {
			quitf(_wa, "find 2-cyc (%d, %d)", x, y);
		}
		ed[x].insert(y);
		++deg[x], ++deg[y];
	}
	for (int x = 1; x <= n; ++x) {
		for (set<int>::iterator it = ed[x].begin(); it != ed[x].end(); ++it) {
			int y = *it;
			if (deg[x] > deg[y] || deg[x] == deg[y] && x > y) {
				e[x].push_back(y);
				re[y].push_back(x);
			} else {
				e[y].push_back(x);
				re[x].push_back(y);
			}
		}
	}
	for (int x = 1; x <= n; ++x) {
		for (int z : e[x]) {
			++w[z];
		}
		for (int y = x + 1; y <= n; ++y) {
			int cnt = 0;
			for (int z : e[y]) {
				cnt += w[z];
			}
			if (cnt >= 2) {
				quitf(_wa, "wa");
			}
		}
		for (int z : e[x]) {
			w[z] = 0;
		}
	}
	for (int x = 1; x <= n; ++x) {
		for (int y : e[x]) {
			for (int z : e[y]) {
				++w[z];
			}
		}
		for (int y : e[x]) {
			if (w[y]) {
				for (int z : re[y]) {
					if (find(re[z].begin(), re[z].end(), x) != re[z].end()) {
						quitf(_wa, "find 3-cyc (%d, %d, %d)", x, y, z);
					}
				}
				LOG("ERR\n");
				return 0;
			}
		}
		for (int y : e[x]) {
			for (int z : e[y]) {
				if (w[z] > 1) {
					for (int w : re[z]) {
						if (w != y && find(re[w].begin(), re[w].end(), x) != re[w].end()) {
							quitf(_wa, "find 4-cyc (%d, %d, %d, %d)", x, y, z, w);
						}
					}
					LOG("ERR\n");
					exit(0);
				}
			}
		}
		for (int y : e[x]) {
			for (int z : re[y]) {
				if (w[z]) {
					for (int w : re[z]) {
						if (find(re[w].begin(), re[w].end(), x) != re[w].end()) {
							quitf(_wa, "find 4-cyc (%d, %d, %d, %d)", x, y, z, w);
						}
					}
					LOG("ERR\n");
					exit(0);
				}
			}
		}
		for (int y : e[x]) {
			for (int z : e[y]) {
				w[z] = 0;
			}
		}
	}
	int lim = ans.readInt();
	if (m >= lim) {
		quitf(_ok, "Accepted.\nEdges: %d\n", m);
	} else {
		quitp(sqr(10. * m / lim), "\nEdges: %d\n", m);
	}
	return 0;
}
