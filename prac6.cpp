#include<bits/stdc++.h>
using namespace std;
bool flag = true;
int i = 0;
void S(string &);
void L(string &);
void Ldash(string &);
void L(string& st) {
    S(st);
    Ldash(st);
}

void Ldash(string& st) {
    if (st[i] == ',') {
        i++;
        S(st);
        Ldash(st);
    }
    else if(st[i]=='\0'){
        flag=true;
    }
    else{
        flag=false;
    }
}

void S(string &s){
    if(s[i] == 'a'){
        i++;
        if(s[i] == '\0'){
            flag = true;
        }else{
            flag = false;
        }
    }
    else if(s[i] == '('){
             i++;
             L(s);
             if(s[i] == ')'){
                i++;
                if(s[i] == '\0'){
                    flag = true;
                }else{
                    flag = false;
                }
             }else{
                 flag = false;
             }
    }
    else{
        flag = false;
    }
}



int main(){
    int test;
    cout<<"Enter test cases: ";
    cin>>test;
    while(test--){
        string str;
        cout<<"Enter the string: ";
        cin>>str;
        S(str);
        if(flag){
            cout<<"Valid String"<<endl;
        }else{
            cout<<"Invalid string"<<endl;
        }
    }

}
