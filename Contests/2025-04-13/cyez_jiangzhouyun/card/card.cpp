#include<bits/stdc++.h>

using namespace std;

ifstream fin("card.in");
ofstream fout("card.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=2e3+9;

int p[N],q[N],r[N],vis[N],ip[N],iq[N],n;

signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>p[i],ip[p[i]]=i;
        for(int i=1;i<=n;i++) cin>>q[i],iq[q[i]]=i;

        if(n<=8){
            int ans=0;
            for(int i=1;i<=n;i++) r[i]=i;
            do{
                int res=0;
                for(int l=n;l>=1;l--){
                    for(int i=1;i<=n-l+1;i++){
                        for(int j=1;j<=n-l+1;j++){
                            bool flag=0;
                            for(int k=0;k<l;k++){
                                if(p[r[i+k]]!=q[r[j+k]]){
                                    flag=1;
                                    break ;
                                }
                            }
                            if(!flag){
                                res=l;
                                break ;
                            }
                        }
                        if(res) break ;
                    }
                    if(res) break ;
                }
                ans=max(ans,res);
            }while(next_permutation(r+1,r+n+1));
            cout<<ans<<endl;
        }else{
            int ans=0,cnt=0;
            vector<int> tmp;
            for(int i=1;i<=n;i++){
                if(vis[i]) continue ;
                int cur=i,len=0;
                while(!vis[cur]){
                    len++;
                    vis[cur]=1;
                    cur=ip[q[cur]];
                }
                if(len==1) cnt++;
                else ans=max(ans,len-1),tmp.push_back(len-1);
            }
            ans=max(ans,cnt);
            sort(tmp.begin(),tmp.end());
            for(int i=0;i<tmp.size();i++){
                int c=tmp.size()-i;
                int k=tmp.end()-upper_bound(tmp.begin(),tmp.end(),tmp[i]);
                ans=max(ans,c*tmp[i]+k);
            }
            cout<<ans<<endl;
            
            for(int i=1;i<=n;i++) vis[i]=0;
        }
    }

    return 0;
}