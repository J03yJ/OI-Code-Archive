#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;
const int V=1e5;
const int SQV=3.3e2+9;

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
vector<tuple<int,int,int>> v[SQV+9];
int lst[N],res[N];

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
        else if(op[p[i]]==3){
            for(int j=1;j*j<=qk[p[i]];j++){
                if(qk[p[i]]%j) continue ;
                if(pos[j]&&pos[qk[p[i]]/j]){
                    ans[p[i]]=1;
                    break ;
                }
            }
        }else{
            if(qk[p[i]]>SQV){
                for(int j=1;j*qk[p[i]]<=V;j++){
                    if(pos[j]&&pos[j*qk[p[i]]]){
                        ans[p[i]]=1;
                        break ;
                    }
                }
            }else v[qk[p[i]]].push_back(make_tuple(p[i],ql[p[i]],qr[p[i]]));
        }
    }
    for(int k=1;k<=SQV;k++){
        for(int i=0;i<=V;i++) lst[i]=res[i]=0;
        for(int i=1;i<=n;i++){
            lst[a[i]]=i;
            if(a[i]%k) res[i]=a[i]*k>V?0:lst[a[i]*k];
            else res[i]=max(a[i]*k>V?0:lst[a[i]*k],lst[a[i]/k]);
            res[i]=max(res[i],res[i-1]);
        }
        for(tuple<int,int,int> t:v[k]){
            int l=get<1>(t),r=get<2>(t),i=get<0>(t);
            ans[i]=l<=res[r];
        }
    }

    for(int i=1;i<=m;i++){
        if(ans[i]) cout<<"yuno"<<endl;
        else cout<<"yumi"<<endl;
    }

    return 0;
}