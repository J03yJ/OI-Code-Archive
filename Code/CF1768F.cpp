#include<bits/stdc++.h>

using namespace std;

const int N=4e5+9;
const long long inf=1e18;

int n;
long long f[N],a[N];

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    
    for(int i=1;i<=n;i++) f[i]=inf;f[1]=0;
    for(int i=1;i<=n;i++){
        int dis=n/a[i];
        for(int j=i-1;j>=i-dis&&j>=1;j--){
            f[i]=min(f[i],f[j]+a[i]*(i-j)*(i-j));
            if(a[j]<=a[i]) break ;
        }
        for(int j=i+1;j<=i+dis&&j<=n;j++){
            f[j]=min(f[j],f[i]+a[i]*(j-i)*(j-i));
            if(a[j]<=a[i]) break ;
        }
    }

    for(int i=1;i<=n;i++) cout<<f[i]<<' ';cout<<endl;

    return 0;
}