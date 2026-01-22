#include<bits/stdc++.h>

using namespace std;

int main(){
    int tmp;
    cin>>tmp;
    string s;
    char a,b;
    cin>>a>>b;
    cin>>s;
    for(char &c:s) if(c!=a) c=b;
    cout<<s<<endl;;
}