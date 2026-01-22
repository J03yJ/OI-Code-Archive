#include<bits/stdc++.h>

using namespace std;

const int N=5e2+9;
int vis[N][N][N];

int main(){
    int n,k;
    cin>>n>>k;

    if(n%3==0||k%3<2){
        int m=k/3,cnt=0;
        vector<array<int,3>> res;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                int a=i,b=j,c=(n+n-i-j)%n;
                if(vis[a][b][c]) continue ;
                vis[a][b][c]=vis[c][a][b]=vis[b][c][a]=1;
                if(a==b&&b==c){
                    res.push_back({a,b,c});
                    continue ;
                }
                if(!m) continue ;
                m--;cnt+=3;
                cout<<a<<' '<<b<<' '<<c<<endl;
                cout<<b<<' '<<c<<' '<<a<<endl;
                cout<<c<<' '<<a<<' '<<b<<endl;
            }
        }
        for(int i=0;i<k-cnt;i++) cout<<res[i][0]<<' '<<res[i][1]<<' '<<res[i][2]<<endl;
    }else{
        int m=k/3,cnt=0;
        vector<array<int,3>> res;
        res.push_back({1,1,1});
        vis[1][1][n-2]=vis[n-2][1][1]=vis[1][n-2][1]=1;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                int a=i,b=j,c=(n+n-i-j)%n;
                if(vis[a][b][c]) continue ;
                // cout<<a<<' '<<b<<' '<<c<<endl;
                if(a==b&&b==c){
                    res.push_back({a,a,a});
                    continue ;
                }
                if(!m) continue ;
                m--;cnt+=3;
                cout<<a<<' '<<b<<' '<<c<<endl;
                cout<<b<<' '<<c<<' '<<a<<endl;
                cout<<c<<' '<<a<<' '<<b<<endl;
                vis[a][b][c]=vis[c][a][b]=vis[b][c][a]=1;
            }
        }
        for(int i=0;i<k-cnt;i++) cout<<res[i][0]<<' '<<res[i][1]<<' '<<res[i][2]<<endl;
    }

    return 0;
}