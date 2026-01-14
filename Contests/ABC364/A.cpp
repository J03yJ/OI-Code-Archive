#include<bits/stdc++.h>

using namespace std;

int main(){
    int n;
    cin>>n;
    string s,lst="";
    for(int i=1;i<=n;i++){
        cin>>s;
        if(s=="sweet"&&lst=="sweet"&&i!=n){
            cout<<"No"<<endl;
            return 0;
        }
        lst=s;
    }
    cout<<"Yes"<<endl;
    return 0;
}