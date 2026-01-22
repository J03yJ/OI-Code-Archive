#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cassert>
using namespace std;

#define LOG(f...) fprintf(stderr, f)
#define all(cont) begin(cont), end(cont)

using ll = long long;

const int N = 100005;
const ll IINF = 2e9;
const ll INF = 1e17;

struct pt { int x, y; };

struct discretizer {
  vector<int> v;
  void clear() { v.clear(); }
  void add(int x) { v.push_back(x); }
  void init() { sort(all(v)); v.erase(unique(all(v)), end(v)); }
  int operator()(int x) const { return lower_bound(all(v), x) - begin(v); }
};

struct min_seg_tree {
  static const int LEN = 1 << 21;
  pair<int, pair<int, int>> t[LEN * 2];
  void init() { memset((void *)t, 0x3f, sizeof(t)); }
  min_seg_tree() { init(); }
  void update(int p, ll v, int id) {
    if (v > 0x3f3f3f3f) return;
    p += LEN;
    if (t[p].first <= v) return;
    t[p].first = v; t[p].second = {p - LEN, id};
    for (p >>= 1; p; p >>= 1)
      t[p] = t[p << 1].first < t[p << 1 | 1].first ? t[p << 1] : t[p << 1 | 1];
  }
  void assign(int p, ll v, int id) {
    if (v > 0x3f3f3f3f) return;
    p += LEN;
    if (t[p].first == v && t[p].second.second == id) return;
    t[p].first = v; t[p].second = {p - LEN, id};
    for (p >>= 1; p; p >>= 1)
      t[p] = t[p << 1].first < t[p << 1 | 1].first ? t[p << 1] : t[p << 1 | 1];
  }
  void erase(int p) {
    p |= LEN; t[p].first = 0x3f3f3f3f;
    for (p >>= 1; p; p >>= 1)
      t[p] = t[p << 1].first < t[p << 1 | 1].first ? t[p << 1] : t[p << 1 | 1];
  }
  pair<int, pair<int, int>> top() const { return t[1]; }
};

struct seg_node {
  ll b;
  pair<ll, int> mn;
  int pos, pos_id;
  int lc, rc;
} t[N * 32 * 3];
int nc = 0;

int n;
pt p[N];
discretizer dx, dy, d0, d1;
min_seg_tree H;
int idx[N], idy[N], id0[N], id1[N];
int rtx[N][4], rty[N][4], rt0[N][4], rt1[N][4];

template<int k>
struct seg_op {
  static const ll pos_init = k < 0 ? -IINF : IINF;
  static ll pos_v(int x) { return x ? t[x].pos : pos_init; }
  static int new_node() {
    ++nc;
    t[nc].mn = {INF, 0}; t[nc].b = INF; t[nc].pos = pos_init; t[nc].lc = t[nc].rc = 0;
    return nc;
  }
  static void up(int x) {
    auto &u = t[x], &lc = t[t[x].lc], &rc = t[t[x].rc];
    t[x].mn = min(lc.mn, rc.mn);
    if (k > 0) {
      if (pos_v(t[x].lc) < pos_v(t[x].rc)) u.pos = pos_v(t[x].lc), u.pos_id = lc.pos_id;
      else u.pos = pos_v(t[x].rc), u.pos_id = rc.pos_id;
    }
    else {
      if (pos_v(t[x].lc) > pos_v(t[x].rc)) u.pos = pos_v(t[x].lc), u.pos_id = lc.pos_id;
      else u.pos = pos_v(t[x].rc), u.pos_id = rc.pos_id;
    }
    t[x].mn = min(t[x].mn, make_pair((ll)k * t[x].pos + t[x].b, t[x].pos_id));
  }
  static void insert(int &x, int l, int r, int p, ll mn, int id) {
    if (!x) x = new_node();
    if ((k > 0 && p < t[x].pos) || (k < 0 && p > t[x].pos))
      t[x].pos = p, t[x].pos_id = id;
    t[x].mn = min(t[x].mn, make_pair(mn, id));
    if (l == r) return;
    int mid = (l + r) >> 1;
    p <= mid ? insert(t[x].lc, l, mid, p, mn, id) : insert(t[x].rc, mid + 1, r, p, mn, id);
  }
  static void erase(int &x, int l, int r, int p) {
    if (l == r) { x = 0; return; }
    int mid = (l + r) >> 1;
    p <= mid ? erase(t[x].lc, l, mid, p) : erase(t[x].rc, mid + 1, r, p);
    if (!t[x].lc && !t[x].rc) x = 0;
    else up(x);
  }
  static void update(int &x, int l, int r, int ql, int qr, ll b) {
    if (!x || ql > qr) return;
    if (ql <= l && r <= qr) {
      t[x].b = min(t[x].b, b);
      if (t[x].pos != pos_init) t[x].mn = min(t[x].mn, make_pair(t[x].b + t[x].pos * k, t[x].pos_id));
      return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid) update(t[x].lc, l, mid, ql, qr, b);
    if (qr > mid) update(t[x].rc, mid + 1, r, ql, qr, b);
    up(x);
  }
};

