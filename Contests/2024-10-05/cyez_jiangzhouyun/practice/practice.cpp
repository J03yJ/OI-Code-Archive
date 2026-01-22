#include<bits/stdc++.h>

using namespace std;

ifstream fin("practice.in");
ofstream fout("practice.out");
#define cin fin
#define cout fout

#define int long long
int Solve(int h,int d,int w){
    if(!d||!h) return 0;
    d=min(d,h);

    #define F(x) (2*w*(x/w)+x%w)
    int l=0,r=d+1;
    while(l+1<r){
        int mid=l+r>>1;
        if(F(mid)>h+1) r=mid;
        else l=mid;
    }

    // cout<<l<<' '<<d<<endl;
    
    int ans=(d-r+1)*(h+1)-d*(d+1)/2;
    int trn=r/w,lft=r%w;
    // cout<<ans<<endl;
    ans+=(trn-1)*trn*w*w;
    // cout<<ans<<endl;
    ans+=lft*trn*w*2;
    // cout<<ans<<endl;
    ans+=(lft-1)*lft/2;
    // cout<<ans<<endl;
    ans+=(w-1)*w/2*trn;
    // cout<<ans<<endl;
    return ans;
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        int hl,hr,dl,dr,w;
        cin>>dl>>dr>>hl>>hr>>w;
        // cout<<Solve(hr,dr,w)<<' '<<Solve(hl-1,dr,w)<<' '<<Solve(hr,dl-1,w)<<' '<<Solve(hl-1,dl-1,w)<<endl;
        cout<<Solve(hr,dr,w)-Solve(hl-1,dr,w)-Solve(hr,dl-1,w)+Solve(hl-1,dl-1,w)<<endl;
    }
    return 0;
}