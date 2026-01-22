#include<bits/stdc++.h>

using namespace std;

const int N=5e5+9;
const int S=7.1e2+9;

int a[N],n,m;
int blk[N],L[N],R[N],B;
int F[S][S],A[S][S],buc[N];
vector<int> pos[N];int p[N];
int val[N];map<int,int> mp;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    #define endl '\n'
    
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i],val[i]=a[i];
    sort(val+1,val+n+1);
    int cnt=unique(val+1,val+n+1)-val-1;
    for(int i=1;i<=cnt;i++) mp[val[i]]=i;
    for(int i=1;i<=n;i++) a[i]=mp[a[i]];

    B=ceil(sqrt(n));
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    for(int i=1;i<=blk[n];i++) L[i]=B*(i-1)+1,R[i]=B*i;R[blk[n]]=n;
    for(int i=1;i<=n;i++) p[i]=pos[a[i]].size(),pos[a[i]].push_back(i);
    for(int i=1;i<=blk[n];i++){
        memset(buc,0,sizeof(buc));
        for(int j=i;j<=blk[n];j++){
            F[i][j]=F[i][j-1];
            for(int k=L[j];k<=R[j];k++) F[i][j]=max(F[i][j],++buc[a[k]]);
        }
    }

    memset(buc,0,sizeof(buc));
    int lst=0;
    while(m--){
        int l,r;
        cin>>l>>r;
        l^=lst;r^=lst;
        if(r<l) swap(l,r);
        int ans=0;
        if(blk[l]==blk[r]){
            for(int i=l;i<=r;i++){
                ans=max(ans,++buc[a[i]]);
            }
            for(int i=l;i<=r;i++) buc[a[i]]=0;
        }else{
            ans=F[blk[l]+1][blk[r]-1];
            for(int i=l;i<=R[blk[l]];i++){
                while(p[i]+ans<pos[a[i]].size()&&pos[a[i]][p[i]+ans]<=r) ans++;
            }
            for(int i=L[blk[r]];i<=r;i++){
                while(p[i]-ans>=0&&pos[a[i]][p[i]-ans]>=l) ans++;
            }
        }
        cout<<ans<<endl;
        lst=ans;
    }
    return 0;
}