int min_x, max_x, min_y, max_y;

int dir[N];

// rt0 : -2 -2 2 2
// rt1 : -2 2 2 -2

void insert_pt(int i) {
  int D = dir[i];
  ll V = i == 0 ? 0 : INF;
  D & 2 ? seg_op<2>::insert(rt0[id0[i]][D], min_x, max_x, p[i].x, V, i)
        : seg_op<-2>::insert(rt0[id0[i]][D], min_x, max_x, p[i].x, V, i);
  D == 1 || D == 2 ? seg_op<2>::insert(rt1[id1[i]][D], min_x, max_x, p[i].x, V, i)
                   : seg_op<-2>::insert(rt1[id1[i]][D], min_x, max_x, p[i].x, V, i);
  if (D == 0) seg_op<-1>::insert(rty[idy[i]][D], min_x, max_x, p[i].x, V, i);
  else if (D == 2) seg_op<1>::insert(rty[idy[i]][D], min_x, max_x, p[i].x, V, i);
  else if (D == 1) seg_op<-1>::insert(rtx[idx[i]][D], min_y, max_y, p[i].y, V, i);
  else if (D == 3) seg_op<1>::insert(rtx[idx[i]][D], min_y, max_y, p[i].y, V, i);
}

void heap_up(int id, int tid) {
  H.update(id, t[tid].mn.first, t[tid].mn.second);
}

void heap_assign(int id, int tid) {
  H.assign(id, t[tid].mn.first, t[tid].mn.second);
}

void erase_pt(int i) {
  int D = dir[i];
  D & 2 ? seg_op<2>::erase(rt0[id0[i]][D], min_x, max_x, p[i].x)
        : seg_op<-2>::erase(rt0[id0[i]][D], min_x, max_x, p[i].x);
  heap_assign(id0[i] << 4 | 8 | D, rt0[id0[i]][D]);
  D == 1 || D == 2 ? seg_op<2>::erase(rt1[id1[i]][D], min_x, max_x, p[i].x)
                   : seg_op<-2>::erase(rt1[id1[i]][D], min_x, max_x, p[i].x);
  heap_assign(id1[i] << 4 | 12 | D, rt1[id1[i]][D]);
  if (D == 0) seg_op<-1>::erase(rty[idy[i]][D], min_x, max_x, p[i].x);
  else if (D == 2) seg_op<1>::erase(rty[idy[i]][D], min_x, max_x, p[i].x);
  else if (D == 1) seg_op<-1>::erase(rtx[idx[i]][D], min_y, max_y, p[i].y);
  else if (D == 3) seg_op<1>::erase(rtx[idx[i]][D], min_y, max_y, p[i].y);
  if (D == 0 || D == 2)
    heap_assign(idy[i] << 4 | 4 | D, rty[idy[i]][D]);
  else
    heap_assign(idx[i] << 4 | 0 | D, rtx[idx[i]][D]);
}

