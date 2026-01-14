#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;

int a[N];

int main(){
    int n,ans=0;
    cin>>n;
    for(int i=1;i<=2*n;i++){
        int x;
        cin>>x;
        if(!a[x]) a[x]=i;
        else if(a[x]==i-2) ans++;
    }
    cout<<ans<<endl;
}