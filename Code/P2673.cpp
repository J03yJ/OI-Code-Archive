#include<bits/stdc++.h>

using namespace std;

int main(){
    int l,r;
    cin>>l>>r;
    int x=10;
    for(int i=1;i<=r;i++){
        x*=10;
        if(i>=l) cout<<x/89;
        x%=89;
    }
    cout<<endl;
}