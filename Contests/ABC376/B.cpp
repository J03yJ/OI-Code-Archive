#include<bits/stdc++.h>

using namespace std;

int n,q;
int Clkw(int a,int b){return (b+n-a)%n;}
bool Check(int a,int b,int c){return Clkw(a,b)+Clkw(b,c)==Clkw(a,c);}
int F(int st,int ed,int b){
    if(Check(st,b,ed)) return n-Clkw(st,ed);
    else return Clkw(st,ed);
}

int main(){
    cin>>n>>q;
    int l=1,r=2,ans=0;
    while(q--){
        char op;int x;
        cin>>op>>x;
        if(op=='R') ans+=F(r,x,l),r=x;
        else ans+=F(l,x,r),l=x;
    }
    cout<<ans<<endl;
}