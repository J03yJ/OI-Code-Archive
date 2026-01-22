#include<bits/stdc++.h>

using namespace std;

ifstream fin("tower.in");
ofstream fout("tower.out");
#define cin fin
#define cout fout

#define int long long
const int N=5e2+9;

int a[N];

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m;
        for(int i=1;i<=n;i++) cin>>a[i];

        vector<int> tmp;
        for(int i=1;i<=n;i++){
            int x=a[i];
            while(x){
                tmp.push_back(x);
                x/=2;
            }
        }
        tmp.push_back(0);
        sort(tmp.begin(),tmp.end());
        int cnt=unique(tmp.begin(),tmp.end())-tmp.begin();
        while(tmp.size()>cnt) tmp.pop_back();

        int ans=1e18;
        for(int x:tmp){
            int res=0;
            priority_queue<int> q;
            for(int i=1;i<=n;i++){
                int mn=abs(a[i]-x),now=a[i],cnt=0;
                do{
                    now/=2;
                    cnt++;
                    mn=min(mn,abs(x-now)+cnt);
                }while(now);
                q.push(mn);
                res+=mn;
            }
            for(int i=1;i<=m&&q.size();i++) res-=q.top(),q.pop();
            ans=min(ans,res);
        }
        cout<<ans<<endl;
    }
}