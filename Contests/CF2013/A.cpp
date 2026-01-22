#include<bits/stdc++.h>

using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
        int n,x,y;
        cin>>n>>x>>y;
        cout<<max((n+x-1)/x,(n+y-1)/y)<<endl;
    }

    return 0;
}