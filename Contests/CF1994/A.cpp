#include<bits/stdc++.h>

using namespace std;

const int N=2e2+9;

int a[N][N];

int main(){
    int T;
    cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m;
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) cin>>a[i][j];
        if(n==1&&m==1){
            cout<<"-1"<<endl;
            continue ;
        }else if(m==1){
            for(int i=0;i<n;i++) cout<<a[(i+1)%n][0]<<endl;
            continue ;
        }else{
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    cout<<a[i][(j+1)%m]<<' ';
                }
                cout<<endl;
            }
        }
    }

    return 0;
}