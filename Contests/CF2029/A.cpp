#include<bits/stdc++.h>

using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
        int l,r,k;
        cin>>l>>r>>k;
        int tmp=r/k;
        cout<<max(tmp-l+1,0)<<endl;
    }
    
    return 0;
}