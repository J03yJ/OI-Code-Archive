#include<bits/stdc++.h>

using namespace std;

ifstream fin("a.in");
ofstream fout("a.out");
#define cin fin
#define cout fout

const int N=1e6+9;
const int long long inf=1e18;
long long x[N],y[N];

int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        long long a,b;
        cin>>a>>b;
        x[i]=a-b;
        y[i]=a+b;
    }
    long long l=-1,r=4e9;
    while(l+1<r){
        long long mid=l+r>>1;
        long long xl=-inf,yl=-inf,xr=inf,yr=inf;
        for(int i=1;i<=n;i++){
            xl=max(xl,x[i]-mid);
            yl=max(yl,y[i]-mid);
            xr=min(xr,x[i]+mid);
            yr=min(yr,y[i]+mid);
        }
        if(xl>xr||yl>yr) l=mid;
        else r=mid;
    }
    cout<<r<<endl;
    return 0;
}