#include<bits/stdc++.h>

using namespace std;

int main(){
    int r,b,g;
    string s;
    cin>>r>>g>>b>>s;
    if(s=="Red") cout<<min(g,b)<<endl;
    else if(s=="Blue") cout<<min(r,g)<<endl;
    else cout<<min(r,b)<<endl;
}