void update_pt(int i, int dis) {
  int slen = (dis + 1) / 2, slen_v = slen * 2;
  switch (dir[i]) {
    case 0:
      seg_op<2>::update(rt0[id0[i]][3], min_x, max_x, p[i].x + slen, max_x, slen_v - 2LL * (p[i].x + slen));
      heap_up(id0[i] << 4 | 8 | 3, rt0[id0[i]][3]);
      seg_op<2>::update(rt1[id1[i]][1], min_x, max_x, p[i].x + slen, max_x, slen_v - 2LL * (p[i].x + slen));
      heap_up(id1[i] << 4 | 12 | 1, rt1[id1[i]][1]);
      seg_op<1>::update(rty[idy[i]][2], min_x, max_x, p[i].x + dis, max_x, dis - (p[i].x + dis));
      heap_up(idy[i] << 4 | 4 | 2, rty[idy[i]][2]);
      break;
    case 1:
      seg_op<2>::update(rt0[id0[i]][2], min_x, max_x, p[i].x + slen, max_x, slen_v - 2LL * (p[i].x + slen));
      heap_up(id0[i] << 4 | 8 | 2, rt0[id0[i]][2]);
      seg_op<-2>::update(rt1[id1[i]][0], min_x, max_x, min_x, p[i].x - slen, slen_v + 2LL * (p[i].x - slen));
      heap_up(id1[i] << 4 | 12 | 0, rt1[id1[i]][0]);
      seg_op<1>::update(rtx[idx[i]][3], min_y, max_y, p[i].y + dis, max_y, dis - (p[i].y + dis));
      heap_up(idx[i] << 4 | 0 | 3, rtx[idx[i]][3]);
      break;
    case 2:
      seg_op<-2>::update(rt0[id0[i]][1], min_x, max_x, min_x, p[i].x - slen, slen_v + 2LL * (p[i].x - slen));
      heap_up(id0[i] << 4 | 8 | 1, rt0[id0[i]][1]);
      seg_op<-2>::update(rt1[id1[i]][3], min_x, max_x, min_x, p[i].x - slen, slen_v + 2LL * (p[i].x - slen));
      heap_up(id1[i] << 4 | 12 | 3, rt1[id1[i]][3]);
      seg_op<-1>::update(rty[idy[i]][0], min_x, max_x, min_x, p[i].x - dis, dis + (p[i].x - dis));
      heap_up(idy[i] << 4 | 4 | 0, rty[idy[i]][0]);
      break;
    case 3:
      seg_op<-2>::update(rt0[id0[i]][0], min_x, max_x, min_x, p[i].x - slen, slen_v + 2LL * (p[i].x - slen));
      heap_up(id0[i] << 4 | 8 | 0, rt0[id0[i]][0]);
      seg_op<2>::update(rt1[id1[i]][2], min_x, max_x, p[i].x + slen, max_x, slen_v - 2LL * (p[i].x + slen));
      heap_up(id1[i] << 4 | 12 | 2, rt1[id1[i]][2]);
      seg_op<-1>::update(rtx[idx[i]][1], min_y, max_y, min_y, p[i].y - dis, dis + (p[i].y - dis));
      heap_up(idx[i] << 4 | 0 | 1, rtx[idx[i]][1]);
      break;
  }
}

bool vis[N];

int solve() {
  dir[0] = 0;
  for (int i = 1; i < n; ++i) {
    if (abs(p[i].x) == abs(p[i].y))
      dir[i] = p[i].x < 0 ? 0 : (p[i].y > 0 ? 3 : 1);
    else if (abs(p[i].x) > abs(p[i].y))
      dir[i] = p[i].x > 0 ? 2 : 0;
    else
      dir[i] = p[i].y > 0 ? 3 : 1;
  }
  dx.clear(); dy.clear(); d0.clear(); d1.clear();
  for (int i = 0; i < n; ++i)
    dx.add(p[i].x), dy.add(p[i].y), d0.add(p[i].x - p[i].y), d1.add(p[i].x + p[i].y);
  dx.init(); dy.init(); d0.init(); d1.init();
  for (int i = 0; i < n; ++i)
    tie(idx[i], idy[i], id0[i], id1[i]) = make_tuple(dx(p[i].x), dy(p[i].y), d0(p[i].x - p[i].y), d1(p[i].x + p[i].y));
  min_x = IINF; max_x = -IINF;
  for (int i = 0; i < n; ++i) {
    min_x = min(min_x, p[i].x), max_x = max(max_x, p[i].x);
    min_y = min(min_y, p[i].y), max_y = max(max_y, p[i].y);
  }
  nc = 0;
  memset(rtx, 0, sizeof(rtx)); memset(rty, 0, sizeof(rty)); memset(rt0, 0, sizeof(rt0)); memset(rt1, 0, sizeof(rt1));
  for (int i = 0; i < n; ++i)
    insert_pt(i);
  H.update(idy[0] << 4 | 4 | 0, 0, 0);
  H.update(id0[0] << 4 | 8 | dir[0], 0, 0);
  H.update(id1[0] << 4 | 12 | dir[0], 0, 0);
  fill(vis, vis + n, false);
  int res = 0;
  while (H.top().first != 0x3f3f3f3f) {
    int val = H.top().first;
    int id = H.top().second.first;
    int x = H.top().second.second;
    H.erase(id);
    if (vis[x]) continue;
    erase_pt(x);
    vis[x] = true;
    ++res;
    update_pt(x, val);
  }
  return res;
}

int main() {
  freopen("ants.in", "r", stdin);
  freopen("ants.out", "w", stdout);
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%d%d", &p[i].x, &p[i].y);
  for (int i = 1; i < n; ++i)
    p[i].x -= p[0].x, p[i].y -= p[0].y;
  p[0].x = 0; p[0].y = 0;
  t[0].mn = {INF, 0};
  int res = 0;
  for (int i = 0; i < 4; ++i) {
    res = max(res, solve());
    transform(p, p + n, p, [](const pt &p) ->pt { return {-p.y, p.x}; });
  }
  printf("%d\n", res);
  return 0;
}
