#include <bits/stdc++.h>
using namespace std;
#define maxn 1005
#define ll long long int
int n, m, top, tot;
int dd[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};
int arr[maxn][maxn], stk[maxn * maxn], h[maxn*maxn], area[maxn*maxn];
bool vis[maxn][maxn];
int fa[maxn * maxn];
ll ans;

struct node{
    int r, c, h;
    bool operator < (const node &t)const{
        return h < t.h ||(h == t.h && r < t.r) || (h == t.h && r == t.r && c < t.c);
    }
}seq[maxn*maxn];

int findroot(int x){
    top = 0;
    while(fa[x])stk[top++] = x, x = fa[x];
    while(top)fa[stk[--top]] = x;
    return x;
}

void merge(int x, int y, int he){
    int rx = findroot(x), ry = findroot(y);
    if(rx == ry) return;
    else{
        fa[rx] = ry;
        h[ry] = he;
        area[ry] += area[rx];
    }
}

int find_minh(int t){
    int x = seq[t].r, y = seq[t].c, h = seq[t].h;
    int minz = INT_MAX;
    for(int i = 0; i < 4; i++){
        if(arr[x + dd[i][0]][y + dd[i][1]] < minz) minz = arr[x + dd[i][0]][y + dd[i][1]];
        if(minz == -1) return minz;
    }
    return minz;
}

int main(){
    // freopen("garden3.in", "r", stdin);
    scanf("%d %d", &n, &m);
    for(int i = 1;  i <= n; i++){
        for(int j = 1; j <= m; j++){
            scanf("%d", &arr[i][j]);
            h[(i-1)*m+j] = arr[i][j];
            seq[tot].h = arr[i][j];
            seq[tot].r = i, seq[tot].c = j;
            tot++;
        }
    }
    for(int i = 1; i <= n; i++) arr[i][0] = arr[i][m + 1] = -1;
    for(int i = 1; i <= m; i++) arr[0][i] = arr[n + 1][i] = -1;
    sort(seq, seq + tot);
    for(int i = 0; i < tot; i++){
        int x = seq[i].r, y = seq[i].c, cur = (x - 1) * m + y;
        ll tmp = 0;
        area[cur] = 1;
        bool flg = 0;
        for(int j = 0; j < 4; j++){
            tmp = 0;
            int xx = x + dd[j][0], yy = y + dd[j][1], cc = (xx - 1) * m + yy;
            if(xx < 1 || xx > n || yy < 1 || yy > m) {flg = 1; continue;}
            if(arr[xx][yy] != -1 &&  area[cc] > 0){
                int rt = findroot(cc);
                 if(rt != cur && h[rt] != -1) {
                    ans += area[rt] * (seq[i].h - h[rt]);
                    merge(rt, cur, seq[i].h);
                 }
                 else if(h[rt] == -1){
                    flg = 1;
                 }
            }
            else{
                if(arr[xx][yy] == -1) flg = 1;
            }
        }
        if(flg == 1) h[cur] = -1;
    }
    printf("%lld\n",ans);
    return 0;
}