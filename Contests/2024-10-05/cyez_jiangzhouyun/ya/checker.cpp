#include<bits/stdc++.h>

using namespace std;

ifstream fin1("ya.in");
ifstream fin2("ya.out");
ofstream fout("result");

const int N=3e3+9;
int a[N][N],b[N];

int main(){
    int n,m;
    fin1>>n>>m;
    for(int i=1,u,v;i<=m;i++){
        fin1>>u>>v;
        a[u][v]=a[v][u]=1;
    }

    int k;
    fin2>>k;
    if(k<n/3){
        fout<<"Less than std."<<endl;
        return 0;
    }
    for(int i=1;i<=k;i++) fin2>>b[i];

    for(int i=1;i<=k;i++){
        for(int j=1;j<=k;j++){
            if(i==j) continue ;
            if(!a[b[i]][b[j]]){
                fout<<"Invalid answer."<<endl;
                return 0;
            }
        }
    }
    fout<<"Valid answer."<<endl;

    return 0;
}