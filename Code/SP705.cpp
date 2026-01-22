#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

int rk[N],sa[N],tmp[N],cnt[N],h[N];
pair<int,int> a[N];

int main(){
    int T;
    cin>>T;
    while(T--){
        string s;
        cin>>s;
        int n=s.size();
        s=" "+s;
        
        int m=128;
        for(int i=1;i<=n;i++) a[i]={s[i],0};

        for(int i=1;i<=n;i++) cnt[a[i].first]++;
        for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
        for(int i=n;i>=1;i--) sa[cnt[a[i].first]--]=i;
        for(int i=1;i<=m;i++) cnt[i]=0;

        m=0;
        for(int i=1;i<=n;i++){
            if(a[sa[i]]!=a[sa[i-1]]) rk[sa[i]]=++m;
            else rk[sa[i]]=m;
        }

        for(int k=1;k<n;k<<=1){
            for(int i=1;i<=n;i++) a[i]={rk[i],rk[i+k]};

            for(int i=1;i<=n;i++) cnt[a[i].second]++;
            for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
            for(int i=n;i>=1;i--) tmp[cnt[a[i].second]--]=i;

            for(int i=1;i<=m;i++) cnt[i]=0;
            for(int i=1;i<=n;i++) cnt[a[i].first]++;
            for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
            for(int i=n;i>=1;i--) sa[cnt[a[tmp[i]].first]--]=tmp[i];
            for(int i=1;i<=m;i++) cnt[i]=0;

            m=0;
            for(int i=1;i<=n;i++){
                if(a[sa[i]]!=a[sa[i-1]]) rk[sa[i]]=++m;
                else rk[sa[i]]=m;
            }
        }

        for(int i=1,k=0;i<=n;i++){
            if(k) k--;
            while(s[i+k]==s[sa[rk[i]-1]+k]) k++;
            h[rk[i]]=k;
        }

        long long sum=0;
        for(int i=1;i<=n;i++) sum+=i-h[rk[i]];
        
        cout<<sum<<endl;
    }
    return 0;
}