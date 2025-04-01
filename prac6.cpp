#include<bits/stdc++.h>
using namespace std;

bool flag;
int i;

void S(string &);
void L(string &);
void Ldash(string &);

void L(string &st) {
    S(st);
    Ldash(st);
}

void Ldash(string &st) {
    if (st[i] == ',') {
        i++;
        S(st);
        Ldash(st);
    }
}

void S(string &s) {
    if (s[i] == 'a') {
        i++;
    } else if (s[i] == '(') {
        i++;
        L(s);
        if (s[i] == ')') {
            i++;
        } else {
            flag = false;  // Closing parenthesis not found
        }
    } else {
        flag = false;  // Unexpected character
    }
}

int main() {
    int test;
    cout << "Enter test cases: ";
    cin >> test;
    while (test--) {
        string str;
        cout << "Enter the string: ";
        cin >> str;

        // Reset variables for each test case
        i = 0;
        flag = true;

        // Start parsing
        S(str);

        // Check if the string is fully parsed and valid
        if (flag && i == str.length()) {
            cout << "Valid string" << endl;
        } else {
            cout << "Invalid string" << endl;
        }
    }

    return 0;
}
