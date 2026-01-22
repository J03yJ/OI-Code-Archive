#include<bits/stdc++.h>

using namespace std;

const int N=3e3+9;

int lat[N][N],n,m;
void InitFull(int n){
    for(int i=0;i<n;i++){
        for(int j=i,k=i;!lat[j+1][k+1];j=(j+n-1)%n,k=(k+1)%n){
            lat[j+1][k+1]=i+1;
        }
    }
}
void InitHalf(int n){
    for(int i=0;i<n;i++){
        for(int j=i,k=i;!lat[j+1][k+1];j=(j+n-1)%n,k=(k+1)%n){
            lat[j+1][k+1]=i%(n/2)+1;
        }
    }
    for(int i=0;i<n-1;i++){
        for(int j=i+1,k=i;!lat[j+1][k+1];j=(j+n-1)%n,k=(k+1)%n){
            lat[j+1][k+1]=i%(n/2)+1+n/2;
        }
    }
}
inline int Id(int x,int k){
    return x+k*m;
}

int main(){
    cin>>n;
    m=n/3;
    
    if(n%6==3){
        InitFull(m);
        for(int i=1;i<=m;i++) cout<<Id(i,0)<<' '<<Id(i,1)<<' '<<Id(i,2)<<endl;
        for(int i=1;i<=m;i++){
            for(int j=i+1;j<=m;j++){
                for(int k:{0,1,2}){
                    cout<<Id(i,k)<<' '<<Id(j,k)<<' '<<Id(lat[i][j],(k+1)%3)<<endl;
                }
            }
        }
    }else{
        InitHalf(m);
        for(int i=1;i<=m/2;i++) cout<<Id(i,0)<<' '<<Id(i,1)<<' '<<Id(i,2)<<endl;
        for(int i=1;i<=m/2;i++){
            for(int k:{0,1,2}){
                cout<<n<<' '<<Id(i,k)<<' '<<Id(i+m/2,(k+2)%3)<<endl;
            }
        }
        for(int i=1;i<=m;i++){
            for(int j=i+1;j<=m;j++){
                for(int k:{0,1,2}){
                    cout<<Id(i,k)<<' '<<Id(j,k)<<' '<<Id(lat[i][j],(k+1)%3)<<endl;
                }
            }
        }
    }

    return 0;
}