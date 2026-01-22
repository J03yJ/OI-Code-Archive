#include<bits/stdc++.h>

using namespace std;

ifstream fin("sequence.in");
ofstream fout("sequence.out");
#define cin fin
#define cout fout

const int N=2e5+9;
const int M=5e4+9;

int a[N],b[N],c[N],pos[N],buc[N];
// void Print(auto x,int lim){
//     for(int i=0;i<lim;i++) cout<<x[i]<<' ';cout<<endl;
// }

int main(){
    int id,T;
    cin>>id>>T;
    while(T--){
        int n,m,v;
        cin>>n>>m>>v;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=m;i++) cin>>b[i];
        for(int i=0;i<v;i++) cin>>c[i];

        int err=0,sum=0;
        sort(a+1,a+n+1),sort(b+1,b+m+1);
        for(int i=1;i<=n;i++){
            pos[i]=lower_bound(b+1,b+m+1,a[i])-b;
            if(pos[i]==pos[i-1]) err=1;
            sum=(sum+a[i])%v;
        }
        if(err){
            cout<<0<<endl;
            continue ;
        }
        pos[n+1]=m+1;

        bitset<M> res,mask;
        for(int i=0;i<v;i++) mask[i]=1;
        res[(v-sum)%v]=1;
        for(int i=1;i<=m;i++) b[i]%=v;
        for(int i=1,j=pos[1],k=pos[1];i<=n;i++,k=j){
            // cout<<pos[i]<<endl;
            for(;j<pos[i+1];j++) buc[b[j]]^=1;
            vector<int> tmp;
            for(int t=k;t<j;t++){
                if(buc[b[t]]){
                    tmp.push_back(b[t]);
                    buc[b[t]]=0;
                }
            }
            bitset<M> lst=res;
            res.reset();
            // cout<<k<<' '<<j-1<<" : "<<endl;
            // Print(lst,v);
            for(int x:tmp){
                // cout<<x<<" : "<<endl;
                // Print((lst<<x)&mask,v);
                // Print(lst>>(v-x),v);
                res^=(lst<<x)&mask;
                res^=lst>>(v-x);
                // Print(res,v);
            }
            // cout<<endl;
        }

        int ans=0;
        for(int i=0;i<v;i++) if(c[i]) ans^=res[i];
        cout<<ans<<endl;
    }

    return 0;
}