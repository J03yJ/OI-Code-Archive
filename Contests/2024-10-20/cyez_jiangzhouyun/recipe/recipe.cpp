#include<bits/stdc++.h>

using namespace std;

ifstream fin("recipe.in");
ofstream fout("recipe.out");
#define cin fin
#define cout fout

#define int long long
const int N=2e6+9;

int a[N],p[N],b[N],n,k;
int Insert(int x){
    for(int i=k-1;~i;i--){
        if(!(x>>i&1)) continue ;
        if(!b[i]){
            b[i]=x;
            return 1;
        }
        x^=b[i];
    }
    return 0;
}

signed main(){
    cin>>k,n=1<<k;
    for(int i=1;i<n;i++) cin>>a[i],p[i]=i;
    sort(p+1,p+n,[](int x,int y){return a[x]<a[y];});

    int ans=0;
    for(int i=1;i<n;i++){
        if(Insert(p[i])) ans+=a[p[i]];
    }
    cout<<ans<<endl;
    
    return 0;
}