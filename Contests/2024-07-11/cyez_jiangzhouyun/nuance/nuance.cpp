#include<bits/stdc++.h>
using namespace std;

ifstream fin("nuance.in");
ofstream fout("nuance.out");
#define cin fin
#define cout fout

#define int long long
const int N=2e5+9;
const int B=13331;
const int p=1e9+9;

int a[N],n,m;
int qpow(int x,int y){
    int m=1;
    while(y){
        if(y&1) m=m*x%p;
        x=x*x%p;
        y>>=1;
    }
    return m;
}

namespace SGT{
    
}
namespace BIT{
    int tr[N];
    void add(int x,int k){
        while(x<=n){
            tr[x]+=k;
            x+=x&-x;
        }
    }
    int ask(int x){
        int sum=0;
        while(x){
            sum+=tr[x];
            x&=x-1;
        }
        return sum;
    }
    int ask(int l,int r){
        if(l>r) return 0;
        else return ask(r)-ask(l-1);
    }
    void clear(){
        for(int i=1;i<=n;i++) tr[i]=0;
    }
}

signed main(){

}