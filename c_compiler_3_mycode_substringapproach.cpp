#include <bits/stdc++.h>
using namespace std;

vector<string> keywords = {"int", "char", "float", "return", "if", "else", "while", "for", "do", "void"};
vector<char> punctuation = {'(', ')', '{', '}', ',', ';'};
vector<char> operators = {'+', '-', '*', '/', '=', '<', '>', '!', '%'};

// Function to check if a token is a valid identifier
bool isValidIdentifier(const string &token) {
    if (!isalpha(token[0]) && token[0] != '_') return false;
    for (char ch : token) {
        if (!isalnum(ch) && ch != '_') return false;
    }
    return true;
}

// Function to tokenize a line by splitting at spaces
void tokenize(const string &line, vector<string> &tokens) {
    stringstream ss(line);
    string word;
    
    while (ss >> word) { // Splitting at spaces
        tokens.push_back(word);
    }
}

// Function to categorize tokens
void processTokens(const vector<string> &tokens, vector<string> &categorizedTokens) {
    for (const string &token : tokens) {
        if (find(keywords.begin(), keywords.end(), token) != keywords.end()) {
            categorizedTokens.push_back("Keyword: " + token);
        }
        else if (isValidIdentifier(token)) {
            categorizedTokens.push_back("Identifier: " + token);
        }
        else if (isdigit(token[0])) {
            categorizedTokens.push_back("Constant: " + token);
        }
        else if (token.length() == 1 && find(punctuation.begin(), punctuation.end(), token[0]) != punctuation.end()) {
            categorizedTokens.push_back("Punctuation: " + token);
        }
        else if (token.length() == 1 && find(operators.begin(), operators.end(), token[0]) != operators.end()) {
            categorizedTokens.push_back("Operator: " + token);
        }
        else {
            categorizedTokens.push_back("Token: " + token); // Keeping it general for some cases
        }
    }
}

int main() {
    ifstream inputFile("input.c");
    
    string line;
    vector<string> tokens;
    vector<string> categorizedTokens;
    
    while (getline(inputFile, line)) {
        tokenize(line, tokens);
    }
    
    processTokens(tokens, categorizedTokens);

    cout << "TOKENS" << endl;
    for (const string &token : categorizedTokens) {
        cout << token << endl;
    }

    inputFile.close();
    return 0;
}
