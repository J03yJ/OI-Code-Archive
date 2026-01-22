#include <bits/stdc++.h>
using namespace std;
#define maxn 1005
#define ll long long int
int d[4], top, stk[maxn * maxn];
int fa[maxn * maxn];
struct node{
    int id, h;
    bool operator <(const node &t)const{
        return h < t.h;
    }
}seq[maxn*maxn];
ll ans;
int area[maxn * maxn], h[maxn * maxn];
bool bj[maxn * maxn];

int n, m, tot;
int findroot(int a){
    top = 0;
    while(fa[a]) {stk[top++] = a, a = fa[a];}
    while(top) {fa[stk[--top]] = a;}
    return a;
}
void merge(int a, int b){
    int ra = findroot(a), rb = findroot(b);
    if(ra != rb){
        fa[ra] = rb;
        area[rb] += area[ra];
    }
}
int main(){
    // freopen("garden3.in", "r", stdin);
    scanf("%d %d", &n, &m);
    d[0] = -1, d[1] = 1, d[2] = -m, d[3] = m;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            ++tot;
            scanf("%d",&h[tot]);
            seq[tot].id = tot, seq[tot].h = h[tot];
            area[tot] = 1;
            if(i == 1 || i == n || j == 1 || j == m) bj[tot] = 1;
        }
    }
    sort(seq + 1, seq + tot + 1);
    for(int i = 1; i <= tot; i++){
        bool flg = 0;
        int id = seq[i].id, nid = 0, cur, rt;
        area[tot] = 1;
        cur = findroot(id);
        for(int j = 0; j < 4; j++){
            if(j == 0 && id % m == 1 || j == 1 && id % m == 0 || j == 2 && id <= m || j == 3 && id > (n - 1) * m)continue;
            nid = id + d[j];
            rt = findroot(nid);
            if(h[rt] > h[cur]) continue;
            if(bj[rt] == 0) {
                ans += area[rt] * (h[cur] - h[rt]);
                merge(rt, cur);
            }
            else flg = 1;
        }
        if(flg == 1) bj[cur] = 1, area[cur] = 0;
    }
    printf("%lld\n", ans);
    return 0;
}