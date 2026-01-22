#include<bits/stdc++.h>

using namespace std;

const int N=20;

tuple<int,int,int> a[N];
bool cmp(tuple<int,int,int> a,tuple<int,int,int> b){
    return get<1>(a)+get<2>(a)>get<1>(b)+get<2>(b);
}

int main(){
    int n,h;
    cin>>n>>h;
    for(int i=1,x,y,z;i<=n;i++){
        cin>>x>>y>>z;
        a[i]=make_tuple(x,y,z);
    }

    long long ans=0;
    sort(a+1,a+n+1,cmp);
    for(int sta=0;sta<(1<<n);sta++){
        long long sum=0,H=0,res=1e18;
        for(int i=n;i;i--){
            if(!(sta>>i-1&1)) continue ;
            res=min(res,get<2>(a[i])-sum);
            sum+=get<1>(a[i]);
            H+=get<0>(a[i]);
        }
        if(res<0) continue ;
        if(H<h) continue ;
        ans=max(ans,res);
    }
    
    if(!ans) cout<<"Mark is too tall"<<endl;
    else cout<<ans<<endl;

    return 0;
}