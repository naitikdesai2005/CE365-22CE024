#include<bits/stdc++.h>
using namespace std;
int main(){
    int n = 36;
    vector<char> inputSymbols;
    char temp;
    string s = "abcdefghijklmnopqrstuvwxyz0123456789";
    cout<<"\nInput symbols";
    for(int i = 0;i<n;i++){
        inputSymbols.push_back(s[i]);
    }
    for(auto s:inputSymbols){
      cout<<s;
    }
    int states=3;
    int initial=0;
    int numberofaccept = 1;
    vector<int> acceptingstates(numberofaccept);
    cout<<"Enter accepting states: ";
    for(int i = 0;i<numberofaccept;i++){
        acceptingstates[i] = 1;
    }
    int m = states;
    printf("Transition table: ");
    int mat[m][n];
    for(int i = 0;i<m;i++){
        for(int j = 0;j<n;j++){

            if(i == 0){
                if(inputSymbols[j]!='0' && inputSymbols[j]!='1' && inputSymbols[j]!='2' && inputSymbols[j]!='3' && inputSymbols[j]!='4' && inputSymbols[j]!='5' && inputSymbols[j]!='6' && inputSymbols[j]!='7' && inputSymbols[j]!='8' && inputSymbols[j]!='9'){
                    mat[i][j] = 1;
                }else{
                    mat[i][j] = 2;
                }
            }else if(i == 1){
                mat[i][j] = 1;
            }else{
                mat[i][j] = 2;
            }

            cout<<i<<" to "<<inputSymbols[j]<<"-> ";
            cout<<mat[i][j]<<endl;
        }
        cout<<endl;
    }
    int test1;
    cout<<endl<<"Enter test cases: ";
    cin>>test1;
    while(test1--){
    string input;
    cout<<"Enter string input: ";
    cin>>input;
    int currentstate = initial;
    for(int i = 0;i<input.length();i++){
            int intermediate = -1;
            for(int j = 0;j<inputSymbols.size()+1;j++){
                if(input[i] == inputSymbols[j]){
                    intermediate = j;
                    break;
                }
            }
            currentstate = mat[currentstate][intermediate];
    }

    //cout<<currentstate;
    bool flag = false;
    for(int i=0;i<numberofaccept;i++){
        if(currentstate == acceptingstates[i]){
            flag = true;
            break;
        }
    }
    if(flag){
        cout<<"Valid String"<<endl;
    }else{
    cout<<"Invalid String"<<endl;
    }
}
    cout<<endl<<"By 22CE024 - Naitik Desai";
    return 0;
}
