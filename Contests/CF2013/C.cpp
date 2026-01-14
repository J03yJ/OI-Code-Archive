#include<bits/stdc++.h>

using namespace std;

int Query(string s){
    int op;
    cout<<"? "<<s<<endl;
    cin>>op;
    return op;
}
void Ret(string s){
    cout<<"! "<<s<<endl;
}

int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;

        if(n==1){
            if(Query("0")) Ret("0");
            else Ret("1");
            continue ;
        }

        string s="";
        if(Query("00")) s="00";
        else if(Query("01")) s="01";
        else if(Query("10")){
            for(int i=1;i<n;i++) s.push_back('1');
            s.push_back('0');
            Ret(s);
            continue ;
        }else{
            for(int i=1;i<=n;i++) s.push_back('1');
            Ret(s);
            continue ;
        }

        while(s.size()<n){
            if(Query(s+"0")) s+="0";
            else if(Query(s+"1")) s+="1";
            else break ;
        }
        while(s.size()<n){
            if(Query("0"+s)) s="0"+s;
            else if(Query("1"+s)) s="1"+s;
            else break ;
        }
        Ret(s);
    }
    return 0;
}