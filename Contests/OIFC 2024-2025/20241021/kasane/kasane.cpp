#include<bits/stdc++.h>

using namespace std;

ifstream fin("kasane.in");
ofstream fout("kasane.out");
#define cin fin
#define cout fout
#define endl '\n'

#define ssiz(x) (signed)x.size()
const int N=1e6+9;

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n,k;
        cin>>n>>k;
        string s;
        cin>>s;

        if(k==1){
            cout<<1ll*n*(n+1)/2<<endl;
            continue ;
        }

        vector<int> d(n);
        for(int i=0,l=0,r=-1;i<n;i++){
            int k=i>r?0:min(r-i+1,d[r+l-i+1]);
            while(i-k-1>=0&&i+k<n&&s[i-k-1]==s[i+k]) k++;
            d[i]=k--;
            if(i+k>r) l=i-k-1,r=i+k;
        }
        d.erase(d.begin());
        d.push_back(0);
        if(k==2){
            long long ans=0;
            for(int x:d) ans+=x;
            cout<<ans<<endl;
            continue ;
        }
        
        vector<int> tr(n<<1);
        auto Add=[&tr](int x,int k){
            while(x<ssiz(tr)){
                tr[x]+=k;
                x+=x&-x;
            }
        };
        auto Ask=[&tr](int x){
            int sum=0;
            while(x){
                sum+=tr[x];
                x&=x-1;
            }
            return sum;
        };
        auto RAsk=[&tr,&Ask](int k){
            return Ask(ssiz(tr)-1)-Ask(k-1);
        };
        long long ans=0,a=(k+1)/2-1,b=k/2;
        vector<vector<pair<int,int>>> q(n);
        vector<int> res(n);
        for(int i=0;i<n;i++){
            q[i].push_back({i,1});
            int pos=max((b*i-d[i]+b-1)/b,0ll);
            if(pos) q[pos].push_back({i,-1});
        }
        for(int i=0;i<n;i++){
            for(auto p:q[i]){
                ans+=p.second*RAsk(p.first+1);
                res[p.first]+=p.second*RAsk(p.first+1);
                // cout<<i<<' '<<p.first<<' '<<p.second<<' '<<RAsk(p.first+1)<<endl;
            }
            Add(d[i]/a+i+1,1);
            // cout<<" : "<<d[i]/a+i<<' '<<d[i]/a<<' '<<i<<endl;
        }
        // for(int x:res) cout<<x<<' ';cout<<endl;
        // for(int x:d) cout<<x<<' ';cout<<endl;
        cout<<ans<<endl;
    }

    return 0;
}