#include<bits/stdc++.h>

using namespace std;

int main(){
    ifstream fin1("dig.out");
    ifstream fin2("dig13.out");
    int cnt=0;
    while(!fin2.eof()){
        if(fin1.eof()){
            cout<<"Less"<<endl;
            return 0;
        }
        cnt++;
        double x,y;
        fin1>>x,fin2>>y;
        if(fabs(x-y)>1e-4){
            cout<<"Err on line "<<cnt<<" : "<<x<<' '<<y<<endl;
            return 0;
        }
    }
    cout<<"OK"<<endl;
}