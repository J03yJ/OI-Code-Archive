#include<bits/stdc++.h>

using namespace std;

signed main(){
    ifstream fin1("city.out");
    ifstream fin2("3.ans");
    ofstream fout("transf.out");

    string s,t;
    while(getline(fin1,s),getline(fin2,t)){
        if(s!=t){
            fout<<s.size()<<' '<<t.size()<<endl;
            for(int i=0;i<t.size();i++){
                if(s[i]!=t[i]) fout<<s[i]<<' '<<t[i]<<endl;
            }
            fout<<s<<endl;
            fout<<t<<endl;
            fout<<int(s.back())<<endl;
        }
    }

    return 0;
}