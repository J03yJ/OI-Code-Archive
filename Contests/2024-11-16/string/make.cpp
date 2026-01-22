#include<bits/stdc++.h>

using namespace std;

int main(){
    srand(time(0));
    int n=rand()%2000,m=rand()%2000;
    int k=rand()%n;
    ofstream fout("string.in");
    fout<<n<<' '<<m<<' '<<k<<endl;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            fout<<char('a');
        }
        fout<<endl;
    }

    return 0;
}