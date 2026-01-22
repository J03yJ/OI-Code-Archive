#include<bits/stdc++.h>

using namespace std;

ifstream fin("magic.in");
ofstream fout("magic.out");
#define cin fin
#define cout fout

const int N=1e5+9;
const int inf=1e9+7;

int a[N],b[N],n,m;

int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=m;i++) cin>>b[i];
        sort(a+1,a+n+1);
        sort(b+1,b+m+1);
        b[m+1]=inf;
        int ans=0;
        for(int i=0;i<=m;i++){
            int l=upper_bound(a+1,a+n+1,b[i])-a;
            int r=lower_bound(a+1,a+n+1,b[i+1])-a-1;
            ans=max(ans,r-l+1);
        }
        cout<<ans<<endl;
    }

    return 0;
}