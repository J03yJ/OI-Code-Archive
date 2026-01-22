#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;
int a[N],b[N],apre[N],bpre[N],asuf[N],bsuf[N],n;

int Get(int l,int r,int *a){
    int ans=a[l];
    for(int i=l;i<=r;i++) ans=__gcd(ans,a[i]);
    return ans;
}
int GCD(int x,int y){
    if(!x||!y) return x|y;
    else return __gcd(x,y);
}
pair<int,int> CalcAns(int l,int r){
    if(l>r) return {GCD(apre[l-1],bsuf[r+1]),GCD(bpre[l-1],asuf[r+1])};
    else return {GCD(Get(l,r,a),GCD(bpre[l-1],bsuf[r+1])),GCD(Get(l,r,b),GCD(apre[l-1],asuf[r+1]))};
}
int CalcCnt(int l,int r,int L,int R,int ra,int rb){
    int i=r,j=L;
    while(i>=l&&a[i]%ra==0&&b[i]%rb==0) i--;
    while(j<=R&&a[j]%ra==0&&b[j]%rb==0) j++;
    cout<<l<<' '<<r<<' '<<L<<' '<<R<<' '<<ra<<' '<<rb<<' '<<(r-i)<<' '<<(j-L)<<' '<<a[j]<<endl;
    return (r-i)*(j-L);
}
void Upd(int l,int r,int L,int R,int &mx,int &c){
    pair<int,int> tmp=CalcAns(r+1,L-1);
    int ans=tmp.first+tmp.second;
    int cnt=CalcCnt(l,r,L,R,tmp.first,tmp.second);
    if(ans>mx) mx=ans,c=cnt;
    else if(ans==mx) c+=cnt;
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=n;i++) cin>>b[i];
        vector<int> pos;
        map<int,int> mp;
        for(int i=1;i<=n;i++) apre[i]=(i==1?a[1]:__gcd(apre[i-1],a[i]));
        for(int i=1;i<=n;i++) bpre[i]=(i==1?b[1]:__gcd(bpre[i-1],b[i]));
        for(int i=n;i>=1;i--) asuf[i]=(i==n?a[n]:__gcd(asuf[i+1],a[i]));
        for(int i=n;i>=1;i--) bsuf[i]=(i==n?b[n]:__gcd(bsuf[i+1],b[i]));

        for(int i=1;i<=n;i++){
            if(apre[i]!=apre[i-1]) pos.push_back(i-1),pos.push_back(i);
            else if(bpre[i]!=bpre[i-1]) pos.push_back(i-1),pos.push_back(i);
            if(asuf[i]!=asuf[i+1]) pos.push_back(i+1),pos.push_back(i);
            else if(bsuf[i]!=bsuf[i+1]) pos.push_back(i+1),pos.push_back(i);
        }
        sort(pos.begin(),pos.end());
        pos.push_back(n+1);
        int lim=unique(pos.begin(),pos.end())-pos.begin();
        while(pos.size()>lim) pos.pop_back();
        if(pos.front()==0) pos.erase(pos.begin());
        for(int x:pos) cout<<x<<' ';cout<<endl;

        int mx=0,c=0;
        for(int i=0;i<pos.size()-1;i++){
            for(int j=i;j<pos.size()-1;j++){
                Upd(pos[i],pos[i+1]-1,pos[j],pos[j+1]-1,mx,c);
            }
        }
        
        cout<<mx<<' '<<c<<endl;
        
        for(int i=1;i<=n;i++) apre[i]=asuf[i]=bpre[i]=bsuf[i]=0;
    }

    return 0;
}