#include <queue>

#include "testlib.h"

using namespace std;

using ull = unsigned long long;
using ll = long long;
using LL = __int128;

const LL LIM = LL(1) << 80;

const int N = 1050;

const int SUBSET_L = 2;
const int SUBSET = 1 << SUBSET_L;

int n;

int topo[N], deg[N];
vector<int> g[N];
set<pair<int, int>> st;
ull clo[N][N >> 6];

LL sum[N >> 2][16];

void setv(int pos, LL x) {
  int i = pos >> SUBSET_L, j = pos & (SUBSET - 1);
  for (int t = 0; t < (1 << SUBSET); ++t)
    if ((t >> j) & 1)
      sum[i][t] += x;
}

LL gets(ull* bs) {
  LL ret = 0;
  for (int i = 0; i <= (n >> SUBSET_L); ++i)
    ret += sum[i][(bs[i >> (6 - SUBSET_L)] >> ((i & ((1 << (6 - SUBSET_L)) - 1)) << SUBSET_L)) & ((1 << SUBSET) - 1)];
  return ret;
}

void bitOR(ull* as, ull* bs) {
  for (int i = 0; i <= (n >> 6); ++i)
    as[i] |= bs[i];
}

void bitSET(ull* bs, int pos) {
  bs[pos >> 6] |= 1ULL << (pos & 63);
}

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  ll k = inf.readLong(static_cast<ll>(-1e18), static_cast<ll>(1e18), "k");

  n = ouf.readInt(1, 1000, "n");
  int m = ouf.readInt(0, 1000, "m");
  while (m--) {
    int x, y;
    x = ouf.readInt(1, n, "x");
    y = ouf.readInt(1, n, "y");
    if (!st.insert(make_pair(x, y)).second)
      quitf(_wa, "edge (%d, %d) appeared twice", x, y);
    g[--x].push_back(--y);
    ++deg[y];
  }

  queue<int> q;
  for (int i = 0; i < n; ++i) if (!deg[i]) q.push(i);
  int cnt = 0;
  while (!q.empty()) {
    int u = topo[cnt++] = q.front(); q.pop();
    for (int v : g[u])
      if (!--deg[v])
        q.push(v);
  }
  if (cnt != n) quitf(_wa, "not a DAG");

  LL res = 0;
  for (int s = 0; s < n; ++s) {
    memset(sum, 0, sizeof(sum));
    memset(clo, 0, sizeof(clo));
    setv(s, 1);
    bitSET(clo[s], s);
    for (int i = n - 1; i >= 0; --i) {
      int u = topo[i];
      if (u == s) {
        if (u == 0 && s == n - 1)
          res = 1;
        continue;
      }
      for (int v : g[u])
        bitOR(clo[u], clo[v]);
      LL trns = -gets(clo[u]);
      if (trns > LIM || trns < -LIM)
        quitf(_wa, "abs(trns(%d, %d)) exceeded 2^80", u + 1, s + 1);
      bitSET(clo[u], u);
      setv(u, trns);
      if (u == 0 && s == n - 1)
        res = trns;
    }
  }
  if (res == k)
    quitf(_ok, "trns(1, %d) = %lld", n, k);
  else if (res > 1LL << 62 || res < -(1LL << 62))
    quitf(_wa, "trns(1, %d) expected %lld, found %Le", n, k, (long double)(res));
  else
    quitf(_wa, "trns(1, %d) expected %lld, found %lld", n, k, (ll)res);

  return 0;
}
