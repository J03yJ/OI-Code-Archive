#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

long long a[N],n;

int main(){
    while(cin>>n,n){
        for(int i=1;i<=n;i++) cin>>a[i];

        if(n==1) cout<<a[1]<<endl;
        else{
            long long ans=0,sum=0;
            for(int i=1;i<=n;i++) ans=max(ans,a[i]+a[i%n+1]),sum+=a[i];
            cout<<max(ans,(long long)ceil(double(sum)/(n/2)))<<endl;
        }
    }
    
    return 0;
}