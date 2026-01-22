#include<bits/stdc++.h>

using namespace std;

const int N=3e3+9;

char a[N][N];
int n;
char Get(int x,int y,int k){
    if(k>4) k%=4;
    if(!k) return a[x][y];
    else return Get(n-y+1,x,k-1);
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) cin>>a[i][j];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int k=min(min(i,n-i+1),min(j,n-j+1));
            cout<<Get(i,j,k);
        }
        cout<<endl;
    }

    return 0;
}