#include<bits/stdc++.h>

using namespace std;

const int N=2e6+9;
const int V=25;

int a[N];

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            for(int j=1,tmp;j<a[i];j++) cin>>tmp;
        }
        sort(a+1,a+n+1);
        int ans=0,lft=(1ll<<V)-1;
        for(int i=1;i<=n;i++){
            int res=0;
            for(int j=V-1;~j;j--){
                if(!(lft>>j&1)) continue ;
                if(res+(1<<j)<=a[i]) res+=(1<<j);
            }
            lft^=res;
            ans|=res;
        }
        cout<<ans<<endl;
    }
    return 0;
}