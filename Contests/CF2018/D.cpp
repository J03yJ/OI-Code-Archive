#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;
const int inf=1e9;

int a[N],p[N],n,mx;

struct Node{
    int l,r;
    int dat[2][2][2];
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat

int ls[3]={0,0,1},rs[3]={0,1,0};
inline void ChMax(int &x,int y){
    if(y>x) x=y;
}
inline void Reset(int x){
    for(int i:{0,1}) for(int j:{0,1}) for(int k:{0,1}) dat(x)[i][j][k]=-inf;
}
void PushUp(int x){
    Reset(x);
    for(int i:{0,1}){
        for(int j:{0,1}){
            for(int k:{0,1,2}){
                ChMax(dat(x)[0][i][j],max(dat(x<<1)[0][i][ls[k]],0)+
                                      max(dat(x<<1|1)[0][rs[k]][j],0));
            }
        }
    }
    for(int i:{0,1}){
        for(int j:{0,1}){
            for(int k:{0,1,2}){
                ChMax(dat(x)[1][i][j],dat(x<<1)[1][i][ls[k]]+
                                      max(dat(x<<1|1)[0][rs[k]][j],0));
                ChMax(dat(x)[1][i][j],max(dat(x<<1)[0][i][ls[k]],0)+
                                      dat(x<<1|1)[1][rs[k]][j]);
                ChMax(dat(x)[1][i][j],dat(x<<1)[1][i][ls[k]]+
                                      dat(x<<1|1)[1][rs[k]][j]);
            }
        }
    }
}
void Build(int x,int l,int r){
    l(x)=l,r(x)=r,Reset(x);
    if(l(x)==r(x)) return ;
    int mid=l(x)+r(x)>>1;
    Build(x<<1,l,mid);
    Build(x<<1|1,mid+1,r);
}
void Modify(int x,int pos){
    if(l(x)==r(x)){
        dat(x)[a[pos]==mx][1][1]=1;
        return ;
    }
    int mid=l(x)+r(x)>>1;
    if(pos<=mid) Modify(x<<1,pos);
    else Modify(x<<1|1,pos);
    PushUp(x);
    // cout<<l(x)<<' '<<r(x)<<" : ";
    // for(int i:{0,1}) for(int j:{0,1}) for(int k:{0,1}) cout<<dat(x)[i][j][k]<<' ';
    // cout<<endl;
}
int Query(){
    int ans=0;
    for(int i:{0,1}){
        for(int j:{0,1}) ans=max(ans,dat(1)[1][i][j]);
    }
    return ans;
}

int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        iota(p+1,p+n+1,1);

        sort(p+1,p+n+1,[](int x,int y){return a[x]>a[y];});
        mx=a[p[1]];
        int ans=0;
        Build(1,1,n);
        for(int i=1;i<=n;i++){
            Modify(1,p[i]);
            ans=max(ans,a[p[i]]+mx+Query());
            // cout<<a[p[i]]<<' '<<mx<<' '<<Query()<<' '<<p[i]<<endl;
        }

        cout<<ans<<endl;
    }

    return 0;
}