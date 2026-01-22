#include<bits/stdc++.h>

using namespace std;

ifstream fin("crystal.in");
ofstream fout("crystal.out");
#define cin fin
#define cout fout

const int N=2e3+9;

int a[N][N],f[N][N],ind[N][N],vis[N][N],lim[N],n;
vector<pair<int,int>> e[N][N];
bool Valid(pair<int,int> x){
    if(x.first<1||x.first>=(n<<1)) return 0;
    else if(x.second<1||x.second>lim[x.first]) return 0;
    else return 1;
}
void AdEg(pair<int,int> x,pair<int,int> y){
    if(!Valid(x)||!Valid(y)) return ;
    ind[y.first][y.second]++;
    e[x.first][x.second].push_back(y);
}

int main(){
    cin>>n;
    for(int i=1;i<n;i++) lim[i]=i+n-1;
    for(int i=n;i<(n<<1);i++) lim[i]=n+n-(i-n+1);
    for(int i=1;i<(n<<1);i++){
        for(int j=1;j<=lim[i];j++) cin>>a[i][j];
    }

    for(int i=1;i<n;i++){
        for(int j=1;j<=lim[i];j++){
            AdEg({i,j},{i-1,j});
            AdEg({i,j},{i+1,j});
            AdEg({i,j},{i,j-1});
            AdEg({i,j},{i-1,j-1});
            AdEg({i,j},{i,j+1});
            AdEg({i,j},{i+1,j+1});
        }
    }
    for(int i=n;i<=n;i++){
        for(int j=1;j<=lim[i];j++){
            AdEg({i,j},{i-1,j});
            AdEg({i,j},{i+1,j});
            AdEg({i,j},{i,j-1});
            AdEg({i,j},{i-1,j-1});
            AdEg({i,j},{i+1,j-1});
            AdEg({i,j},{i,j+1});
        }
    }
    for(int i=n+1;i<(1<<n);i++){
        for(int j=1;j<=lim[i];j++){
            AdEg({i,j},{i-1,j});
            AdEg({i,j},{i+1,j});
            AdEg({i,j},{i,j-1});
            AdEg({i,j},{i+1,j-1});
            AdEg({i,j},{i,j+1});
            AdEg({i,j},{i-1,j+1});
        }
    }

    queue<pair<int,int>> q;
    for(int i=1;i<(1<<n);i++){
        for(int j=1;j<=lim[i];j++){
            if(ind[i][j]<6){
                f[i][j]=vis[i][j]=1;
                q.push({i,j});
            }else{
                bool err=0;
                for(pair<int,int> x:e[i][j]){
                    if(a[x.first][x.second]!=a[i][j]){
                        err=1;
                        break ;
                    }
                }
                if(!err) continue ;
                f[i][j]=vis[i][j]=1;
                q.push({i,j});
            }
        }
    }
    while(q.size()){
        pair<int,int> x=q.front();
        q.pop();
        for(pair<int,int> y:e[x.first][x.second]){
            if(vis[y.first][y.second]) continue ;
            f[y.first][y.second]=f[x.first][x.second]+1;
            vis[y.first][y.second]=1;
            q.push(y);
        }
    }

    for(int i=1;i<(n<<1);i++){
        for(int j=1;j<=lim[i];j++) cout<<f[i][j]<<' ';
        cout<<endl;
    }

    return 0;
}