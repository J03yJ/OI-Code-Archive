#include<bits/stdc++.h>

using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
        int n,k;
        cin>>n>>k;
        n--;k--;
        cout<<(n+k-1)/k<<endl;
    }
}