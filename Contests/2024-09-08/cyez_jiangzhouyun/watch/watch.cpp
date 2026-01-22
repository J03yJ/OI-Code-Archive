#include<bits/stdc++.h>

using namespace std;

ifstream fin("watch.in");
ofstream fout("watch.out");
#define cin fin
#define cout fout

#define int long long
#define bint __int128

bint QPow(bint x,bint y){
    bint res=1;
    while(y){
        if(y&1) res=res*x;
        x=x*x;
        y>>=1;
    }
    return res;
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n,k;
        cin>>n>>k;
        map<bint,bool> mp;
        bool flag=0;
        for(bint i=1,lst=0;;i++){
            bint x=QPow(i,k);
            if(x-n>lst) break ;
            mp[x]=1;
            if(mp[x-n]){
                flag=1;
                break ;
            }
            lst=x;
        }
        cout<<flag<<endl;
    }

    return 0;
}