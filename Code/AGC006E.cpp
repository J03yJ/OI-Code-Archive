#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

int a[N][3],c[N],n;

struct fenw{
    int tr[N];
    void Add(int x,int k){
        while(x<=n){
            tr[x]+=k;
            x+=x&-x;
        }
    }
    int Ask(int x){
        int res=0;
        while(x){
            res+=tr[x];
            x&=x-1;
        }
        return res;
    }
    int Ask(int l,int r){
        return Ask(r)-Ask(l-1);
    }
}tr[2];

int main(){
    cin>>n;
    for(int k:{0,1,2}) for(int i=1;i<=n;i++) cin>>a[i][k];

    #define Err() return cout<<"No"<<endl,0
    #define NErr() return cout<<"Yes"<<endl,0
    #define Bel(x) ((x-1)/3+1)
    for(int i=1;i<=n;i++){
        for(int k:{0,1,2}) if(Bel(a[i][k])!=Bel(a[i][(k+1)%3])) Err();
        if(Bel(a[i][0])-i&1) Err();
        if(a[i][1]%3!=2) Err();
        if(a[i][0]%3) c[i]=Bel(a[i][0]);
        else c[i]=-Bel(a[i][0]);
    }

    int cnt[2]={0,0};
    for(int i=1;i<=n;i++) if(c[i]<0) cnt[i&1]++;
    for(int i=1;i<=n;i++){
        cnt[i&1^1]+=tr[i&1].Ask(abs(c[i])+1,n);
        tr[i&1].Add(abs(c[i]),1);
    }

    if((cnt[0]&1)||(cnt[1]&1)) Err();
    else NErr();
}