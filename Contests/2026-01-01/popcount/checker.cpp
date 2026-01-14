#include <bits/stdc++.h>

using namespace std;

const int MAXN = (1 << 10) + 10;
const int fx[4] = {-1, 1, 0, 0}, fy[4] = {0, 0, -1, 1};

int n, m;
int a[MAXN][MAXN];
bool vis[MAXN * MAXN];

int main(int argc, char* argv[]) {
	FILE *inf = fopen(argv[1], "r");
	FILE *ansf = fopen(argv[2], "r");
	fscanf(inf, "%d %d", &n, &m);
	n = 1 << n, m = 1 << m;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j) {
			fscanf(ansf, "%d", &a[i][j]);
			if(a[i][j] < 0 || a[i][j] > n * m - 1) {
				printf("Wrong Answer!\nThe element on (%d, %d) : %d violents the bound.\n", i, j, a[i][j]);
				return 0;
			}
			if(vis[a[i][j]]) {
				printf("Wrong Answer!\nThe element on (%d, %d) : %d repeated.\n", i, j, a[i][j]);
				return 0;
			}
			vis[a[i][j]] = true;
		}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			for(int k = 0, x, y; k < 4; ++k) {
				x = i + fx[k], y = j + fy[k];
				if(x < 1) x = n; if(x > n) x = 1;
				if(y < 1) y = m; if(y > m) y = 1;
				if(x == i && y == j) continue;
				if(__builtin_popcount(a[i][j] ^ a[x][y]) != 1) {
					printf("Wrong Answer!\nThe popcount of (%d, %d) xor (%d, %d) is %d.\n", 
							i, j, x, y, __builtin_popcount(a[i][j] ^ a[x][y]));
					return 0;
				}
			}
	printf("Accepted.\njuju AK IOI!/se/se/se\n");
	return 0;
}
