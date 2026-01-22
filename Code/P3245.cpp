#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;

int a[N],blk[N];
int ql[N],qr[N],per[N],cnt[N];
long long ans[N];
bool cmp(int x,int y){
    if(blk[ql[x]]!=blk[ql[y]]) return blk[ql[x]]<blk[ql[y]];
    else return qr[x]<qr[y];
}

signed main(){
    int p,m;string s;
    cin>>p>>s>>m;
    int n=s.size();
    for(int i=1;i<=m;i++) cin>>ql[i]>>qr[i],per[i]=i;

    if(p==2||p==5){
        for(int i=1;i<=n;i++){
            cnt[i]=cnt[i-1]+((s[i-1]-'0')%p==0);
            ans[i]=ans[i-1]+((s[i-1]-'0')%p==0)*i;
        }
        for(int i=1;i<=m;i++) cout<<ans[qr[i]]-ans[ql[i]-1]-(cnt[qr[i]]-cnt[ql[i]-1])*(ql[i]-1)<<endl;

        return 0;
    }

    for(int i=n,j=1;i>=1;i--,j=j*10%p){
        a[i]=(a[i+1]+(s[i-1]-'0')*j%p)%p;
    }
    int B=sqrt(n);
    for(int i=1;i<=n+1;i++) blk[i]=(i-1)/B+1;
    sort(per+1,per+m+1,cmp);

    map<int,int> mp;
    for(int i=1,cnt=0;i<=n+1;i++){
        if(!mp[a[i]]) mp[a[i]]=++cnt;
        a[i]=mp[a[i]];
    }

    for(int i=1,l=1,r=0,res=0;i<=m;i++){
        // cout<<ql[per[i]]<<' '<<qr[per[i]]<<endl;
        qr[per[i]]++;
        while(r<qr[per[i]]) res+=cnt[a[++r]],cnt[a[r]]++;
        while(l>ql[per[i]]) res+=cnt[a[--l]],cnt[a[l]]++;
        while(r>qr[per[i]]) cnt[a[r]]--,res-=cnt[a[r--]];
        while(l<ql[per[i]]) cnt[a[l]]--,res-=cnt[a[l++]];
        ans[per[i]]=res;
    }

    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;

    return 0;
}