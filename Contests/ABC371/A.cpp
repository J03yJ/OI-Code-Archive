#include<bits/stdc++.h>

using namespace std;

int main(){
    char a,b,c;
    cin>>a>>c>>b;
    if(a=='>'){ // A>B
        if(b=='>') cout<<'B'<<endl; // B>C
        else{
            if(c=='>') cout<<'C'<<endl; // B<C,B<A
            else cout<<'A'<<endl;
        }
    }else{  // A<B
        if(b=='<') cout<<'B'<<endl; // B<C
        else{
            if(c=='<') cout<<'C'<<endl;
            else cout<<'A'<<endl;
        }
    }
    return 0;
}