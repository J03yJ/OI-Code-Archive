#include<bits/stdc++.h>

using namespace std;

int main(){
    int n,lst=-1e9,c,ans=0;
    cin>>n>>c;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        if(x>=lst+c) ans++,lst=x;
    }
    cout<<ans<<endl;

    return 0;
}