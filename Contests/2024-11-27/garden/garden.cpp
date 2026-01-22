#include<bits/stdc++.h>

using namespace std;

ifstream fin("garden.in");
ofstream fout("garden.out");
#define cin fin
#define cout fout

const int N=1e2+9;

short ans[N][N][N][N],f[N][N];
int a[N],b[N],n,m,k,tot;
char c[N][N];

int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) cin>>c[i][j],c[i][j]-='0';
    }
    map<pair<int,int>,int> mp;
    for(int i=1;i<=k;i++){
        cin>>a[i]>>b[i];
        if(mp[{a[i],b[i]}]) i--,k--;
        else mp[{a[i],b[i]}]=1;
    }

    int tmp=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int p=1;p<=k;p++){
                if(i+a[p]>n||i+a[p]<1) continue ;
                if(j+b[p]>m||j+b[p]<1) continue ;
                f[i][j]+=c[i+a[p]][j+b[p]];
            }
            for(int p=1;p<=k;p++){
                if(i-a[p]>n||i-a[p]<1) continue ;
                if(j-b[p]>m||j-b[p]<1) continue ;
                for(int q=1;q<=k;q++){
                    if(i-a[q]>n||i-a[q]<1) continue ;
                    if(j-b[q]>m||j-b[q]<1) continue ;
                    ans[i-a[p]][j-b[p]][i-a[q]][j-b[q]]-=c[i][j];
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int p=1;p<=n;p++){
                for(int q=1;q<=n;q++){
                    tmp=max(tmp,f[i][j]+f[p][q]+ans[i][j][p][q]);
                }
            }
        }
    }
    cout<<tmp<<endl;

    return 0;
}