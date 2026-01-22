#include<bits/stdc++.h>

using namespace std;

ifstream fin("cycle.in");
ofstream fout("cycle.out");
#define cin fin
#define cout fout
#define endl '\n'

#define ssiz(x) (signed)x.size()
const int N=2e5+9;
const int lgN=2e1;

int to[N][lgN],tr[N<<2],n,m;
long long step[N][lgN];
void Modify(int x,int l,int r,int ql,int qr,int k){
    if(ql<=l&&r<=qr){
        tr[x]=max(tr[x],k);
        return ;
    }
    int mid=(l+r)>>1;
    if(ql<=mid) Modify(x<<1,l,mid,ql,qr,k);
    if(qr>mid) Modify(x<<1|1,mid+1,r,ql,qr,k);
}
void Work(int x,int l,int r,int mx){
    mx=max(mx,tr[x]),tr[x]=0;
    if(l==r){
        to[l][0]=(mx-1)%n+1;
        step[l][0]=mx-l;
        // cout<<l<<" : "<<to[l][0]<<' '<<step[l][0]<<endl;
        return ;
    }
    int mid=(l+r)>>1;
    Work(x<<1,l,mid,mx);
    Work(x<<1|1,mid+1,r,mx);
}
void InitST(){
    for(int k=1;k<lgN;k++){
        for(int i=1;i<=n;i++){
            to[i][k]=to[to[i][k-1]][k-1];
            step[i][k]=step[i][k-1]+step[to[i][k-1]][k-1];
        }
    }
}
int Query(int x){
    if(n==1) return 0;
    int stp=0,cnt=0;
    for(int k=lgN-1;~k;k--){
        if(stp+step[x][k]<n-1){
            stp+=step[x][k];
            cnt+=1<<k;
            x=to[x][k];
        }
    }
    stp+=step[x][0];
    cnt++;
    if(stp>=n-1) return cnt;
    else return -1;
}

int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1,lim;i<=m;i++){
            cin>>lim;
            vector<int> p(lim+1,0);
            for(int j=1;j<=lim;j++) cin>>p[j];
            p.push_back(p[1]+n);
            for(int j=1;j<=lim+1;j++) Modify(1,1,n,p[j-1]+1,min(p[j],n),p[j]);
        }
        Work(1,1,n,0);
        InitST();
        for(int i=1;i<=n;i++) cout<<Query(i%n+1)<<' ';cout<<endl;
    }

    return 0;
}