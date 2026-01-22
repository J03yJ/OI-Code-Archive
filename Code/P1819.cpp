#include<bits/stdc++.h>

using namespace std;

const int N=3e2+9;

int f[N][N][N],to[3][N][26],buc[3][26],n;
char a[3][N];

int main(){
    cin>>n;
    for(int k:{0,1,2}){
        for(int i=1;i<=n;i++) cin>>a[k][i];
        for(int i=0;i<26;i++) buc[k][i]=n+1;
        for(int i=n;i>=1;i--){
            for(int j=0;j<26;j++) to[k][i][j]=buc[k][j];
            buc[k][a[k][i]-'a']=i;
        }
    }

    return 0;
}