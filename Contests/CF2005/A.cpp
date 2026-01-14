#include<bits/stdc++.h>

using namespace std;

int main(){
    int T;
    cin>>T;
    char a[6]={'0','a','e','i','o','u'};
    while(T--){
        int x;
        cin>>x;
        for(int i=1;i<=5;i++){
            int cnt=x/5;
            if(i<=x%5) cnt++;
            for(int j=1;j<=cnt;j++) cout<<a[i];
        }
        cout<<endl;
    }
}