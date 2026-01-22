#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=1e5+9;
const int lgN=2e1;

struct SufArr{
    int sa[N],lsa[N],rk[N],lrk[N],h[N],cnt[N],n;
    string s;
    inline void InitH(){
        memset(rk,0,sizeof rk);
        memset(lrk,0,sizeof lrk);

        n=s.size();
        s=" "+s;
        
        for(int i=1;i<=n;i++) cnt[s[i]]++;
        for(int i=1;i<128;i++) cnt[i]+=cnt[i-1];
        for(int i=n;i>=1;i--) sa[cnt[s[i]]--]=i;
        for(int i=0;i<128;i++) cnt[i]=0;
        
        int tot=0;
        for(int i=1;i<=n;i++){
            if(s[sa[i]]!=s[sa[i-1]]) tot++;
            rk[sa[i]]=tot;
        }

        for(int k=1;k<=n&&tot<n;k<<=1){
            for(int i=1;i<=n;i++) cnt[rk[sa[i]+k]]++;
            for(int i=1;i<=tot;i++) cnt[i]+=cnt[i-1];
            for(int i=n;i>=1;i--) lsa[cnt[rk[sa[i]+k]]--]=sa[i];
            for(int i=0;i<=tot;i++) cnt[i]=0;

            for(int i=1;i<=n;i++) cnt[rk[lsa[i]]]++;
            for(int i=1;i<=tot;i++) cnt[i]+=cnt[i-1];
            for(int i=n;i>=1;i--) sa[cnt[rk[lsa[i]]]--]=lsa[i];
            for(int i=0;i<=tot;i++) cnt[i]=0;

            tot=0;
            for(int i=1;i<=n;i++) lrk[i]=rk[i];
            for(int i=1;i<=n;i++){
                if(lrk[sa[i]]!=lrk[sa[i-1]]||lrk[sa[i]+k]!=lrk[sa[i-1]+k]) tot++;
                rk[sa[i]]=tot;
            }
        }

        for(int i=1,k=0;i<=n;i++){
            if(k) k--;
            while(i+k<=n&&s[sa[rk[i]]+k]==s[sa[rk[i]-1]+k]) k++;
            h[rk[i]]=k;
        }
    }
    inline void Set(string str){s=str,InitH();}

    int mn[N][lgN],lg[N];
    inline void InitLCP(){
        for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
        for(int i=1;i<=n;i++) mn[i][0]=h[i];
        for(int k=1;k<=lg[n];k++){
            for(int i=1;i<=n-(1<<k)+1;i++) mn[i][k]=min(mn[i][k-1],mn[i+(1<<k-1)][k-1]);
        }
    }
    inline int Query(int l,int r){
        l=rk[l],r=rk[r];
        if(l>r) swap(l,r);
        if(++l>r) return n-r+1;
        int k=lg[r-l+1];
        return min(mn[l][k],mn[r-(1<<k)+1][k]);
    }
    inline int RQuery(int l,int r){return Query(n-r+1,n-l+1);}
}arr,brr;
int f[N],g[N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    int T;
    cin>>T;
    while(T--){
        string s;
        cin>>s;
        int n=s.size();
        arr.Set(string(s.begin(),s.end()));
        brr.Set(string(s.rbegin(),s.rend()));
        arr.InitLCP();
        brr.InitLCP();

        for(int len=1;len<=(n>>1);len++){
            for(int i=len,j=len<<1;j<=n;i+=len,j+=len){
                int lcp=min(len,arr.Query(i,j));
                int lcs=min(len,brr.RQuery(i,j));
                if(lcp+lcs<=len) continue ;
                int lpos=i-lcs+1;
                int rpos=j+lcp-1;
                f[lpos+(len<<1)-1]++,f[rpos+1]--;
                g[lpos]++,g[rpos-(len<<1)+1+1]--;
            }
        }
        for(int i=1;i<=n;i++) f[i]+=f[i-1],g[i]+=g[i-1];

        ll ans=0;
        for(int i=1;i<n;i++) ans+=1ll*f[i]*g[i+1];
        cout<<ans<<endl;

        for(int i=1;i<=n+1;i++) f[i]=g[i]=0;
    }

    return 0;
}