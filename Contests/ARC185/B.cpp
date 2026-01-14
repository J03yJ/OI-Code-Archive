#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;

int a[N],n;
struct Data{
    int l,r,sum;
    Data(){}
    Data(int _l,int _r,int _s){
        l=_l,r=_r,sum=_s;
    }
    int Mx(){return (sum+r-l)/(r-l+1);}
    int Mn(){return sum/(r-l+1);}
    Data operator +(Data x){
        return Data(l,x.r,sum+x.sum);
    }
};

signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        vector<Data> stk;
        for(int i=1;i<=n;i++){
            Data x=Data(i,i,a[i]);
            while(stk.size()&&stk.back().Mx()<=x.Mn()){
                x=stk.back()+x;
                stk.pop_back();
            }
            stk.push_back(x);
        }
        if(stk.size()<=1) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }

    return 0;
}