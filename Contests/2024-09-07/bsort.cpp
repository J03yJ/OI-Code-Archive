#include<bits/stdc++.h>

using namespace std;

ifstream fin("bsort.in");
ofstream fout("bsort.out");
#define cin fin
#define cout fout

const int N=2e5+9;

int a[N],n,k;
int tr[N];
void Add(int x,int k){
    while(x<=n){
        tr[x]+=k;
        x+=x&-x;
    }
}
int Ask(int x){
    int sum=0;
    while(x){
        sum+=tr[x];
        x&=x-1;
    }
    return sum;
}
int Ask(int l,int r){
    return Ask(r)-Ask(l-1);
}
int c[N];

int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];

    long long ans=0;
    for(int i=1;i<=n;i++){
        int x=Ask(a[i]+1,n);
        int p=(x+k-2)/(k-1);
        if(i<=p*(k-1)+1){
            if(!c[p]) c[p]=1;
            else p--;
        }
        ans+=p;
        Add(a[i],1);
    }
    cout<<ans<<endl;

    return 0;
}