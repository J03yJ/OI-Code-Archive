#include <bits/stdc++.h>
using namespace std;
#define maxn 1005
#define ll long long int
bool flg[maxn][maxn];
ll ans;
struct node{
    int r, c, maxz;
    node(int _r, int _c, int _maxz){
        r = _r, c = _c, maxz = _maxz;
    }
    bool operator <(const node &t)const{
        return maxz > t.maxz;
    }
};
priority_queue<node> myq; 
int h[maxn][maxn], arr[maxn][maxn];
int d[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
int n, m;

void bfs(){
    while(!myq.empty()){
        node tmp = myq.top();
        int x = tmp.r, y = tmp.c;
        myq.pop();
        if(flg[x][y] == 0) continue;
        flg[x][y] = 0;
        int xx, yy;
        for(int j = 0; j < 4; j++){
            xx = x + d[j][0], yy = y + d[j][1];
            if(xx > 0 && xx <= n && yy > 0 && yy <= m){
                if(h[xx][yy] > max(arr[xx][yy],h[x][y])){
                    h[xx][yy] = max(arr[xx][yy],h[x][y]);
                    myq.push(node(xx, yy, h[xx][yy]));
                    flg[xx][yy] = 1;
                }
            }
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++)scanf("%d", &arr[i][j]);
    }
    memset(h, 0x3f, sizeof h);
    for(int i = 1; i <= n; i++) {
        myq.push(node(i,1,arr[i][1]));
        myq.push(node(i, m, arr[i][m]));
        h[i][1] = arr[i][1], h[i][m] = arr[i][m];
        flg[i][1] = 1;
        flg[i][m] = 1;

    }
    for(int i = 2; i < m; i++){
        myq.push(node(1, i, arr[1][i]));
        myq.push(node(n, i, arr[n][i]));
        h[1][i] = arr[1][i];
        h[n][i] = arr[n][i];
        flg[1][i] = 1, flg[n][i] = 1;
    }
    bfs();
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            ans += h[i][j] - arr[i][j];
        }
    }
    printf("%lld\n", ans);
    return 0;
}