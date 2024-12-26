#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cout<<"Number of input symbols: ";
    cin>>n;
    vector<char> inputSymbols;
    char temp;
    cout<<"\nInput symbols";
    for(int i = 0;i<n;i++){
            cin>>temp;
        inputSymbols.push_back(temp);
    }
    //for(auto s:inputSymbols){
      // cout<<s;
    //}
    int states=0;
    cout<<"Enter number of states: ";
    cin>>states;
    int initial=0;
    cout<<"Enter initial state: ";
    cin>>initial;
    int numberofaccept = 0;
    cout<<"Enter the number of accepting states: ";
    cin>>numberofaccept;
    vector<int> acceptingstates(numberofaccept);
    cout<<"Enter accepting states: ";
    for(int i = 0;i<numberofaccept;i++){
        cin>>acceptingstates[i];
    }
    int m = states;
    printf("Transition table: ");
    int mat[m][n];
    for(int i = 0;i<m;i++){
        for(int j = 0;j<n;j++){
            cout<<i<<" to "<<inputSymbols[j]<<"-> ";
            cin>>mat[i][j];
        }
    }
    for(int i = 0;i<m;i++){
        for(int j = 0;j<n;j++){
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
