#include<bits/stdc++.h>

using namespace std;

ifstream fin1("football.in");
ifstream fin2("football.out");
ofstream fout("check.out");
#define endl '\n'

const int N=1.5e3+9;

int vis[N],id[N],t[N],n,k;
bitset<N> a[N],b[N],x,y;

signed main(){
    fin1>>n>>k;
    for(int i=1;i<=n;i++){
        string s;
        fin1>>s;
        for(int j=0;j<k;j++) if(s[j]=='1') a[i].set(j,1);
    }
    int c1=0,c2=0;
    for(int i=1;i<=n;i++){
        char c;
        fin2>>c;
        if(c=='1') x^=a[i],c1++;
        else if(c=='2') y^=a[i],c2++;
    }
    if(x!=y) fout<<"!!!"<<endl;
    if(c1!=c2) fout<<"???"<<endl;
    for(int i=0;i<k;i++) fout<<x[i];fout<<endl;
    for(int i=0;i<k;i++) fout<<y[i];fout<<endl;
    
    return 0;
}