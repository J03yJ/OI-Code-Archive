#include<bits/stdc++.h>

using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
        int x,y;
        cin>>x>>y;
        int sum=0,i=1;
        while(sum+i<=x+y) sum+=i,i++;
        cout<<i-1<<endl;
    }
}