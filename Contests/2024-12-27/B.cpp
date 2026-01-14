#include<bits/stdc++.h>

using namespace std;

using pt=pair<double,double>;

double Dot(pt x,pt y){
    return x.first*y.first+x.second*y.second;
}
double Len(pt x){
    return sqrt(Dot(x,x));
}
double Angle(pt x,pt y){
    return acos(Dot(x,y)/Len(x)/Len(y));
}
pt Rev(pt x){
    return pt(-x.first,-x.second);
}

const int N=1e6+9;

int n;
pt p[N],v[N];
double a[N],pi=acos(-1);

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    cin>>n;
    for(int i=1;i<=n;i++) cin>>p[i].first>>p[i].second;

    for(int i=1;i<=n;i++){
        int j=i%n+1;
        v[i]=pt(p[i].first-p[j].first,p[i].second-p[j].second);
    }
    for(int i=1;i<=n;i++){
        int j=i%n+1;
        a[i]=Angle(v[i],Rev(v[j]));
    }

    double ans=0;
    for(int i=1;i<=n;i++){
        int j=i%n+1;
        ans+=max(0.0,pi-a[i]-a[j]);
    }
    ans/=pi;

    cout<<fixed<<setprecision(10)<<ans<<endl;
    
    return 0;
}