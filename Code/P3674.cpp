#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;
const int V=1e5;

int a[N],blk[N],n,m;
int ql[N],qr[N],qk[N],op[N],p[N],cnt[N];
bitset<N> pos,neg,ans;
bool cmp(int x,int y){
    if(blk[ql[x]]!=blk[ql[y]]) return blk[ql[x]]<blk[ql[y]];
    else return qr[x]<qr[y];
}
inline void upd(int k){
    if(cnt[k]) pos[k]=neg[V-k]=1;
    else pos[k]=neg[V-k]=0;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++) cin>>op[i]>>ql[i]>>qr[i]>>qk[i],p[i]=i;

    int B=sqrt(n);
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    sort(p+1,p+m+1,cmp);

    for(int i=1,l=1,r=0;i<=m;i++){
        while(r<qr[p[i]]) cnt[a[++r]]++,upd(a[r]);
        while(l>ql[p[i]]) cnt[a[--l]]++,upd(a[l]);
        while(r>qr[p[i]]) cnt[a[r]]--,upd(a[r--]);
        while(l<ql[p[i]]) cnt[a[l]]--,upd(a[l++]);
        if(op[p[i]]==1) ans[p[i]]=(pos<<qk[p[i]]&pos).any();
        else if(op[p[i]]==2) ans[p[i]]=(neg>>V-qk[p[i]]&pos).any();
        else{
            for(int j=1;j*j<=qk[p[i]];j++){
                if(qk[p[i]]%j) continue ;
                if(pos[j]&&pos[qk[p[i]]/j]){
                    ans[p[i]]=1;
                    break ;
                }
            }
        }
    }

    for(int i=1;i<=m;i++){
        if(ans[i]) cout<<"hana"<<endl;
        else cout<<"bi"<<endl;
    }

    return 0;
}