#include<bits/stdc++.h>

using namespace std;

int n,q;
int Clkw(int a,int b){return (b+n-a)%n;}
bool Check(int a,int b,int c){return Clkw(a,b)+Clkw(b,c)==Clkw(a,c);}
int F(int st,int ed,int b){
    if(Check(st,b,ed)) return n-Clkw(st,ed);
    else return Clkw(st,ed);
}
void Ins(int &x,int k){
    if(!x) x=k;
    else x=min(x,k);
}

int main(){
    cin>>n>>q;
    map<pair<int,int>,int> f;
    f[{1,2}]=1;
    while(q--){
        char op;int x;
        cin>>op>>x;
        // if(op=='R') ans+=F(r,x,l),r=x;
        // else ans+=F(l,x,r),l=x;
        map<pair<int,int>,int> g;
        for(auto p:f){
            int l=p.first.first,r=p.first.second,w=p.second;
            if(op=='L'){
                if(x!=r){
                    Ins(g[{x,r}],w+F(l,x,r));
                }
                if(Check(l,r,x)||r==x){
                    int pos=x%n+1,val=Clkw(l,x)+Clkw(r,pos)+w;
                    Ins(g[{x,pos}],val);
                }
                if(!Check(l,r,x)||r==x){
                    int pos=x==1?n:x-1,val=n-Clkw(l,x)+n-Clkw(r,pos)+w;
                    Ins(g[{x,pos}],val);
                }
            }else{
                if(x!=l){
                    Ins(g[{l,x}],w+F(r,x,l));
                }
                if(Check(r,l,x)||l==x){
                    int pos=x%n+1,val=Clkw(r,x)+Clkw(l,pos)+w;
                    Ins(g[{pos,x}],val);
                }
                if(!Check(r,l,x)||l==x){
                    int pos=x==1?n:x-1,val=n-Clkw(r,x)+n-Clkw(l,pos)+w;
                    Ins(g[{pos,x}],val);
                }
            }
        }
        f=g;
        // for(auto p:f){
        //     cout<<p.first.first<<' '<<p.first.second<<' '<<p.second<<endl;
        // }
        // cout<<endl;
    }
    int ans=1e9;
    for(auto p:f) ans=min(ans,p.second);
    cout<<ans-1<<endl;

    return 0;
}