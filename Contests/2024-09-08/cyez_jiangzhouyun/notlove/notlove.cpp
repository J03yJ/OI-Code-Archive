#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#include<bits/stdc++.h>

using namespace std;

ifstream fin("notlove.in");
ofstream fout("notlove.out");
#define cin fin
#define cout fout

const int N=1e6+9;
const int inf=1e9+7ll;

int val[N],cnt[N],a[N],n,tot;
struct Data{
    int dlt,lim;
    Data(){dlt=0,lim=inf;}
    Data(int d,int l){dlt=d;lim=l;}
    Data operator +(Data x){
        return Data(dlt+x.dlt,min(x.lim,lim+x.dlt));
    }
};
namespace SgT{
    struct Node{
        int l,r;
        Data dat;
    }tr[N<<1];
    #define l(x) tr[x].l
    #define r(x) tr[x].r
    #define dat(x) tr[x].dat
    void Build(int x,int l,int r){
        l(x)=l;r(x)=r;
        dat(x)=Data(0,inf);
        if(l(x)==r(x)) return ;
        int mid=l(x)+r(x)>>1;
        Build(x<<1,l,mid);
        Build(x<<1|1,mid+1,r);
    }
    void Modify(int x,int pos,int k){
        if(l(x)==r(x)){
            dat(x).lim=k;
            dat(x).dlt=1;
            return ;
        }
        int mid=l(x)+r(x)>>1;
        if(pos<=mid) Modify(x<<1,pos,k);
        else Modify(x<<1|1,pos,k);
        dat(x)=dat(x<<1)+dat(x<<1|1);
    }
    Data Query(int x,int l,int r){
        if(l>r) return Data(0,inf);
        if(l<=l(x)&&r(x)<=r) return dat(x);
        int mid=l(x)+r(x)>>1;
        if(l<=mid&&r>mid) return Query(x<<1,l,r)+Query(x<<1|1,l,r);
        else if(l<=mid) return Query(x<<1,l,r);
        else return Query(x<<1|1,l,r);
    }
}
namespace Fenw{
    int tr[N<<1];
    void Clear(){
        for(int i=1;i<=tot;i++) tr[i]=0;
    }
    void Add(int x,int k){
        while(x<=tot){
            tr[x]+=k;
            x+=x&-x;
        }
    }
    int Ask(int x){
        int sum=0;
        while(x){
            sum+=tr[x];
            x&=x-1;
        }
        return sum;
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i],val[i]=a[i];
        
        sort(val+1,val+n+1);
        for(int i=1;i<=n;i++){
            a[i]=lower_bound(val+1,val+n+1,a[i])-val;
            val[a[i]]--;
        }
        for(int i=1;i<=n;i++) val[a[i]]++;
        tot=0;
        for(int i=1;i<=n;i++) if(val[a[i]]<0) tot++;

        SgT::Build(1,1,n);
        for(int i=1,pos=tot;i<=n;i++){
            SgT::Modify(1,a[i],val[a[i]]);
            if(a[i]<=tot) Fenw::Add(a[i],1);
            while(pos&&-Fenw::Ask(pos)<=val[pos]) pos--;
            int ans=-Fenw::Ask(pos);
            Data d=SgT::Query(1,pos+1,n);
            cout<<min(ans+d.dlt,d.lim)<<'\n';
        }

        Fenw::Clear();
    }
    return 0;
}