#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e3+9;

int _a[N<<1],*a=_a+N,n,m,trg;
int _use[N<<1],*use=_use+N;
int _f[N*N<<1],*f=_f+N*N;
inline void ChMax(int &x,int y){
    if(y>x) x=y;
}
void Insert(int w,int flag,int c){
    if(w>0){
        for(int s=1;c>0;c-=s,s<<=1){
            int k=min(s,c);
            for(int i=m;i>=-m+k*w;i--) ChMax(f[i],f[i-k*w]+k*flag);
        }
    }else{
        for(int s=1;c>0;c-=s,s<<=1){
            int k=min(s,c);
            for(int i=-m;i<=m+k*w;i++) ChMax(f[i],f[i-k*w]+k*flag);
        }
    }
}

signed main(){
    cin>>n>>trg;
    for(int i=-n;i<=n;i++) cin>>a[i];
    m=n*n;

    int lm=0,rm=0;
    for(int i=1;i<=n;i++) rm+=a[i]*i;
    for(int i=-1;i>=-n;i--) lm+=a[i]*i;
    if(trg<lm||trg>rm){
        cout<<"impossible"<<endl;
        return 0;
    }

    int cur=0;
    for(int i=-n;i<=n;i++){
        use[i]=a[i];
        cur+=use[i]*i;
    }
    if(cur>trg){
        for(int i=n;i>=1;i--){
            int tmp=cur-trg;
            use[i]-=min(a[i],tmp/i);
            cur-=i*(a[i]-use[i]);
        }
    }else{
        for(int i=-n;i<=-1;i++){
            int tmp=cur-trg;
            use[i]-=min(a[i],tmp/i);
            cur-=i*(a[i]-use[i]);
        }
    }

    memset(_f,-0x3f,sizeof(_f));f[cur-trg]=0;
    for(int i=-n;i<=n;i++) f[cur-trg]+=use[i];
    for(int i=-n;i<=n;i++){
        if(!i) continue ;
        if(use[i]) Insert(-i,-1,min(use[i],m));
        if(a[i]-use[i]) Insert(i,1,min(a[i]-use[i],m));
    }
    if(f[0]<0) cout<<"impossible"<<endl;
    else cout<<f[0]<<endl;

    return 0;
}