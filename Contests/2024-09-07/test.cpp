#include<bits/stdc++.h>

using namespace std;

int main(){
    vector<int> a(2000);
    for(int i=0;i<2000;i++) a[i]=i+1;
    random_shuffle(a.begin()+5,a.end());
    for(int x:a) cout<<x<<' ';cout<<endl;
}