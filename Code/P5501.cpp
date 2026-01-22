#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=5e5+9;
const int V=1e5;

int a[N],blk[N],n,m;
int ql[N],qr[N],p[N],ans[N];
bool Cmp(int x,int y){
    if(blk[ql[x]]!=blk[ql[y]]) return blk[ql[x]]<blk[ql[y]];
    else return qr[x]<qr[y];
}

vector<tuple<signed,signed,signed,char,char>> v[N];
int cnt[N],cntt[N],sum[N],sumt[N],vblk[N],VB;
void InitVB(){
    VB=sqrt(V);
    for(int i=1;i<=V;i++) blk[i]=(i-1)/VB+1;
}
void Add(int x,int val){
    for(int i=x;blk[i]==blk[x];i++) cnt[i]+=val;
    for(int i=blk[x]+1;i<=blk[V];i++) cntt[i]+=val;
    for(int i=x;blk[i]==blk[x];i++) sum[i]+=val*x;
    for(int i=blk[x]+1;i<=blk[V];i++) sumt[i]+=val*x;
}
int AskC(int l,int r){return cnt[r]+cntt[blk[r]]-cnt[l-1]-cntt[blk[l-1]];}
int AskS(int l,int r){return sum[r]+sumt[blk[r]]-sum[l-1]-sumt[blk[l-1]];}
void Clear(){
    memset(cnt,0,sizeof cnt);
    memset(cntt,0,sizeof cnt);
    memset(sum,0,sizeof sum);
    memset(sumt,0,sizeof sumt);
}
int prer[N],prel[N];

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>ql[i]>>qr[i],p[i]=i;

    int B=sqrt(n);
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    sort(p+1,p+m+1,Cmp);

    InitVB();
    for(int i=1;i<=n;i++){
        Add(a[i],1);
        prer[i]=AskS(a[i]+1,V)+(AskC(1,a[i]-1)+1)*a[i];
        prer[i]+=prer[i-1];
    }
    Clear();
    for(int i=1;i<=n;i++){
        Add(a[i],1);
        prel[i]=AskS(a[i]+1,V)+AskC(1,a[i]-1)*a[i];
        prel[i]+=prel[i-1];
    }
    Clear();

    for(int i=1,l=1,r=0;i<=m;i++){
        if(r<qr[p[i]]){
            ans[p[i]]+=prer[qr[p[i]]]-prer[r];
            v[l-1].push_back(make_tuple(r+1,qr[p[i]],p[i],-1,0));
            r=qr[p[i]];
        }
        if(l>ql[p[i]]){
            ans[p[i]]-=prel[l-1]-prel[ql[p[i]]-1];
            v[r].push_back(make_tuple(ql[p[i]],l-1,p[i],1,1));
            l=ql[p[i]];
        }
        if(r>qr[p[i]]){
            ans[p[i]]+=prer[qr[p[i]]]-prer[r];
            v[l-1].push_back(make_tuple(qr[p[i]]+1,r,p[i],1,0));
            r=qr[p[i]];
        }
        if(l<ql[p[i]]){
            ans[p[i]]-=prel[l-1]-prel[ql[p[i]]-1];
            v[r].push_back(make_tuple(l,ql[p[i]]-1,p[i],-1,1));
            l=ql[p[i]];
        }
        // if(r<qr[p[i]]){
        //     ans[p[i]]+=prer[qr[p[i]]]-prer[r];
        //     while(r<qr[p[i]]) r++,v[l-1].push_back(make_tuple(r,r,p[i],-1,0));
        // }
        // if(l>ql[p[i]]){
        //     ans[p[i]]-=prel[l-1]-prel[ql[p[i]]-1];
        //     while(l>ql[p[i]]) l--,v[r].push_back(make_tuple(l,l,p[i],1,1));
        // }
        // if(r>qr[p[i]]){
        //     ans[p[i]]+=prer[qr[p[i]]]-prer[r];
        //     while(r>qr[p[i]]) v[l-1].push_back(make_tuple(r,r,p[i],1,0)),r--;
        // }
        // if(l<ql[p[i]]){
        //     ans[p[i]]-=prel[l-1]-prel[ql[p[i]]-1];
        //     while(l<ql[p[i]]) v[r].push_back(make_tuple(l,l,p[i],-1,1)),l++;
        // }
    }

    for(int i=1;i<=n;i++){
        Add(a[i],1);
        for(tuple<int,int,int,int,int> t:v[i]){
            for(int i=get<0>(t);i<=get<1>(t);i++){
                int pos=a[i];
                int res=AskS(pos+1,V)+(AskC(1,pos-1)+get<4>(t))*pos;
                ans[get<2>(t)]+=get<3>(t)*res;
            }
        }
    }
    for(int i=1;i<=m;i++) ans[p[i]]+=ans[p[i-1]];
    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;

    return 0;
}