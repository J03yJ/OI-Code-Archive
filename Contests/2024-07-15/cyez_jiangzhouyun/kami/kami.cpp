#include<bits/stdc++.h>

using namespace std;

ifstream fin("kami.in");
ofstream fout("kami.out");
#define cin fin
#define cout fout

const int N=3e5+9;

int gcd(int x,int y){
    if(!y) return x;
    else return gcd(y,x%y);
}

int G(int x,int y,int pw){
    if(pw==1) return 1;
    if(x+y+1<pw) return 0;
    pw/=2;
    return G(x%pw,y%pw,pw);
}
int F(int x,int y){
    if(!x) return y;
    if(x<3) return F(x-1,y)^F(x-1,y+1);
    long long k=0,pw=1;
    x--;
    while(pw<=x) k++,pw<<=1;
    int yy=y%(pw/2);
    int xx=x%(pw/2);
    if(!G(xx,yy,pw/2)) return 0;
    int xxx=pw;
    int yyy=y-yy;
    int g=gcd(xxx,yyy);
    // cout<<x<<' '<<y<<' '<<xxx<<' '<<yyy<<' '<<g<<' '<<G(xx,yy,pw/2)<<endl;
    return g*F(xxx/g,yyy/g);
}

int main(){
    string s;
    cin>>s;
    int n=s.size();
    s=" "+s;

    int ans=F(n,0),cnt=0;
    for(int i=1;i<=n;i++){
        if(s[i]=='1') cnt++;
        else ans^=F(n-i,cnt+1);
    }
    ans^=cnt;

    cout<<ans<<endl;

    return 0;
}