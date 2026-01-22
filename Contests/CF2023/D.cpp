#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

pair<double,int> a[N];
int n;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].first>>a[i].second;
        a[i].first/=100;
    }
    #define W(x) (x.first*x.second/(1-x.first))
    sort(a+1,a+n+1,[](pair<double,int> x,pair<double,int> y){
        return W(x)>W(y);
    });

    double ans=0;
    pair<double,int> res={1,0};
    for(int i=1;i<=n;i++){
        pair<double,int> cur={a[i].first*res.first,a[i].second+res.second};
        cout<<cur.first<<' '<<cur.second<<' '<<W(cur)<<' '<<W(res)<<endl;
        cout<<res.first<<' '<<res.second<<endl;
        if(W(cur)>W(res)) res=cur;
        ans=max(ans,cur.first*cur.second);
    }
    cout<<ans<<endl;

    return 0;
}