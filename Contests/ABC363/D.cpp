#include<bits/stdc++.h>

using namespace std;

#define int long long

signed main(){
    long long x;
    cin>>x;
    if(x==1){
        cout<<0<<endl;
        return 0;
    }
    x--;
    for(int i=9,j=1;;i=10*i,j*=10){
        if(x<=i){
            x+=j-1;
            string s="";
            while(x){
                char ch=x%10+'0';
                s+=ch;
                x/=10;
            }
            for(int i=s.size()-1;i;i--) cout<<s[i];
            cout<<s<<endl;
            return 0;
        }else x-=i;
        if(x<=i){
            x+=j-1;
            string s="";
            while(x){
                char ch=x%10+'0';
                s+=ch;
                x/=10;
            }
            for(int i=s.size()-1;~i;i--) cout<<s[i];
            cout<<s<<endl;
            return 0;
        }else x-=i;
    }
}