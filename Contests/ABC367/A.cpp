#include<bits/stdc++.h>

using namespace std;

int d[48];

int main(){
    int a,b,c;
    cin>>a>>b>>c;
    if(a>=b&&a<c) cout<<"No"<<endl;
    else if(b>c&&(a>=b||a<c)) cout<<"No"<<endl;
    else cout<<"Yes"<<endl;
    return 0;
}