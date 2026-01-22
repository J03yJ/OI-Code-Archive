#include<bits/stdc++.h>
using namespace std;
 
#define int long long
#define endl '\n'
 
ifstream fin("xorcat.in");
ofstream fout("xorcat.out");
#define cin fin
#define cout fout
 
namespace JoeyJ{
    const int N=2e5+9;
    const int K=40;
     
    int a[N];
     
    struct base{
        int a[K];
        bool zero;
        int cnt=0;
         
        void insert(int k,int pos=K-1){
            if(cnt==K&&zero) return ;
            if(!k){
                zero=1;
                return ;
            }
            for(int i=pos;~i;i--){
                if(!((k>>i)&1)) continue ;
                if(!a[i]){
                    a[i]=k;
                    cnt++;
                    return ;
                }
                k^=a[i];
                if(!k){
                    zero=true;
                    return ;
                }
            }
        }
        void format(){
            for(int i=0;i<K;i++){
                if(!a[i]) continue ;
                for(int j=i+1;j<K;j++){
                    if((a[j]>>i)&1) a[j]^=a[i];
                }
            }
        }
         
        int operator [](int pos){
            return a[pos];
        }
        void operator +=(base b){
            zero|=b.zero;
            for(int i=0;i<K;i++){
                if(!b[i]) continue ;
                this->insert(b[i],i);
            }
        }
         
        void clear(){
            memset(a,0,sizeof(a));
            zero=0;
            cnt=0;
        }
        base(){
            this->clear();
        }
    };
     
    struct node{
        int l,r;
        base dat;
    }tr[N<<2];
    #define l(x) tr[x].l
    #define r(x) tr[x].r
    #define dat(x) tr[x].dat
     
    inline void pushup(int x){
        dat(x)=dat(2*x);
        dat(x)+=dat(2*x+1);
    }
    void build(int x,int l,int r){
        l(x)=l;r(x)=r;
        dat(x).clear();
        if(l(x)==r(x)){
            dat(x).insert(a[l]);
            return ;
        }
        int mid=l(x)+r(x)>>1;
        build(2*x,l,mid);
        build(2*x+1,mid+1,r);
        pushup(x);
    }
    void query(int x,int l,int r,base &b){
        if(r<l) return ;
        if(l<=l(x)&&r(x)<=r){
            b+=dat(x);
            return ;
        }
        int mid=l(x)+r(x)>>1;
        if(l<=mid) query(2*x,l,r,b);
        if(r>mid) query(2*x+1,l,r,b);
    }
     
    void main(){
        int n,m;
        cin>>n>>m;
        for(int i=1;i<=n;i++) cin>>a[i];
        build(1,1,n);
        vector<base> pre(n+2),suc(n+2);
        for(int i=1;i<=n;i++){
        	query(1,1,i,pre[i]);
        	query(1,i,n,suc[i]);
		}
        for(int i=1;i<=m;i++){
            int x,y,k;
            cin>>x>>y>>k;
            base ans;
            if(x>y) swap(x,y);
            if(!x&&!y) ans+=pre[n];
            else if(!x) ans+=pre[y-1],ans+=suc[y+1];
            else ans+=pre[x-1],query(1,x+1,y-1,ans),ans+=suc[y+1];
            ans.format();
            if(ans.zero) k--;
//          ans.debug();
            vector<int> v;
            int res=0;
            for(int j=0;j<K;j++) if(ans[j]) v.push_back(ans[j]);
            for(int j=0;j<v.size();j++) if((k>>j)&1) res^=v[j];
            cout<<res<<endl;
        }
    }
}
 
signed main(){
    int T;
    cin>>T;
    while(T--) JoeyJ::main();
    return 0;
}
