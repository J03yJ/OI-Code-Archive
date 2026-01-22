#include<bits/stdc++.h>

using namespace std;

#define int long long
#define one __int128(1)
using frac=pair<int,int>;

frac Find(frac p,frac q){
    if(one*q.first*p.second<one*p.first*q.second) swap(p,q);
    if(p.first<p.second&&q.first>q.second) return {1,1};
    else{
        int tmp=p.first/p.second;
        frac ans=tmp?Find({p.first-tmp*p.second,p.second},{q.first-tmp*q.second,q.second})
                    :Find({p.second,p.first},{q.second,q.first});
        if(!tmp) swap(ans.first,ans.second);
        else ans.first+=ans.second*tmp;
        return ans;
    }
}

signed main(){
    int a,b,c,d;
    while(cin>>a>>b>>c>>d){
        frac ans=Find({a,b},{c,d});
        cout<<ans.first<<'/'<<ans.second<<endl;
    }
    return 0;
}